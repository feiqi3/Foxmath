#include "./matrix4x4.h"
#include "../base/fox_avx.h"
#include "../base/fox_pure.h"
#include "../base/fox_sse.h"

namespace fm {
mat4::mat4() noexcept : __data{} {}

mat4::mat4(FMFLOAT _m00, FMFLOAT _m01, FMFLOAT _m02, FMFLOAT _m03, FMFLOAT _m10,
           FMFLOAT _m11, FMFLOAT _m12, FMFLOAT _m13, FMFLOAT _m20, FMFLOAT _m21,
           FMFLOAT _m22, FMFLOAT _m23, FMFLOAT _m30, FMFLOAT _m31, FMFLOAT _m32,
           FMFLOAT _m33) noexcept
    : __data{vector4(_m00, _m01, _m02, _m03), vector4(_m10, _m11, _m12, _m13),
             vector4(_m20, _m21, _m22, _m23), vector4(_m30, _m31, _m32, _m33)} {
}

mat4::mat4(const vector4 &vec0, const vector4 &vec1, const vector4 &vec2,
           const vector4 &vec3) noexcept
    : __data{vec0, vec1, vec2, vec3} {}

mat4::mat4(const mat4 &in) {
  memcpy(this->__data, in.__data, sizeof(this->__data));
}

const vector4& FM_CALL mat4::operator[](size_t t) const noexcept {
  return __data[t];
}

vector4 &FM_CALL mat4::operator[](size_t t) noexcept { return __data[t]; }

// There are 16 xmm register under AVX-supported cpu
// and 8 xmm register under SSE-supported cpu
// So I guess it's okay
const mat4 FM_CALL mat4::operator*(const mat4 &b) const noexcept {
  simd::_fm_vec4 a0 = simd::fmLoadVecP(__data[0].__data);
  simd::_fm_vec4 a1 = simd::fmLoadVecP(__data[1].__data);
  simd::_fm_vec4 a2 = simd::fmLoadVecP(__data[2].__data);
  simd::_fm_vec4 a3 = simd::fmLoadVecP(__data[3].__data);
  simd::_fm_vec4 b0 = simd::fmLoadVec(b[0][0], b[1][0], b[2][0], b[3][0]);
  simd::_fm_vec4 b1 = simd::fmLoadVec(b[0][1], b[1][1], b[2][1], b[3][1]);
  simd::_fm_vec4 b2 = simd::fmLoadVec(b[0][2], b[1][2], b[2][2], b[3][2]);
  simd::_fm_vec4 b3 = simd::fmLoadVec(b[0][3], b[1][3], b[2][3], b[3][3]);
  FMFLOAT _m00 = simd::fmVecDot(a0, b0);
  FMFLOAT _m01 = simd::fmVecDot(a0, b1);
  FMFLOAT _m02 = simd::fmVecDot(a0, b2);
  FMFLOAT _m03 = simd::fmVecDot(a0, b3);
  FMFLOAT _m10 = simd::fmVecDot(a1, b0);
  FMFLOAT _m11 = simd::fmVecDot(a1, b1);
  FMFLOAT _m12 = simd::fmVecDot(a1, b2);
  FMFLOAT _m13 = simd::fmVecDot(a1, b3);
  FMFLOAT _m20 = simd::fmVecDot(a2, b0);
  FMFLOAT _m21 = simd::fmVecDot(a2, b1);
  FMFLOAT _m22 = simd::fmVecDot(a2, b2);
  FMFLOAT _m23 = simd::fmVecDot(a2, b3);
  FMFLOAT _m30 = simd::fmVecDot(a3, b0);
  FMFLOAT _m31 = simd::fmVecDot(a3, b1);
  FMFLOAT _m32 = simd::fmVecDot(a3, b2);
  FMFLOAT _m33 = simd::fmVecDot(a3, b3);
  return mat4(_m00, _m01, _m02, _m03, _m10, _m11, _m12, _m13, _m20, _m21, _m22,
              _m23, _m30, _m31, _m32, _m33);
}

const mat4 FM_CALL mat4::operator+(const mat4 &b) const noexcept {
  mat4 ret;
  ret.__data[0] = this->__data[0] + b.__data[0];
  ret.__data[1] = this->__data[1] + b.__data[1];
  ret.__data[2] = this->__data[2] + b.__data[2];
  ret.__data[3] = this->__data[3] + b.__data[3];
  return ret;
}

const mat4 FM_CALL mat4::operator-(const mat4 &b) const noexcept {
  mat4 ret;
  ret.__data[0] = this->__data[0] - b.__data[0];
  ret.__data[1] = this->__data[1] - b.__data[1];
  ret.__data[2] = this->__data[2] - b.__data[2];
  ret.__data[3] = this->__data[3] - b.__data[3];
  return ret;
}

mat4 FM_CALL mat4::transpose() const noexcept {
  mat4 ret;
  // Magic
  simd::fmMat4Transpose(reinterpret_cast<decltype( &(__data[0].__data))>( this->__data),
      reinterpret_cast<decltype(&(ret.__data[0].__data))>(ret.__data));
  return ret;
}

static mat4 mat4Ones({1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1});

mat4 FM_CALL mat4::identity() { return mat4Ones; }

std::ostream &operator<<(std::ostream &out, const mat4 &s) {
  out << s.__data[0] << "\n"
      << s.__data[1] << "\n"
      << s.__data[2] << "\n"
      << s.__data[3];
  return out;
}
const fm::vector4 FM_CALL operator*(const fm::vector4 &veca,
                                    const fm::mat4 &b) noexcept {
  simd::_fm_vec4 a = simd::fmLoadVecP(veca.__data);
  simd::_fm_vec4 b0 = simd::fmLoadVec(b[0][0], b[1][0], b[2][0], b[3][0]);
  simd::_fm_vec4 b1 = simd::fmLoadVec(b[0][1], b[1][1], b[2][1], b[3][1]);
  simd::_fm_vec4 b2 = simd::fmLoadVec(b[0][2], b[1][2], b[2][2], b[3][2]);
  simd::_fm_vec4 b3 = simd::fmLoadVec(b[0][3], b[1][3], b[2][3], b[3][3]);
  return vector4(simd::fmVecDot(a, b0), simd::fmVecDot(a, b1),
                 simd::fmVecDot(a, b2), simd::fmVecDot(a, b3));
}
const fm::vector4 FM_CALL operator*(const fm::mat4 &mata,
                                    const fm::vector4 &vecb) noexcept {
  simd::_fm_vec4 a = simd::fmLoadVecP(vecb.__data);
  simd::_fm_vec4 b0 = simd::fmLoadVecP(mata.__data[0].__data);
  simd::_fm_vec4 b1 = simd::fmLoadVecP(mata.__data[1].__data);
  simd::_fm_vec4 b2 = simd::fmLoadVecP(mata.__data[2].__data);
  simd::_fm_vec4 b3 = simd::fmLoadVecP(mata.__data[3].__data);
  return vector4(simd::fmVecDot(a, b0), simd::fmVecDot(a, b1),
                 simd::fmVecDot(a, b2), simd::fmVecDot(a, b3));
}

const mat4 FM_CALL mat4::operator*(FMFLOAT b) const FMTHROW {
  mat4 ret{this->__data[0] * b, this->__data[1] * b, this->__data[2] * b,
           this->__data[3] * b};
  return ret;
}

const fm::mat4 FM_CALL operator*(FMFLOAT a, const fm::mat4 &matb) FMTHROW {
  return matb * a;
}

FMFLOAT FM_CALL mat4::determinant() const FMTHROW {
  mat4 _U;
  U(&_U);
  return (_U)[0][0] * (_U)[1][1] * (_U)[2][2] * (_U)[3][3];
}

void mat4::LU(mat4 *outL, mat4 *outU) const FMTHROW {
  vector4 Row0 = (*this)[0];
  vector4 Row1 = (*this)[1];
  FMFLOAT r1Factor = Row1[0] / Row0[0];
  Row1 = Row1 - Row0 * r1Factor;

  auto Row2 = (*this)[2];
  FMFLOAT r20Factor = Row2[0] / Row0[0];
  Row2 = Row2 - Row0 * r20Factor;
  FMFLOAT r21Factor = Row2[1] / Row1[1];
  Row2 = Row2 - Row1 * r21Factor;

  auto Row3 = (*this)[3];
  FMFLOAT r30Factor = Row3[0] / Row0[0];
  Row3 = Row3 - r30Factor * Row0;
  FMFLOAT r31Factor = Row3[1] / Row1[1];
  Row3 = Row3 - r31Factor * Row1;
  FMFLOAT r32Factor = Row3[2] / Row2[2];
  Row3 = Row3 - r32Factor * Row2;

/*   auto Row4 = (*this)[4];
  FMFLOAT r40Factor = Row4[0] / Row0[0];
  Row4 = Row4 - r30Factor * Row0;
  FMFLOAT r41Factor = Row4[1] / Row1[1];
  Row4 = Row4 - r41Factor * Row1;
  FMFLOAT r42Factor = Row4[2] / Row2[2];
  Row4 = Row4 - r42Factor * Row2;
  FMFLOAT r43Factor = Row4[3] / Row3[3];
  Row4 = Row4 - r43Factor * Row3; */

  *outL = mat4(mat4Ones);
  (*outL)[1][0] = r1Factor;
  (*outL)[2][0] = r20Factor;
  (*outL)[2][1] = r21Factor;
  (*outL)[3][0] = r30Factor;
  (*outL)[3][1] = r31Factor;
  (*outL)[3][2] = r32Factor;
/*   (*outL)[4][0] = r40Factor;
  (*outL)[4][1] = r41Factor;
  (*outL)[4][2] = r42Factor;
  (*outL)[4][3] = r43Factor; */
  *outU = mat4(Row0, Row1, Row2, Row3);
  return;
}

void mat4::U(mat4 *out) const FMTHROW {
  vector4 Row0 = (*this)[0];
  vector4 Row1 = (*this)[1];
  FMFLOAT r1Factor = Row1[0] / Row0[0];
  Row1 = Row1 - Row0 * r1Factor;

  auto Row2 = (*this)[2];
  FMFLOAT r20Factor = Row2[0] / Row0[0];
  Row2 = Row2 - Row0 * r20Factor;
  FMFLOAT r21Factor = Row2[1] / Row1[1];
  Row2 = Row2 - Row1 * r21Factor;

  auto Row3 = (*this)[3];
  FMFLOAT r30Factor = Row3[0] / Row0[0];
  Row3 = Row3 - r30Factor * Row0;
  FMFLOAT r31Factor = Row3[1] / Row1[1];
  Row3 = Row3 - r31Factor * Row1;
  FMFLOAT r32Factor = Row3[2] / Row2[2];
  Row3 = Row3 - r32Factor * Row2;

  auto Row4 = (*this)[4];
  FMFLOAT r40Factor = Row4[0] / Row0[0];
  Row4 = Row4 - r30Factor * Row0;
  FMFLOAT r41Factor = Row4[1] / Row1[1];
  Row4 = Row4 - r41Factor * Row1;
  FMFLOAT r42Factor = Row4[2] / Row2[2];
  Row4 = Row4 - r42Factor * Row2;
  FMFLOAT r43Factor = Row4[3] / Row3[3];
  Row4 = Row4 - r43Factor * Row3;

  *out = mat4(Row0, Row1, Row2, Row3);
}

static const fm::mat4 ZEROS{vector4(), vector4(), vector4(), vector4()};

mat4 FM_CALL mat4::inverse() const FMTHROW {
  mat4 L, U;
  LU(&L, &U);

  mat4 InvL = identity();
  InvL[1][0] = -(L)[1][0];

  InvL[2][0] = -(L)[2][0];
  InvL[2] = InvL[2] - (L)[2][1] * InvL[1];

  InvL[3][0] = -(L)[3][0];
  InvL[3] = InvL[3] - (L)[3][1] * InvL[1] - (L)[3][2] * InvL[2];

  mat4 InvU = identity();
  InvU[3][3] /= (U)[3][3];
  InvU[2][3] = -InvU[3][3] * (U)[2][3];
  InvU[2] = InvU[2] / (U)[2][2];

  InvU[1][3] = -InvU[3][3] * (U)[1][3];
  InvU[1] = (InvU[1] - (U)[1][2] * InvU[2]) / (U)[1][1];

  InvU[0][3] = -InvU[3][3] * (U)[0][3];
  InvU[0] = (InvU[0] - (U)[0][1]*InvU[1] - (U)[0][2]*InvU[2])/(U)[0][0];
  return InvU  * InvL;
}

mat4 FM_CALL mat4::zeros() { return ZEROS; }
} // namespace fm