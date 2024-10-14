#ifndef FOX_SSE_H_
#define FOX_SSE_H_
#include "basic_def.h"
#include <iostream>
#if defined(_FM_SSE4_) && defined(FOX_USE_FLOAT)

namespace fm {

namespace simd {

template<typename element, size_t element_num, typename = std::enable_if<std::is_floating_point_v<element>>>
_fm_vec4 FM_FORCE_INLINE FM_CALL fmLoadVecP(const element(&ps)[element_num]) {
  // SSE Intinsics need 16 mem align
#if defined(FM_DEBUG)
  MEM_ALIGN_CHECK(ps, 16);
#endif
  if constexpr (element_num == 4) {
	  return _mm_loadu_ps(ps);
  }
  else {
	  FMFLOAT temp[4];
	  memcpy(temp, ps, element_num * sizeof(FMFLOAT));
	  
	  if constexpr (element_num < 4) {
		  temp[3] = 0;
	  }

	  if constexpr (element_num < 3) {
		  temp[2] = 0;
	  }

	  return _mm_loadu_ps(temp);
  }
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmLoadVec(FMFLOAT a, FMFLOAT b, FMFLOAT c,
                                     FMFLOAT d) {
  // In memory, its layout is like :
  //  | a | b | c | d |
  return _mm_set_ps(d, c, b, a);
}

template<typename element, size_t element_num, typename = std::enable_if<std::is_floating_point_v<element>>>
void FM_FORCE_INLINE FM_CALL fmStoreVec(element(&ps)[element_num],const _fm_vec4& vec) {
	FMFLOAT temp[4];
	_mm_storeu_ps(temp, vec);
	memcpy((void*)ps, (void*)temp, element_num * sizeof(FMFLOAT));
}

FMFLOAT FM_FORCE_INLINE FM_CALL fmGetElem(const _fm_vec4 &vec, int pos) {
#if defined(FM_DEBUG)
  assert(pos >= 0 && pos <= 3);
#endif
  FMFLOAT temp[4];
  fmStoreVec(temp, vec);
  return temp[pos];
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmSpreadVec(FMFLOAT t) {
  //_mm_broadcast_ss(&t) -> is a avx intrinsic, much faster than below
  return _mm_set1_ps(t);
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecAdd(const _fm_vec4 &veca,
                                    const _fm_vec4 &vecb) {
  return _mm_add_ps(veca, vecb);
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecScale(const _fm_vec4 &veca, FMFLOAT factor) {
  return _mm_mul_ps(veca, fmSpreadVec(factor));
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecMul(const _fm_vec4 &veca,
                                    const _fm_vec4 &vecb) {
  return _mm_mul_ps(veca, vecb);
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecSub(const _fm_vec4 &veca,
                                    const _fm_vec4 &vecb) {
  return _mm_sub_ps(veca, vecb);
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecDiv(const _fm_vec4 &veca,
                                    const _fm_vec4 &vecb) {
  return _mm_div_ps(veca, vecb);
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecCeil(const _fm_vec4 &vec) {
  return _mm_ceil_ps(vec);
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecFloor(const _fm_vec4 &vec) {
  return _mm_floor_ps(vec);
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecMaxOfEachElem(const _fm_vec4 &veca,
                                              const _fm_vec4 &vecb) {
  return _mm_max_ps(veca, vecb);
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecMinOfEachElem(const _fm_vec4 &veca,
                                              const _fm_vec4 &vecb) {
  return _mm_min_ps(veca, vecb);
}

FMFLOAT FM_FORCE_INLINE FM_CALL fmMaxElemOfVec(const _fm_vec4 &vec) {
  _fm_vec4 temp = vec;
  temp = _mm_shuffle_ps(temp, temp, _FM_SHUFFLE(3, 2, 1, 0));
  /*
  origin:   | 3 | 2 | 1 | 0 |
  premuted: | 0 | 1 | 2 | 3 |
  */
  temp = fmVecMaxOfEachElem(temp, vec);
  /*
  temp:  | max(3,0) | max(2,1) | max(2,1) | max(3,0) |
  temp1: | max(2,1) | max(3,0) | max(3,0) | max(2,1) |
  */
  _fm_vec4 temp1 = _mm_shuffle_ps(temp, temp, _FM_SHUFFLE(1, 0, 3, 2));
  temp = fmVecMaxOfEachElem(temp1, temp);
  /*
  | max | max | max | max |
  */
  return fmGetElem(temp, 0);
}

FMFLOAT FM_FORCE_INLINE FM_CALL fmMinElemOfVec(const _fm_vec4 &vec) {
  _fm_vec4 temp = vec;
  temp = _mm_shuffle_ps(temp, temp, _FM_SHUFFLE(3, 2, 1, 0));
  /*
  origin:   | 3 | 2 | 1 | 0 |
  premuted: | 0 | 1 | 2 | 3 |
  */
  temp = fmVecMinOfEachElem(temp, vec);
  /*
  temp:  | min(3,0) | min(2,1) | min(2,1) | min(3,0) |
  temp1: | min(2,1) | min(3,0) | min(3,0) | min(2,1) |
  */
  _fm_vec4 temp1 = _mm_shuffle_ps(temp, temp, _FM_SHUFFLE(1, 0, 3, 2));
  temp = fmVecMinOfEachElem(temp1, temp);
  /*
  | min | min | min | min |
  */
  return fmGetElem(temp, 0);
}

FMFLOAT FM_FORCE_INLINE FM_CALL fmVecDot(const _fm_vec4 &veca, const _fm_vec4 &vecb) {

  _fm_vec4 ab = fmVecMul(veca, vecb);

  // veca(a,b,c,d) vecb(e,f,g,h)
  //_mm256_hadd_pd(veca,vecb) => (a+b,c+d,e+f,g+h)

  _fm_vec4 temp = _mm_hadd_ps(ab, ab);
  _fm_vec4 shuffle = _mm_shuffle_ps(temp, temp, _FM_SHUFFLE(3, 2, 1, 0));
  return fmGetElem(fmVecAdd(shuffle, temp), 0);
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecSqrt(const _fm_vec4 &vec) {
  return _mm_sqrt_ps(vec);
}

// Two vec3 cross product
_fm_vec4 FM_FORCE_INLINE FM_CALL fmVec3Cross(const _fm_vec4 &veca,
                                       const _fm_vec4 &vecb) {
  /*
  //Naive version
  //a.yzx * b.zxy - a.zxy * b.yzx
          _fm_vec4 aYZX = _mm_shuffle_ps(veca,veca,_FM_SHUFFLE(1, 2, 0, 3));
          _fm_vec4 aZXY = _mm_shuffle_ps(veca,veca,_FM_SHUFFLE(2, 0, 1, 3));
          _fm_vec4 bZXY = _mm_shuffle_ps(vecb,vecb,_FM_SHUFFLE(2, 0, 1, 3));
          _fm_vec4 bYZX = _mm_shuffle_ps(vecb,vecb,_FM_SHUFFLE(1, 2, 0, 3));
          return fmVecSub( fmVecMul(aYZX, bZXY) ,fmVecMul(aZXY, bYZX) );
  */
  // Faster version, one shuffle less
  _fm_vec4 aYZX = (_fm_vec4)_mm_shuffle_ps(veca, veca, _FM_SHUFFLE(1, 2, 0, 3));
  _fm_vec4 bYZX = (_fm_vec4)_mm_shuffle_ps(vecb, vecb, _FM_SHUFFLE(1, 2, 0, 3));
  _fm_vec4 c = _mm_sub_ps(_mm_mul_ps(veca, bYZX), _mm_mul_ps(aYZX, vecb));
  return _mm_shuffle_ps(c, c, _FM_SHUFFLE(1, 2, 0, 3));
}

FMFLOAT FM_FORCE_INLINE FM_CALL fmVec2Cross(const _fm_vec4 &veca,
                                      const _fm_vec4 &vecb) {
  _fm_vec4 bYX = _mm_shuffle_ps(vecb, vecb, _FM_SHUFFLE(1, 0, 2, 3));
  _fm_vec4 temp = _mm_mul_ps(bYX, veca);
  _fm_vec4 hSub = _mm_hsub_ps(temp, temp);
  return fmGetElem(hSub, 0);
}

FMFLOAT FM_FORCE_INLINE FM_CALL fmVecSum(const _fm_vec4 &vec) {
  _fm_vec4 temp = _mm_shuffle_ps(vec, vec, _FM_SHUFFLE(3, 2, 1, 0));
  _fm_vec4 sum = fmVecAdd(temp, vec);
  temp = _mm_hadd_ps(sum, sum);
  return fmGetElem(temp, 0);
}

void FM_FORCE_INLINE FM_CALL fmMat4Transpose(const FMFLOAT (*vecs)[4],
	FMFLOAT(*ret)[4]) {
  _fm_vec4 v0, v1, v2, v3;
  v0 = fmLoadVecP(vecs[0]);
  v1 = fmLoadVecP(vecs[1]);
  v2 = fmLoadVecP(vecs[2]);
  v3 = fmLoadVecP(vecs[3]);

  _fm_vec4 a, b, c, d;
  a = _mm_unpacklo_ps(v0, v1); // 00 10 01 11
  b = _mm_unpackhi_ps(v0, v1); // 02 12 03 13
  c = _mm_unpacklo_ps(v2, v3); // 20 30 21 31
  d = _mm_unpackhi_ps(v2, v3); // 22 32 23 33
  _fm_vec4 ta, tb, tc, td;
  ta = _mm_movelh_ps(a, c); // 00 10 20 30
  tb = _mm_movehl_ps(c, a); // 01 11 21 31
  tc = _mm_movelh_ps(b, d); // 02 12 22 32
  td = _mm_movehl_ps(d, b); // 03 13 23 33

  fmStoreVec(ret[0], ta);
  fmStoreVec(ret[1], tb);
  fmStoreVec(ret[2], tc);
  fmStoreVec(ret[3], td);
}

void FM_FORCE_INLINE FM_CALL fmMat4TransposeVec(const _fm_vec4 *vecs, _fm_vec4 *ret) {

  _fm_vec4 a, b, c, d;
  a = _mm_unpacklo_ps(vecs[0], vecs[1]); // 00 10 01 11
  b = _mm_unpackhi_ps(vecs[0], vecs[1]); // 02 12 03 13
  c = _mm_unpacklo_ps(vecs[2], vecs[3]); // 20 30 21 31
  d = _mm_unpackhi_ps(vecs[2], vecs[3]); // 22 32 23 33
  ret[0] = _mm_movelh_ps(a, c); // 00 10 20 30
  ret[1] = _mm_movehl_ps(c, a); // 01 11 21 31
  ret[2] = _mm_movelh_ps(b, d); // 02 12 22 32
  ret[3] = _mm_movehl_ps(d, b); // 03 13 23 33
}
 
void FM_FORCE_INLINE FM_CALL fmMat4MulVec(const _fm_vec4 *vecsa,
                                      const _fm_vec4 *transposedMatb,_fm_vec4 ret[4]) {
	FMFLOAT _m00 = fmVecDot(vecsa[0], transposedMatb[0]);
	FMFLOAT _m01 = fmVecDot(vecsa[0], transposedMatb[1]);
	FMFLOAT _m02 = fmVecDot(vecsa[0], transposedMatb[2]);
	FMFLOAT _m03 = fmVecDot(vecsa[0], transposedMatb[3]);
	FMFLOAT _m10 = fmVecDot(vecsa[1], transposedMatb[0]);
	FMFLOAT _m11 = fmVecDot(vecsa[1], transposedMatb[1]);
	FMFLOAT _m12 = fmVecDot(vecsa[1], transposedMatb[2]);
	FMFLOAT _m13 = fmVecDot(vecsa[1], transposedMatb[3]);
	FMFLOAT _m20 = fmVecDot(vecsa[2], transposedMatb[0]);
	FMFLOAT _m21 = fmVecDot(vecsa[2], transposedMatb[1]);
	FMFLOAT _m22 = fmVecDot(vecsa[2], transposedMatb[2]);
	FMFLOAT _m23 = fmVecDot(vecsa[2], transposedMatb[3]);
	FMFLOAT _m30 = fmVecDot(vecsa[3], transposedMatb[0]);
	FMFLOAT _m31 = fmVecDot(vecsa[3], transposedMatb[1]);
	FMFLOAT _m32 = fmVecDot(vecsa[3], transposedMatb[2]);
	FMFLOAT _m33 = fmVecDot(vecsa[3], transposedMatb[3]);
	ret[0] = fmLoadVec(_m00, _m01, _m02, _m03); 
	ret[1] = fmLoadVec(_m10, _m11, _m12, _m13); 
	ret[2] = fmLoadVec(_m20, _m21, _m22, _m23); 
	ret[3] = fmLoadVec(_m30, _m31, _m32, _m33); 
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecUnaryMinus(const _fm_vec4 &vec) {
  return _mm_xor_ps(vec, _mm_set1_ps(-0.0f));
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecAbs(const _fm_vec4 &vec) {
  return _mm_andnot_ps(_mm_set1_ps(-0.0f), vec);
}
} // namespace simd
} // namespace fm
#endif

#endif // FOX_SSE_H_