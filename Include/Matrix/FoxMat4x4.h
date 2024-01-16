#ifndef MATRIX_4X4_H_
#define MATRIX_4X4_H_
#include "../Vector/FoxVec4.h"
namespace fm {

class mat4 :public VecBase{
public:
  mat4() FMTHROW;
  mat4(const std::initializer_list<FMFLOAT> &in);
  mat4(FMFLOAT _m00, FMFLOAT _m01, FMFLOAT _m02, FMFLOAT _m03, FMFLOAT _m10,
       FMFLOAT _m11, FMFLOAT _m12, FMFLOAT _m13, FMFLOAT _m20, FMFLOAT _m21,
       FMFLOAT _m22, FMFLOAT _m23, FMFLOAT _m30, FMFLOAT _m31, FMFLOAT _m32,
       FMFLOAT _m33) FMTHROW;
  mat4(const vector4 &vec0, const vector4 &vec1, const vector4 &vec2,
       const vector4 &vec3) FMTHROW;

  mat4(const mat4 &in);

  const vector4 FM_CALL operator[](size_t t) const FMTHROW;

  vector4 &FM_CALL operator[](size_t t) FMTHROW;

  const mat4 FM_CALL operator*(const mat4 &b) const FMTHROW;

  const mat4 FM_CALL operator*(FMFLOAT b) const FMTHROW;

  const mat4 FM_CALL operator+(const mat4 &b) const FMTHROW;

  const mat4 FM_CALL operator-(const mat4 &b) const FMTHROW;

  mat4 FM_CALL inverse() const FMTHROW;

  mat4 FM_CALL transpose() const FMTHROW;

  FMFLOAT FM_CALL determinant() const FMTHROW; 

  void LU(mat4 *outL, mat4 *outU) const FMTHROW;
  
  void U(mat4*out)const FMTHROW;

  static mat4 FM_CALL identity();

  static mat4 FM_CALL zeros();

  friend std::ostream &operator<<(std::ostream &out, const mat4 &s);

  friend const fm::vector4 FM_CALL operator*(const fm::mat4 &mata,
                                             const fm::vector4 &vecb) FMTHROW;

private:
  fm::vector4 __data[4];
};

const fm::vector4 FM_CALL operator*(const fm::vector4 &veca,
                                    const fm::mat4 &matb) FMTHROW;

const fm::vector4 FM_CALL operator*(const fm::mat4 &mata,
                                    const fm::vector4 &vecb) FMTHROW;

const fm::mat4 FM_CALL operator*(FMFLOAT a, const fm::mat4 &matb) FMTHROW;

} // namespace fm

#endif
