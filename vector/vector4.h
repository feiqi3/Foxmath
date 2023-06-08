#ifndef VECTOR4_H_
#define VECTOR4_H_

#include "../base/fox_avx.h"
#include "../base/fox_pure.h"
#include "../base/fox_sse.h"
#include <cmath>
#include <cstring>
#include <ostream>

namespace fm {
class vector4 {
public:
  vector4(FMFLOAT *vec) {
    std::memcpy(this->__data._v, vec, 4 * sizeof(FMFLOAT));
  }
  vector4(FMFLOAT a, FMFLOAT b, FMFLOAT c, FMFLOAT d) {
    this->__data[0] = a;
    this->__data[1] = b;
    this->__data[2] = c;
    this->__data[3] = d;
  }

  FMFLOAT &FM_CALL operator[](size_t t) { return __data._v[t]; }

  const vector4 FM_INLINE FM_CALL operator+(const vector4 &b) const noexcept {
    simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
    simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);

    simd::_fm_vec4 ret = simd::fmVecAdd(veca, vecb);
    return vector4(ret);
  }

  const vector4 FM_INLINE FM_CALL operator-(const vector4 &b) const noexcept {
    simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
    simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);

    simd::_fm_vec4 ret = simd::fmVecSub(veca, vecb);
    return vector4(ret);
  }

  const vector4 FM_INLINE FM_CALL operator*(const vector4 &b) const noexcept {
    simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
    simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
    simd::_fm_vec4 ret = simd::fmVecMul(veca, vecb);
    return vector4(ret);
  }

  const vector4 FM_INLINE FM_CALL operator/(const vector4 &b) const noexcept {
    simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
    simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
    simd::_fm_vec4 ret = simd::fmVecDiv(veca, vecb);
    return vector4(ret);
  }

  const FMFLOAT FM_INLINE FM_CALL dot(const vector4 &b) const noexcept {
    simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
    simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
    return simd::fmVecDot(veca, vecb);
  }

  const vector4 FM_INLINE FM_CALL cross(const vector4 &b) const noexcept {
    simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
    simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
    simd::_fm_vec4 ret = simd::fmVec3Cross(veca, vecb);
    return vector4(ret);
  }

  FMFLOAT FM_INLINE FM_CALL maxElement() const noexcept {
    simd::_fm_vec4 vec = simd::fmLoadVecP(__data._v);
    return simd::fmMaxElemOfVec(vec);
  }

  FMFLOAT FM_INLINE FM_CALL minElement() const noexcept {
    simd::_fm_vec4 vec = simd::fmLoadVecP(__data._v);
    return simd::fmMinElemOfVec(vec);
  }

  FMFLOAT FM_INLINE FM_CALL length() const noexcept {
    simd::_fm_vec4 vec = simd::fmLoadVecP(this->__data._v);
    FMFLOAT ff = simd::fmVecDot(vec, vec);
    return std::sqrt(ff);
  }

  vector4 FM_INLINE FM_CALL square() const noexcept {
    simd::_fm_vec4 vec = simd::fmLoadVecP(this->__data._v);
    return vector4(simd::fmVecMul(vec, vec));
  }
  vector4 FM_INLINE FM_CALL sqrt() const noexcept {
    simd::_fm_vec4 vec = simd::fmLoadVecP(this->__data._v);
    return simd::fmVecSqrt(vec);
  }

  friend const vector4 FM_INLINE FM_CALL operator*(const vector4 &a,
                                                   FMFLOAT b) noexcept;
  friend const vector4 FM_INLINE FM_CALL operator/(const vector4 &a,
                                                   FMFLOAT b) noexcept;

friend std::ostream& operator <<(std::ostream& out,const vector4& s)
	{
		out<<"("<<s.__data._v[0]<<","<<s.__data._v[1]<<","<<s.__data._v[2]<<","<<s.__data._v[3]<<")";
		return out;
	}

protected:
  vector4(const simd::fmAlignFLoat4 &in) : __data(in) {}

  vector4(const simd::_fm_vec4 &in) { simd::fmStroeVec(this->__data, in); }

private:
  simd::fmAlignFLoat4 __data;
};

const vector4 FM_INLINE FM_CALL operator*(const vector4 &a,
                                          FMFLOAT b) noexcept {
  simd::_fm_vec4 veca = simd::fmLoadVecP(a.__data._v);
  simd::_fm_vec4 ret = simd::fmVecScale(veca, b);
  return vector4(ret);
}

const vector4 FM_INLINE FM_CALL operator/(const vector4 &a,
                                          FMFLOAT b) noexcept {
  FMFLOAT inv = ((FMFLOAT)1) / b;
  return a * inv;
}

} // namespace fm

#endif