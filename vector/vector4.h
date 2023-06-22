#ifndef VECTOR4_H_
#define VECTOR4_H_

#include "../base/basic_def.h"
#include <cmath>
#include <cstring>
#include <initializer_list>
#include <ostream>

namespace fm {

class vector3;
class mat4;

class vector4 {
public:
  vector4() FMTHROW;
  vector4(const std::initializer_list<FMFLOAT> &list);
  vector4(FMFLOAT *vec);
  vector4(FMFLOAT a, FMFLOAT b, FMFLOAT c, FMFLOAT d) FMTHROW;
  explicit vector4(FMFLOAT a) FMTHROW;
  vector4(const vector4 &in);

  friend class vector3;

  vector4(const vector3 &in) FMTHROW;
  FMFLOAT &FM_CALL operator[](size_t t) FMTHROW;

   FMFLOAT &FM_CALL x() FMTHROW;
   FMFLOAT &FM_CALL y() FMTHROW;
   FMFLOAT &FM_CALL z() FMTHROW;
   FMFLOAT &FM_CALL w() FMTHROW;


  const FMFLOAT &FM_CALL operator[](size_t t) const FMTHROW;

  const vector4 FM_CALL operator+(const vector4 &b) const FMTHROW;

  const vector4 FM_CALL operator-(const vector4 &b) const FMTHROW;

  const vector4 FM_CALL operator-() const FMTHROW;

  const vector4 FM_CALL operator*(const vector4 &b) const FMTHROW;

  const vector4 FM_CALL operator/(const vector4 &b) const FMTHROW;

  const FMFLOAT FM_CALL dot(const vector4 &b) const FMTHROW;

  // There's an interesting thing I just realized
  // Cross product is not coordinate system related.
  // In the right hand system, right-hand rule should Be used.
  // Vice versa, Left-hand rule should be used in left-hand system.
  const vector4 FM_CALL cross(const vector4 &b) const FMTHROW;

  FMFLOAT FM_CALL maxElement() const FMTHROW;

  FMFLOAT FM_CALL minElement() const FMTHROW;

  FMFLOAT FM_CALL length() const FMTHROW;

  vector4 FM_CALL square() const FMTHROW;

  vector4 FM_CALL sqrt() const FMTHROW;

  // constants
  static FM_CALL vector4 ones() FMTHROW;
  static FM_CALL vector4 right() FMTHROW;
  static FM_CALL vector4 left() FMTHROW;
  static FM_CALL vector4 up() FMTHROW;
  static FM_CALL vector4 down() FMTHROW;
  static FM_CALL vector4 forward() FMTHROW;
  static FM_CALL vector4 back() FMTHROW;

  friend const vector4 FM_CALL operator*(const vector4 &a, FMFLOAT b) FMTHROW;
  friend const vector4 FM_CALL operator/(const vector4 &a, FMFLOAT b) FMTHROW;

  friend vector4 FM_CALL clamp(const vector4 &a, const vector4 &max,
                               const vector4 &min) FMTHROW;

  friend std::ostream &operator<<(std::ostream &out, const vector4 &s);

  friend class mat4;

  friend const vector4 FM_CALL operator*(const vector4 &veca,
                                         const mat4 &matb) FMTHROW;

  friend const vector4 FM_CALL operator*(const mat4 &mata,
                                         const vector4 &vecb) FMTHROW;

  friend FM_CALL vector4 abs(const vector4 &vec) FMTHROW;

protected:
  vector4(const simd::fmAlignFLoat4 &in);

protected:
  simd::fmAlignFLoat4 __data;
};

const vector4 FM_CALL operator*(const vector4 &a, FMFLOAT b) FMTHROW;

const vector4 FM_CALL operator*(FMFLOAT b, const vector4 &a) FMTHROW;

const vector4 FM_CALL operator/(const vector4 &a, FMFLOAT b) FMTHROW;

std::ostream &operator<<(std::ostream &out, const vector4 &s);

bool FM_CALL hasNan(const vector4 &in) FMTHROW;

} // namespace fm

#endif