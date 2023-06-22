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

vector4 &FM_CALL mat4::operator[](size_t t) noexcept { return __data[t]; }

const vector4 &FM_CALL mat4::operator[](size_t t) const noexcept {
  return __data[t];
}

// There are 16 xmm register under AVX-supported cpu
// and 8 xmm register under SSE-supported cpu
// So I guess it's okay
const mat4 FM_CALL mat4::operator*(const mat4 &b) const noexcept {
  simd::_fm_vec4 a0 = simd::fmLoadVecP(__data[0].__data._v);
  simd::_fm_vec4 a1 = simd::fmLoadVecP(__data[1].__data._v);
  simd::_fm_vec4 a2 = simd::fmLoadVecP(__data[2].__data._v);
  simd::_fm_vec4 a3 = simd::fmLoadVecP(__data[3].__data._v);
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

// TODO: simd function support
mat4 FM_CALL mat4::transpose() const noexcept {
  mat4 ret;
  // Magic
  simd::fmMat4Transpose((simd::fmAlignFLoat4 *)this->__data,
                        (simd::fmAlignFLoat4 *)ret.__data);
  return ret;
}

static mat4 mat4Ones({1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1});

mat4 FM_CALL mat4::identity() { return mat4Ones; }

mat4::mat4(const std::initializer_list<FMFLOAT> &in) {
#if defined(FM_DEBUG)
  assert(in.size() == 16);
#endif
  auto lp = in.begin();
  for (char i = 0; i < 3; i++) {
    for (char j = 0; j < 3; j++, ++lp) {
      __data[i][j] = *lp;
    }
  }
}
std::ostream &operator<<(std::ostream &out, const mat4 &s) {
  out << s.__data[0] << "\n"
      << s.__data[1] << "\n"
      << s.__data[2] << "\n"
      << s.__data[3];
  return out;
}
const fm::vector4 FM_CALL operator*(const fm::vector4 &veca,
                                    const fm::mat4 &b) noexcept {
  simd::_fm_vec4 a = simd::fmLoadVecP(veca.__data._v);
  simd::_fm_vec4 b0 = simd::fmLoadVec(b[0][0], b[1][0], b[2][0], b[3][0]);
  simd::_fm_vec4 b1 = simd::fmLoadVec(b[0][1], b[1][1], b[2][1], b[3][1]);
  simd::_fm_vec4 b2 = simd::fmLoadVec(b[0][2], b[1][2], b[2][2], b[3][2]);
  simd::_fm_vec4 b3 = simd::fmLoadVec(b[0][3], b[1][3], b[2][3], b[3][3]);
  return vector4(simd::fmVecDot(a, b0), simd::fmVecDot(a, b1),
                 simd::fmVecDot(a, b2), simd::fmVecDot(a, b3));
}
const fm::vector4 FM_CALL operator*(const fm::mat4 &mata,
                                    const fm::vector4 &vecb) noexcept {
  simd::_fm_vec4 a = simd::fmLoadVecP(vecb.__data._v);
  simd::_fm_vec4 b0 = simd::fmLoadVecP(mata.__data[0].__data._v);
  simd::_fm_vec4 b1 = simd::fmLoadVecP(mata.__data[1].__data._v);
  simd::_fm_vec4 b2 = simd::fmLoadVecP(mata.__data[2].__data._v);
  simd::_fm_vec4 b3 = simd::fmLoadVecP(mata.__data[3].__data._v);
  return vector4(simd::fmVecDot(a, b0), simd::fmVecDot(a, b1),
                 simd::fmVecDot(a, b2), simd::fmVecDot(a, b3));
}

const mat4 FM_CALL mat4::operator*(FMFLOAT b) const FMTHROW {
  mat4 ret{this->__data[0] * b, this->__data[1] * b, this->__data[2] * b,
           this->__data[3] * b};
  return ret;
}

const fm::mat4 FM_CALL operator*(FMFLOAT a, const fm::mat4 &matb) FMTHROW{
	return matb * a;
}

static const fm::mat4 ZEROS{vector4(), vector4(), vector4(), vector4()};

mat4 FM_CALL mat4::zeros() { return ZEROS; }
} // namespace fm