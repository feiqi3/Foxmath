#ifndef FOX_AVX_H__
#define FOX_AVX_H__
#include "basic_def.h"
#include <iostream>

#if defined(_FM_AVX2_) && defined(FOX_USE_DOUBLE)

namespace fm {

namespace simd {

template<typename element, size_t element_num, typename = std::enable_if<std::is_floating_point_v<element>>>
	_fm_vec4 FM_FORCE_INLINE FM_CALL fmLoadVecP(const element(&pd)[element_num]) {
  // AVX Intinsics for pd need 32 mem align
#if defined(FM_DEBUG)
  MEM_ALIGN_CHECK(pd, FM_ALIGN_REQ);
#endif
  if constexpr (element_num == 4) {
	  return _mm256_load_pd(pd);
  }
  else {
	  FMFLOAT temp[4];
	  memcpy(temp, pd, element_num * sizeof(FMFLOAT));

	  if constexpr (element_num < 4) {
		  temp[3] = 0;
	  }

	  if constexpr (element_num < 3) {
		  temp[2] = 0;
	  }
	  return _mm256_loadu_pd(temp);
  }
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmLoadVec(FMFLOAT a, FMFLOAT b, FMFLOAT c,
                                     FMFLOAT d) {
  // In memory, its layout is like :
  //  | a | b | c | d |
  //  | 0 | 1 | 2 | 3 | -> shuffle index
  return _mm256_set_pd(d, c, b, a);
}

template<typename element, size_t element_num, typename = std::enable_if<std::is_floating_point_v<element>>>
void FM_FORCE_INLINE FM_CALL fmStoreVec(element(&pd)[element_num], const _fm_vec4& vec) {
	FMFLOAT temp[4];
	_mm256_storeu_pd(temp, vec);
	memcpy((void*)pd, (void*)temp, element_num * sizeof(FMFLOAT));
}

FMFLOAT FM_FORCE_INLINE FM_CALL fmGetElem(const _fm_vec4 &vec, int pos) {
#if defined(FM_DEBUG)
  assert(pos >= 0 && pos <= 3);
#endif
  // May get a bad asm
  /*return ((double*)(&vec))[pos];*/

  // Use intrinsic to get element
  FMFLOAT temp[4];
  fmStoreVec(temp, vec);
  return temp[pos];
}

// https://www.intel.com/content/www/us/en/docs/cpp-compiler/developer-guide-reference/2021-8/mm256-broadcast-sd.html
// Loads scalar double-precision floating-point values from the specified
// address a, and broadcasts it to all four elements in the destination vector.
_fm_vec4 FM_FORCE_INLINE FM_CALL fmSpreadVec(FMFLOAT t) {
  return _mm256_broadcast_sd(&t);
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecAdd(const _fm_vec4 &veca,
                                    const _fm_vec4 &vecb) {
  return _mm256_add_pd(veca, vecb);
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecScale(const _fm_vec4 &veca, FMFLOAT factor) {
  return _mm256_mul_pd(veca, fmSpreadVec(factor));
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecMul(const _fm_vec4 &veca,const _fm_vec4 &vecb) {
  alignas(32) auto ret = _mm256_mul_pd(veca, vecb);
  return ret;
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecSub(const _fm_vec4 &veca,
                                    const _fm_vec4 &vecb) {
  return _mm256_sub_pd(veca, vecb);
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecDiv(const _fm_vec4 &veca,
                                    const _fm_vec4 &vecb) {
  return _mm256_div_pd(veca, vecb);
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecCeil(const _fm_vec4 &vec) {
  return _mm256_ceil_pd(vec);
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecFloor(const _fm_vec4 &vec) {
  return _mm256_floor_pd(vec);
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecMaxOfEachElem(const _fm_vec4 &veca,
                                              const _fm_vec4 &vecb) {
  return _mm256_max_pd(veca, vecb);
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecMinOfEachElem(const _fm_vec4 &veca,
                                              const _fm_vec4 &vecb) {
  return _mm256_min_pd(veca, vecb);
}

FMFLOAT FM_FORCE_INLINE FM_CALL fmMaxElemOfVec(const _fm_vec4 &vec) {
  _fm_vec4 temp = vec;
  temp = _mm256_permute4x64_pd(temp, _FM_SHUFFLE(3, 2, 1, 0));
  /*
  origin:   | 0 | 1 | 2 | 3 |
  premuted: | 3 | 2 | 1 | 0 |
  */
  temp = fmVecMaxOfEachElem(temp, vec);
  /*
  temp:  | max(3,0) | max(2,1) | max(2,1) | max(3,0) |
  temp1: | max(2,1) | max(3,0) | max(3,0) | max(2,1) |
  */
  _fm_vec4 temp1 = _mm256_permute4x64_pd(temp, _FM_SHUFFLE(1, 0, 3, 2));
  temp = fmVecMaxOfEachElem(temp1, temp);
  /*
  | max | max | max | max |
  */
  return fmGetElem(temp, 0);
}

FMFLOAT FM_FORCE_INLINE FM_CALL fmMinElemOfVec(const _fm_vec4 &vec) {
  _fm_vec4 temp = vec;
  temp = _mm256_permute4x64_pd(temp, _FM_SHUFFLE(3, 2, 1, 0));
  /*
  origin:   | 3 | 2 | 1 | 0 |
  premuted: | 0 | 1 | 2 | 3 |
  */
  temp = fmVecMinOfEachElem(temp, vec);
  /*
  temp:  | min(3,0) | min(2,1) | min(2,1) | min(3,0) |
  temp1: | min(2,1) | min(3,0) | min(3,0) | min(2,1) |
  */
  _fm_vec4 temp1 = _mm256_permute4x64_pd(temp, _FM_SHUFFLE(1, 0, 3, 2));
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

  _fm_vec4 temp = _mm256_hadd_pd(ab, ab);
  _fm_vec4 shuffle = _mm256_permute4x64_pd(temp, _FM_SHUFFLE(3, 2, 1, 0));
  return fmGetElem(fmVecAdd(shuffle, temp), 0);
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecSqrt(const _fm_vec4 &vec) {
  return _mm256_sqrt_pd(vec);
}

// Two vec3 cross product
_fm_vec4 FM_FORCE_INLINE FM_CALL fmVec3Cross(const _fm_vec4 &veca,
                                       const _fm_vec4 &vecb) {
  /*
          //Naive version
          //a.yzx * b.zxy - a.zxy * b.yzx
          _fm_vec4 aYZX = _mm256_permute4x64_pd(veca, _FM_SHUFFLE(1, 2, 0, 3));
          _fm_vec4 aZXY = _mm256_permute4x64_pd(veca, _FM_SHUFFLE(2, 0, 1, 3));
          _fm_vec4 bZXY = _mm256_permute4x64_pd(vecb, _FM_SHUFFLE(2, 0, 1, 3));
          _fm_vec4 bYZX = _mm256_permute4x64_pd(vecb, _FM_SHUFFLE(1, 2, 0, 3));
          return fmVecSub(fmVecMul(aYZX, bZXY), fmVecMul(aZXY, bYZX));
          */
  // Faster version, one shuffle less
  _fm_vec4 aYZX = _mm256_permute4x64_pd(veca, _FM_SHUFFLE(1, 2, 0, 3));
  _fm_vec4 bYZX = _mm256_permute4x64_pd(vecb, _FM_SHUFFLE(1, 2, 0, 3));
  _fm_vec4 c =
      _mm256_sub_pd(_mm256_mul_pd(veca, bYZX), _mm256_mul_pd(aYZX, vecb));
  return _mm256_permute4x64_pd(c, _FM_SHUFFLE(1, 2, 0, 3));
}

FMFLOAT FM_FORCE_INLINE FM_CALL fmVec2Cross(const _fm_vec4 &veca,
                                      const _fm_vec4 &vecb) {
  _fm_vec4 bYX = _mm256_permute4x64_pd(vecb, _FM_SHUFFLE(1, 0, 2, 3));
  _fm_vec4 temp = _mm256_mul_pd(bYX, veca);
  _fm_vec4 hSub = _mm256_hsub_pd(temp, temp);
  return fmGetElem(hSub, 0);
}

FMFLOAT FM_FORCE_INLINE FM_CALL fmVecSum(const _fm_vec4 &vec) {
  _fm_vec4 temp = _mm256_permute4x64_pd(vec, _FM_SHUFFLE(3, 2, 1, 0));
  _fm_vec4 sum = fmVecAdd(temp, vec);
  temp = _mm256_hadd_pd(sum, sum);
  return fmGetElem(temp, 0);
}

void FM_FORCE_INLINE FM_CALL fmMat4Transpose(const FMFLOAT(*vecs)[4],
	 FMFLOAT(*ret)[4]) {
  _fm_vec4 v0, v1, v2, v3;
  v0 = fmLoadVecP(vecs[0]);
  v1 = fmLoadVecP(vecs[1]);
  v2 = fmLoadVecP(vecs[2]);
  v3 = fmLoadVecP(vecs[3]);

  __m256d t1 = _mm256_permute4x64_pd(v0, 0b01001110);      // a2,a3,a0,a1
  __m256d t2 = _mm256_permute4x64_pd(v1, 0b01001110);      // b2,b3,b0,b1
  __m256d t3 = _mm256_permute4x64_pd(v2, 0b01001110);      // c2,c3,c0,c1
  __m256d t4 = _mm256_permute4x64_pd(v3, 0b01001110);      // d2,d3,d0,d1
  __m256d t5 = _mm256_blend_pd(v0, t3, 0b1100);            // a0,a1,c0,c1
  __m256d t6 = _mm256_blend_pd(v1, t4, 0b1100);            // b0,b1,d0,d1
  __m256d t7 = _mm256_blend_pd(t1, v2, 0b1100);            // a2,a3,c2,c3
  __m256d t8 = _mm256_blend_pd(t2, v3, 0b1100);            // b2,b3,d2,d3
  _mm256_storeu_pd(ret[0], _mm256_unpacklo_pd(t5, t6)); // a0,b0,c0,d0
  _mm256_storeu_pd(ret[1], _mm256_unpackhi_pd(t5, t6)); // a1,b1,c1,d1
  _mm256_storeu_pd(ret[2], _mm256_unpacklo_pd(t7, t8)); // a2,b2,c2,d2
  _mm256_storeu_pd(ret[3], _mm256_unpackhi_pd(t7, t8)); // a3,b3,c3,d3
}

void FM_FORCE_INLINE FM_CALL fmMat4TransposeVec(const _fm_vec4 *vecs,
                                       _fm_vec4 *ret) {

  __m256d t1 = _mm256_permute4x64_pd(vecs[0], 0b01001110);      // a2,a3,a0,a1
  __m256d t2 = _mm256_permute4x64_pd(vecs[1], 0b01001110);      // b2,b3,b0,b1
  __m256d t3 = _mm256_permute4x64_pd(vecs[2], 0b01001110);      // c2,c3,c0,c1
  __m256d t4 = _mm256_permute4x64_pd(vecs[3], 0b01001110);      // d2,d3,d0,d1
  __m256d t5 = _mm256_blend_pd(vecs[0], t3, 0b1100);            // a0,a1,c0,c1
  __m256d t6 = _mm256_blend_pd(vecs[1], t4, 0b1100);            // b0,b1,d0,d1
  __m256d t7 = _mm256_blend_pd(t1, vecs[2], 0b1100);            // a2,a3,c2,c3
  __m256d t8 = _mm256_blend_pd(t2, vecs[3], 0b1100);            // b2,b3,d2,d3
  ret[0] = _mm256_unpacklo_pd(t5, t6); // a0,b0,c0,d0
  ret[1] = _mm256_unpackhi_pd(t5, t6); // a1,b1,c1,d1
  ret[2] = _mm256_unpacklo_pd(t7, t8); // a2,b2,c2,d2
  ret[3] = _mm256_unpackhi_pd(t7, t8); // a3,b3,c3,d3
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
  return _mm256_xor_pd(vec, _mm256_set1_pd(-0.0f));
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecAbs(const _fm_vec4 &vec) {
  return _mm256_andnot_pd(_mm256_set1_pd(-0.0f), vec);
}
} // namespace simd
} // namespace fm
#endif //_FM_AVX2_

#endif // FOX_AVX_H__