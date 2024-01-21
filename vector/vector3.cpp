#include "vector3.h"
#include "../base/fox_avx.h"
#include "../base/fox_pure.h"
#include "../base/fox_sse.h"
#include <cmath>
#include <ios>
#include <limits>

namespace fm {
fm::vector3::vector3() FMTHROW : __data({0, 0, 0, 0}) {}

fm::vector3::vector3(FMFLOAT a, FMFLOAT b, FMFLOAT c) FMTHROW
    : __data{a, b, c, 0} {}

fm::vector3::vector3(const FMFLOAT *in) {
  memcpy(__data._v, in, 3 * sizeof(FMFLOAT));
  __data._v[3] = 0;
}

vector3::vector3(const simd::fmAlignFLoat4 &in) {
  memcpy(this->__data._v, in._v, 4 * sizeof(FMFLOAT));
  __data._v[3] = 0;
}

fm::vector3::vector3(const fm::vector3 &in) FMTHROW {
  memcpy(this->__data._v, in.__data._v, 3 * sizeof(FMFLOAT));
}

FMFLOAT &FM_CALL vector3::operator[](size_t t) FMTHROW {
#ifdef FM_DEBUG
  assert(t <= 2 && t >= 0);
#endif // FM_DEBUG
  return __data._v[t];
}

std::ostream &operator<<(std::ostream &out, const vector3 &s) {
  out << "(" << s.__data._v[0] << "," << s.__data._v[1] << "," << s.__data._v[2]
      << ")";
  return out;
}

const FMFLOAT &FM_CALL vector3::operator[](size_t t) const FMTHROW {
#ifdef FM_DEBUG
  assert(t <= 2 && t >= 0);
#endif // FM_DEBUG
  return __data._v[t];
}

const vector3 FM_CALL vector3::operator+(const vector3 &b) const FMTHROW {
  simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
  simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
  simd::_fm_vec4 ret = simd::fmVecAdd(veca, vecb);
  vector3 retVec;
  fmStoreVec(retVec.__data, ret);
  return retVec;
}

const vector3 FM_CALL vector3::operator-(const vector3 &b) const FMTHROW {
  simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
  simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);

  simd::_fm_vec4 ret = simd::fmVecSub(veca, vecb);
  vector3 retVec;
  fmStoreVec(retVec.__data, ret);
  return retVec;
}

const vector3 FM_CALL vector3::operator-() const FMTHROW {
  auto ret = fm::simd::fmLoadVecP(__data._v);
  ret = simd::fmVecUnaryMinus(ret);
  vector3 retVec;
  fmStoreVec(retVec.__data, ret);
  return retVec;
}

const vector3 FM_CALL vector3::operator*(const vector3 &b) const FMTHROW {
  simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
  simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
  simd::_fm_vec4 ret = simd::fmVecMul(veca, vecb);
  vector3 retVec;
  fmStoreVec(retVec.__data, ret);
  return retVec;
}

const vector3 FM_CALL vector3::operator/(const vector3 &b) const FMTHROW {
  simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
  simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
  simd::_fm_vec4 ret = simd::fmVecDiv(veca, vecb);
  vector3 retVec;
  fmStoreVec(retVec.__data, ret);
  return retVec;
}

const FMFLOAT FM_CALL vector3::dot(const vector3 &b) const FMTHROW {
#ifdef FM_DEBUG
  assert(__data._v[3] == 0 && b.__data._v[3] == 0);
#endif // FM_DEBUG

  simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
  simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
  return simd::fmVecDot(veca, vecb);
}

const vector3 FM_CALL vector3::cross(const vector3 &b) const FMTHROW {
  simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
  simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
  simd::_fm_vec4 ret = simd::fmVec3Cross(veca, vecb);
  vector3 retVec;
  fmStoreVec(retVec.__data, ret);
  return retVec;
}

FMFLOAT FM_CALL vector3::maxElement() const FMTHROW {
  simd::_fm_vec4 vec = simd::fmLoadVec(__data._v[0], __data._v[1], __data._v[2],
                                       std::numeric_limits<FMFLOAT>::min());
  return simd::fmMaxElemOfVec(vec);
}

FMFLOAT FM_CALL vector3::minElement() const FMTHROW {
  simd::_fm_vec4 vec = simd::fmLoadVec(__data._v[0], __data._v[1], __data._v[2],
                                       std::numeric_limits<FMFLOAT>::max());
  return simd::fmMinElemOfVec(vec);
}

FMFLOAT FM_CALL vector3::length() const FMTHROW {
#ifdef FM_DEBUG
  assert(__data._v[3] == 0);
#endif // FM_DEBUG
  simd::_fm_vec4 vec = simd::fmLoadVecP(this->__data._v);
  FMFLOAT ff = simd::fmVecDot(vec, vec);
  return std::sqrt(ff);
}

vector3 FM_CALL vector3::square() const FMTHROW {
  simd::_fm_vec4 vec = simd::fmLoadVecP(this->__data._v);
  auto ret = (simd::fmVecMul(vec, vec));
  vector3 retVec;
  fmStoreVec(retVec.__data, ret);
  return retVec;
}

vector3 FM_CALL vector3::sqrt() const FMTHROW {
#ifdef FM_DEBUG
  assert(__data._v[3] == 0);
#endif // FM_DEBUG
  simd::_fm_vec4 vec = simd::fmLoadVecP(this->__data._v);
  auto ret = simd::fmVecSqrt(vec);
  vector3 retVec;
  fmStoreVec(retVec.__data, ret);
  return retVec;
}

const vector3 FM_CALL operator*(const vector3 &a, FMFLOAT b) FMTHROW {
  simd::_fm_vec4 veca = simd::fmLoadVecP(a.__data._v);
  simd::_fm_vec4 ret = simd::fmVecScale(veca, b);
  vector3 retVec;
  fmStoreVec(retVec.__data, ret);
  return retVec;
}

const vector3 FM_CALL operator/(const vector3 &a, FMFLOAT b) FMTHROW {
  FMFLOAT inv = ((FMFLOAT)1) / b;
  return a * inv;
}

const vector3 FM_CALL operator*(FMFLOAT b, const vector3 &a) FMTHROW {
  return a * b;
}

bool FM_CALL hasNan(const vector3 &in) FMTHROW {
  return std::isnan(in[0]) || std::isnan(in[1]) || std::isnan(in[2]);
}
static const vector3 ONE{1, 1, 1};
static const vector3 RIGHT{1, 0, 0};
static const vector3 LEFT = -RIGHT;
static const vector3 UP{0, 1, 0};
static const vector3 DOWN = -UP;
static const vector3 FORWARD{0, 0, 1};
static const vector3 BACK = -FORWARD;

vector3 FM_CALL vector3::ones() FMTHROW { return ONE; }
vector3 FM_CALL vector3::right() FMTHROW { return RIGHT; }
vector3 FM_CALL vector3::left() FMTHROW { return LEFT; }
vector3 FM_CALL vector3::up() FMTHROW { return UP; }
vector3 FM_CALL vector3::down() FMTHROW { return DOWN; }
vector3 FM_CALL vector3::forward() FMTHROW { return FORWARD; }
vector3 FM_CALL vector3::back() FMTHROW { return BACK; }

FMFLOAT &FM_CALL vector3::x() FMTHROW { return __data[0]; }
FMFLOAT &FM_CALL vector3::y() FMTHROW { return __data[1]; }
FMFLOAT &FM_CALL vector3::z() FMTHROW { return __data[2]; }

void FM_CALL fm::vector3::normalize() FMTHROW {
	auto t = this->length();
	auto x = simd::fmLoadVecP(this->__data._v);
	x = simd::fmVecScale(x, 1./t);
	simd::fmStoreVec(__data, x);
}

} // namespace fm