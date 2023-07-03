#ifndef FOX_PURE_H_
#define FOX_PURE_H_
#include "basic_def.h"
#include <algorithm>
#include <cstring>

#if defined(FOX_PURE) && (!defined(_FM_SSE4_) && !defined(_FM_AVX2_))

#include <cmath>
namespace fm {

namespace simd {

_fm_vec4 FM_FORCE_INLINE FM_CALL fmLoadVecP(const FMFLOAT *pd) {
  _fm_vec4 ret;
  std::memcpy(ret.v, pd, 4 * sizeof(FMFLOAT));
  return ret;
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmLoadVec(FMFLOAT a, FMFLOAT b, FMFLOAT c,
                                     FMFLOAT d) {
  _fm_vec4 ret;
  ret.v[0] = a;
  ret.v[1] = b;
  ret.v[2] = c;
  ret.v[3] = d;
  return ret;
}

void FM_FORCE_INLINE FM_CALL fmStoreVec(fmAlignFLoat4 &f4, _fm_vec4 vec) {
  memcpy(f4._v, vec.v, 4 * sizeof(FMFLOAT));
}

FMFLOAT FM_FORCE_INLINE FM_CALL fmGetElem(const _fm_vec4 &vec, int pos) {
#if defined(FM_DEBUG)
  assert(pos >= 0 && pos <= 3);
#endif
  return vec.v[pos];
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmSpreadVec(FMFLOAT t) {
  _fm_vec4 ret;
  ret.v[0] = t;
  ret.v[1] = t;
  ret.v[2] = t;
  ret.v[3] = t;
  return ret;
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecAdd(const _fm_vec4 &veca,
                                    const _fm_vec4 &vecb) {
  _fm_vec4 ret;
  ret.v[0] = veca.v[0] + vecb.v[0];
  ret.v[1] = veca.v[1] + vecb.v[1];
  ret.v[2] = veca.v[2] + vecb.v[2];
  ret.v[3] = veca.v[3] + vecb.v[3];
  return ret;
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecScale(const _fm_vec4 &veca, FMFLOAT factor) {
  _fm_vec4 ret = veca;
  ret.v[0] *= factor;
  ret.v[1] *= factor;
  ret.v[2] *= factor;
  ret.v[3] *= factor;
  return ret;
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecMul(const _fm_vec4 &veca,
                                    const _fm_vec4 &vecb) {
  _fm_vec4 ret = veca;
  ret.v[0] = veca.v[0] * vecb.v[0];
  ret.v[1] = veca.v[1] * vecb.v[1];
  ret.v[2] = veca.v[2] * vecb.v[2];
  ret.v[3] = veca.v[3] * vecb.v[3];
  return ret;
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecSub(const _fm_vec4 &veca,
                                    const _fm_vec4 &vecb) {
  _fm_vec4 ret = veca;
  ret.v[0] = veca.v[0] - vecb.v[0];
  ret.v[1] = veca.v[1] - vecb.v[1];
  ret.v[2] = veca.v[2] - vecb.v[2];
  ret.v[3] = veca.v[3] - vecb.v[3];
  return ret;
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecDiv(const _fm_vec4 &veca,
                                    const _fm_vec4 &vecb) {
  _fm_vec4 ret;
  ret.v[0] = veca.v[0] / vecb.v[0];
  ret.v[1] = veca.v[1] / vecb.v[1];
  ret.v[2] = veca.v[2] / vecb.v[2];
  ret.v[3] = veca.v[3] / vecb.v[3];
  return ret;
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecCeil(const _fm_vec4 &vec) {
  _fm_vec4 ret;
  ret.v[0] = std::ceil(vec.v[0]);
  ret.v[1] = std::ceil(vec.v[1]);
  ret.v[2] = std::ceil(vec.v[2]);
  ret.v[3] = std::ceil(vec.v[3]);
  return ret;
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecFloor(const _fm_vec4 &vec) {
  _fm_vec4 ret;
  ret.v[0] = std::floor(vec.v[0]);
  ret.v[1] = std::floor(vec.v[1]);
  ret.v[2] = std::floor(vec.v[2]);
  ret.v[3] = std::floor(vec.v[3]);
  return ret;
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecMaxOfEachElem(const _fm_vec4 &veca,
                                              const _fm_vec4 &vecb) {
  _fm_vec4 ret;
  ret.v[0] = std::max(veca.v[0], vecb.v[0]);
  ret.v[1] = std::max(veca.v[1], vecb.v[1]);
  ret.v[2] = std::max(veca.v[2], vecb.v[2]);
  ret.v[3] = std::max(veca.v[3], vecb.v[3]);
  return ret;
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecMinOfEachElem(const _fm_vec4 &veca,
                                              const _fm_vec4 &vecb) {
  _fm_vec4 ret;
  ret.v[0] = std::min(veca.v[0], vecb.v[0]);
  ret.v[1] = std::min(veca.v[1], vecb.v[1]);
  ret.v[2] = std::min(veca.v[2], vecb.v[2]);
  ret.v[3] = std::min(veca.v[3], vecb.v[3]);
  return ret;
}

FMFLOAT FM_FORCE_INLINE FM_CALL fmMaxElemOfVec(const _fm_vec4 &vec) {
  FMFLOAT temp =
      std::max(vec.v[0], std::max(vec.v[1], std::max(vec.v[2], vec.v[3])));
  return temp;
}

FMFLOAT FM_FORCE_INLINE FM_CALL fmMinElemOfVec(const _fm_vec4 &vec) {
  FMFLOAT temp =
      std::min(vec.v[0], std::min(vec.v[1], std::min(vec.v[2], vec.v[3])));
  return temp;
}

FMFLOAT FM_FORCE_INLINE FM_CALL fmVecDot(const _fm_vec4 &veca, const _fm_vec4 &vecb) {
  _fm_vec4 temp = fmVecMul(veca, vecb);
  return temp.v[0] + temp.v[1] + temp.v[2] + temp.v[3];
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecSqrt(const _fm_vec4 &vec) {
  _fm_vec4 ret;
  ret.v[0] = std::sqrt(vec.v[0]);
  ret.v[1] = std::sqrt(vec.v[1]);
  ret.v[2] = std::sqrt(vec.v[2]);
  ret.v[3] = std::sqrt(vec.v[3]);
  return ret;
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVec3Cross(const _fm_vec4 &veca,
                                       const _fm_vec4 &vecb) {
  _fm_vec4 ret;
  ret.v[0] = veca.v[1] * vecb.v[2] - veca.v[2] * vecb.v[1];
  ret.v[1] = veca.v[2] * vecb.v[0] - veca.v[0] * vecb.v[2];
  ret.v[2] = veca.v[0] * vecb.v[1] - veca.v[1] * vecb.v[0];
  ret.v[3] = 0;
  return ret;
}

FMFLOAT FM_FORCE_INLINE FM_CALL fmVec2Cross(const _fm_vec4 &veca,
                                      const _fm_vec4 &vecb) {
  FMFLOAT ret;
  ret = veca.v[0] * vecb.v[1] - veca.v[1] - vecb.v[0];
  return ret;
}

FMFLOAT FM_FORCE_INLINE FM_CALL fmVecSum(const _fm_vec4 &vec) {
  return vec.v[0] + vec.v[1] + vec.v[2] + vec.v[3];
}

void FM_FORCE_INLINE FM_CALL fmMat4Transpose(const fmAlignFLoat4 *vecs,
                                       fmAlignFLoat4 *ret) {
  for (char i = 0; i < 4; i++) {
    for (char j = 0; j < 4; j++) {
      ret[i]._v[j] = vecs[j]._v[i];
    }
  }
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecUnaryMinus(const _fm_vec4 &vec) {
	_fm_vec4 ret;
	for (char i = 0; i < 4; ++i) {
		ret.v[i] = -vec.v[i];
	}
	return ret;
}

_fm_vec4 FM_FORCE_INLINE FM_CALL fmVecAbs(const _fm_vec4 &vec) {
  	_fm_vec4 ret;
	for (char i = 0; i < 4; ++i) {
		ret.v[i] = std::abs(vec.v[i]);
	}
	return ret;
}

void FM_FORCE_INLINE FM_CALL fmMat4TransposeVec(const _fm_vec4 *vecs,
                                       _fm_vec4 *ret) {
  for (char i = 0; i < 4; i++) {
    for (char j = 0; j < 4; j++) {
      ret[i].v[j] = vecs[j].v[i];
    }
  }
}

void FM_FORCE_INLINE FM_CALL fmMat4MulVec(const _fm_vec4 *vecsa,
                                      const _fm_vec4 *transposedMatb,_fm_vec4 ret[4]) {
	float _m00 = fmVecDot(vecsa[0], transposedMatb[0]);
	float _m01 = fmVecDot(vecsa[0], transposedMatb[1]);
	float _m02 = fmVecDot(vecsa[0], transposedMatb[2]);
	float _m03 = fmVecDot(vecsa[0], transposedMatb[3]);
	float _m10 = fmVecDot(vecsa[1], transposedMatb[0]);
	float _m11 = fmVecDot(vecsa[1], transposedMatb[1]);
	float _m12 = fmVecDot(vecsa[1], transposedMatb[2]);
	float _m13 = fmVecDot(vecsa[1], transposedMatb[3]);
	float _m20 = fmVecDot(vecsa[2], transposedMatb[0]);
	float _m21 = fmVecDot(vecsa[2], transposedMatb[1]);
	float _m22 = fmVecDot(vecsa[2], transposedMatb[2]);
	float _m23 = fmVecDot(vecsa[2], transposedMatb[3]);
	float _m30 = fmVecDot(vecsa[3], transposedMatb[0]);
	float _m31 = fmVecDot(vecsa[3], transposedMatb[1]);
	float _m32 = fmVecDot(vecsa[3], transposedMatb[2]);
	float _m33 = fmVecDot(vecsa[3], transposedMatb[3]);
	ret[0] = fmLoadVec(_m00, _m01, _m02, _m03); 
	ret[1] = fmLoadVec(_m10, _m11, _m12, _m13); 
	ret[2] = fmLoadVec(_m20, _m21, _m22, _m23); 
	ret[3] = fmLoadVec(_m30, _m31, _m32, _m33); 
}

} // namespace simd
} // namespace fm
#endif // FOX_PURE

#endif // FOX_PURE_H_
