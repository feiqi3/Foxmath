#include "vector4.h"
#include "../base/fox_avx.h"
#include "../base/fox_pure.h"
#include "../base/fox_sse.h"
#include "vector3.h"

#include <cmath>
namespace fm {
vector4::vector4(FMFLOAT *vec) {
  std::memcpy(this->__data._v, vec, 4 * sizeof(FMFLOAT));
}

vector4::vector4() FMTHROW : __data{0, 0, 0, 0} {}

vector4::vector4(FMFLOAT a) FMTHROW : __data{a, a, a, a} {}

vector4::vector4(const vector4 &in) {
  memcpy(this->__data._v, in.__data._v, sizeof(__data));
}

vector4::vector4(const vector3 &in) FMTHROW {
  memcpy(this->__data._v, in.__data._v, 4 * sizeof(FMFLOAT));
}

FMFLOAT &FM_CALL vector4::operator[](size_t t) FMTHROW {
#ifdef FM_DEBUG
  assert(t <= 3 && t >= 0);
#endif // FM_DEBUG

  return __data._v[t];
}

const FMFLOAT &FM_CALL vector4::operator[](size_t t) const FMTHROW {
#ifdef FM_DEBUG
  assert(t <= 3 && t >= 0);
#endif // FM_DEBUG
  return __data._v[t];
}

vector4::vector4(FMFLOAT a, FMFLOAT b, FMFLOAT c, FMFLOAT d) FMTHROW
    : __data{a, b, c, d} {}

const vector4 FM_CALL vector4::operator+(const vector4 &b) const FMTHROW {
  simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
  simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
  simd::_fm_vec4 ret = simd::fmVecAdd(veca, vecb);
  vector4 retVec;
  fmStoreVec(retVec.__data, ret);
  return retVec;
}

const vector4 FM_CALL vector4::operator-(const vector4 &b) const FMTHROW {
  simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
  simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);

  simd::_fm_vec4 ret = simd::fmVecSub(veca, vecb);
  vector4 retVec;
  fmStoreVec(retVec.__data, ret);
  return retVec;
}

const vector4 FM_CALL vector4::operator-() const FMTHROW {
  auto ret = fm::simd::fmLoadVecP(__data._v);
  ret = simd::fmVecUnaryMinus(ret);
  vector4 retVec;
  fmStoreVec(retVec.__data, ret);
  return retVec;
}

const vector4 FM_CALL vector4::operator*(const vector4 &b) const FMTHROW {
  simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
  simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
  simd::_fm_vec4 ret = simd::fmVecMul(veca, vecb);
  vector4 retVec;
  fmStoreVec(retVec.__data, ret);
  return retVec;
}

const vector4 FM_CALL vector4::operator/(const vector4 &b) const FMTHROW {
  simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
  simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
  simd::_fm_vec4 ret = simd::fmVecDiv(veca, vecb);
  vector4 retVec;
  fmStoreVec(retVec.__data, ret);
  return retVec;
}

const FMFLOAT FM_CALL vector4::dot(const vector4 &b) const FMTHROW {
  simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
  simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
  return simd::fmVecDot(veca, vecb);
}

const vector4 FM_CALL vector4::cross(const vector4 &b) const FMTHROW {
  simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
  simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
  simd::_fm_vec4 ret = simd::fmVec3Cross(veca, vecb);
  vector4 retVec;
  fmStoreVec(retVec.__data, ret);
  return retVec;
}

FMFLOAT FM_CALL vector4::maxElement() const FMTHROW {
  simd::_fm_vec4 vec = simd::fmLoadVecP(__data._v);
  return simd::fmMaxElemOfVec(vec);
}

FMFLOAT FM_CALL vector4::minElement() const FMTHROW {
  simd::_fm_vec4 vec = simd::fmLoadVecP(__data._v);
  return simd::fmMinElemOfVec(vec);
}

FMFLOAT FM_CALL vector4::length() const FMTHROW {
  simd::_fm_vec4 vec = simd::fmLoadVecP(this->__data._v);
  FMFLOAT ff = simd::fmVecDot(vec, vec);
  return std::sqrt(ff);
}

vector4 FM_CALL vector4::square() const FMTHROW {
  simd::_fm_vec4 vec = simd::fmLoadVecP(this->__data._v);
  auto ret = (simd::fmVecMul(vec, vec));
  vector4 retVec;
  fmStoreVec(retVec.__data, ret);
  return retVec;
}

vector4 FM_CALL vector4::sqrt() const FMTHROW {
  simd::_fm_vec4 vec = simd::fmLoadVecP(this->__data._v);
  auto ret = simd::fmVecSqrt(vec);
  vector4 retVec;
  fmStoreVec(retVec.__data, ret);
  return retVec;
}

vector4::vector4(const simd::fmAlignFLoat4 &in) : __data(in) {}

std::ostream &operator<<(std::ostream &out, const vector4 &s) {
  out << "(" << s.__data._v[0] << "," << s.__data._v[1] << "," << s.__data._v[2]
      << "," << s.__data._v[3] << ")";
  return out;
}

const vector4 FM_CALL operator*(const vector4 &a, FMFLOAT b) FMTHROW {
  simd::_fm_vec4 veca = simd::fmLoadVecP(a.__data._v);
  simd::_fm_vec4 ret = simd::fmVecScale(veca, b);
  vector4 retVec;
  fmStoreVec(retVec.__data, ret);
  return retVec;
}

const vector4 FM_CALL operator/(const vector4 &a, FMFLOAT b) FMTHROW {
  FMFLOAT inv = ((FMFLOAT)1) / b;
  return a * inv;
}

const vector4 FM_CALL operator*(FMFLOAT b, const vector4 &a) FMTHROW {
  return a * b;
}

bool FM_CALL hasNan(const vector4 &in) FMTHROW {
  return std::isnan(in[0]) || std::isnan(in[1]) || std::isnan(in[2]) ||
         std::isnan(in[3]);
}

static const vector4 ONE{1, 1, 1, 1};
static const vector4 RIGHT{1, 0, 0, 0};
static const vector4 LEFT = -RIGHT;
static const vector4 UP{0, 1, 0, 0};
static const vector4 DOWN = -UP;
static const vector4 FORWARD{0, 0, 1, 0};
static const vector4 BACK = -FORWARD;

vector4 FM_CALL vector4::ones() FMTHROW { return ONE; }
vector4 FM_CALL vector4::right() FMTHROW { return RIGHT; }
vector4 FM_CALL vector4::left() FMTHROW { return LEFT; }
vector4 FM_CALL vector4::up() FMTHROW { return UP; }
vector4 FM_CALL vector4::down() FMTHROW { return DOWN; }
vector4 FM_CALL vector4::forward() FMTHROW { return FORWARD; }
vector4 FM_CALL vector4::back() FMTHROW { return BACK; }

FMFLOAT &FM_CALL vector4::x() FMTHROW { return __data[0]; }
FMFLOAT &FM_CALL vector4::y() FMTHROW { return __data[1]; }
FMFLOAT &FM_CALL vector4::z() FMTHROW { return __data[2]; }
FMFLOAT &FM_CALL vector4::w() FMTHROW { return __data[3]; }

void FM_CALL vector4::normalize() FMTHROW {
  auto t = this->length();
  auto x = simd::fmLoadVecP(this->__data._v);
  x = simd::fmVecScale(x, 1. / t);
  simd::fmStoreVec(__data, x);
}
} // namespace fm