#include "transform.h"

#include "../matrix/matrix4x4.h"
#include "../vector/vector3.h"
#include "../vector/vector4.h"
#include "operation.h"
#include <cmath>
#include <cstdlib>
#include <limits>

static constexpr FMFLOAT BIAS = 30 * std::numeric_limits<FMFLOAT>::min();

template <typename VecType>
static bool FM_FORCE_INLINE isNormalized(const VecType &t) FMTHROW {
  return std::abs(t.length() - 1) < BIAS;
}

namespace fm {

fm::mat4 FM_CALL translate(const fm::vector3 &vector) FMTHROW {
  mat4 tmp = mat4::identity();
  tmp[0][3] = vector[0];
  tmp[1][3] = vector[1];
  tmp[2][3] = vector[2];
  return tmp;
}

fm::mat4 FM_CALL scale(const fm::vector3 &vector) FMTHROW {
  mat4 tmp = mat4::identity();
  tmp[0][0] *= vector[0];
  tmp[1][1] *= vector[1];
  tmp[2][2] *= vector[2];
  return tmp;
}

// Right hand system for default
// For left hand system should use -theta instead of theta.
// https://mathworld.wolfram.com/RodriguesRotationFormula.html
fm::mat4 FM_CALL rotate(const fm::vector3 &axis, FMFLOAT angle) FMTHROW {
#if defined(FM_DEBUG)
  // Axis vector should be normalized.
  assert(isNormalized(axis));
#endif

  mat4 wtilde = mat4::zeros();
  wtilde[3] = vector4(0, 0, 0, 1);
  wtilde[0][1] = -axis[2];
  wtilde[0][2] = axis[1];
  wtilde[1][0] = axis[2];
  wtilde[1][2] = -axis[0];
  wtilde[2][0] = -axis[1];
  wtilde[2][1] = axis[0];

  mat4 ret = mat4::identity() + wtilde * std::sin(angle) +
             wtilde * wtilde * (FMFLOAT(1) - std::cos(angle));
  return ret;
}

// This version may have a bad performance
/*
fm::mat4 FM_CALL rotate(const fm::mat4 &in, const fm::vector3 &w,
                        FMFLOAT theta) {
#if defined(FM_DEBUG)
  // Axis vector should be normalized.
  assert(isNormalized(axis));
#endif
  FMFLOAT cosTheta = std::cos(theta);
  FMFLOAT OneSubCosTheta = FMFLOAT(1) - cosTheta;
  FMFLOAT SinTheta = std::sin(theta);
  mat4 ret{vector4(                                            //
               cosTheta + w[0] * w[0] * OneSubCosTheta,        //
               w[0] * w[1] * OneSubCosTheta - w[2] * SinTheta, //
               w[1] * SinTheta + w[0] * w[2] * OneSubCosTheta, //
               0),
           vector4(                                             //
               w[2] * SinTheta + w[0] * w[1] * OneSubCosTheta,  //
               cosTheta + w[1] * w[1] * OneSubCosTheta,         //
               -w[0] * SinTheta + w[1] * w[2] * OneSubCosTheta, //
               0),
           vector4(                                             //
               -w[1] * SinTheta + w[0] * w[2] * OneSubCosTheta, //
               w[0] * SinTheta + w[1] * w[2] * OneSubCosTheta,  //
               cosTheta + w[2] * w[2] * OneSubCosTheta,         //
               0),
           vector4(0, 0, 0, 1)};
  return ret * in;
}
*/

fm::mat4 FM_CALL rotateX_LH(FMFLOAT angle) FMTHROW {
  mat4 tmp = mat4::identity();
  auto cosTheta = Cos(angle);
  auto sinTheta = Sin(angle);
  tmp[1][1] = cosTheta;
  tmp[1][2] = -sinTheta;
  tmp[2][1] = sinTheta;
  tmp[2][2] = cosTheta;
  return tmp;
}

fm::mat4 FM_CALL rotateY_LH(FMFLOAT angle) FMTHROW {
  mat4 tmp = mat4::identity();
  auto cosTheta = Cos(angle);
  auto sinTheta = Sin(angle);
  tmp[0][0] = cosTheta;
  tmp[0][2] = sinTheta;
  tmp[2][0] = -sinTheta;
  tmp[2][2] = cosTheta;
  return tmp;
}

fm::mat4 FM_CALL rotateZ_LH(FMFLOAT angle) FMTHROW {
  mat4 tmp = mat4::identity();
  auto cosTheta = Cos(angle);
  auto sinTheta = Sin(angle);
  tmp[0][0] = cosTheta;
  tmp[0][1] = -sinTheta;
  tmp[1][0] = sinTheta;
  tmp[1][1] = cosTheta;
  return tmp;
}

fm::mat4 FM_CALL rotateX_RH(FMFLOAT angle) FMTHROW {
  mat4 tmp = mat4::identity();
  auto cosTheta = Cos(angle);
  auto sinTheta = Sin(angle);
  tmp[1][1] = cosTheta;
  tmp[1][2] = sinTheta;
  tmp[2][1] = -sinTheta;
  tmp[2][2] = cosTheta;
  return tmp;
}

fm::mat4 FM_CALL rotateY_RH(FMFLOAT angle) FMTHROW {
  mat4 tmp = mat4::identity();
  auto cosTheta = Cos(angle);
  auto sinTheta = Sin(angle);
  tmp[0][0] = cosTheta;
  tmp[0][2] = -sinTheta;
  tmp[2][0] = sinTheta;
  tmp[2][2] = cosTheta;
  return tmp;
}

fm::mat4 FM_CALL rotateZ_RH(FMFLOAT angle) FMTHROW {
  mat4 tmp = mat4::identity();
  auto cosTheta = Cos(angle);
  auto sinTheta = Sin(angle);
  tmp[0][0] = cosTheta;
  tmp[0][1] = sinTheta;
  tmp[1][0] = -sinTheta;
  tmp[1][1] = cosTheta;
  return tmp;
}

FMFLOAT dot(const vector3 &a, const vector3 &b) { return a.dot(b); }

FMFLOAT dot(const vector4 &a, const vector4 &b) { return a.dot(b); }

vector3 cross(const vector3 &a, const vector3 &b) { return a.cross(b); }

vector4 cross(const vector4 &a, const vector4 &b) { return a.cross(b); }

vector4 normalize(const vector4 &a) { return a / a.length(); }

vector3 normalize(const vector3 &a) { return a / a.length(); }

fm::mat4 FM_CALL lookAtRH(const vector3 &eye, const vector3 &center,
                          const vector3 &up) {
  vector3 f(normalize(center - eye));
  vector3 s(normalize(cross(f, up)));
  vector3 u(cross(s, f));
  mat4 Result = mat4::identity();
  Result[0][0] = s.x();
  Result[0][1] = s.y();
  Result[0][2] = s.z();
  Result[1][0] = u.x();
  Result[1][1] = u.y();
  Result[1][2] = u.z();
  Result[2][0] = -f.x();
  Result[2][1] = -f.y();
  Result[2][2] = -f.z();
  Result[0][3] = -dot(s, eye);
  Result[1][3] = -dot(u, eye);
  Result[2][3] = dot(f, eye);
  return Result;
}

fm::mat4 FM_CALL lookAtLH(const vector3 &eye, const vector3 &center,
                          const vector3 &up) {
  vector3 f(normalize(center - eye));
  vector3 s(normalize(cross(up, f)));
  vector3 u(cross(f, s));

  mat4 Result = mat4::identity();
  Result[0][0] = s.x();
  Result[0][1] = s.y();
  Result[0][2] = s.z();
  Result[1][0] = u.x();
  Result[1][1] = u.y();
  Result[1][2] = u.z();
  Result[2][0] = f.x();
  Result[2][1] = f.y();
  Result[2][2] = f.z();
  Result[0][3] = -dot(s, eye);
  Result[1][3] = -dot(u, eye);
  Result[2][3] = -dot(f, eye);
  return Result;
}

// z from 0 to 1
fm::mat4 FM_CALL perspectiveRHZO(FMFLOAT fovy, FMFLOAT aspect, FMFLOAT zNear,
                                 FMFLOAT zFar) FMTHROW {

  FMFLOAT tanHalfFovy = Tan(fovy / static_cast<FMFLOAT>(2));

  mat4 Result = mat4::zeros();
  Result[0][0] = -static_cast<FMFLOAT>(1) / (aspect * tanHalfFovy);
  Result[1][1] = -static_cast<FMFLOAT>(1) / (tanHalfFovy);
  Result[2][2] = zFar / (zNear - zFar);
  Result[2][3] = -(zFar * zNear) / (zFar - zNear);
  Result[3][2] = static_cast<FMFLOAT>(1);
  return Result;
}

// This will inverse Z
// means (right hand)before -> (left hand)after
mat4 FM_CALL perspectiveRHZO_InvZ(FMFLOAT fovy, FMFLOAT aspect, FMFLOAT zNear,
                                  FMFLOAT zFar) {
  assert(abs(aspect - std::numeric_limits<FMFLOAT>::epsilon()) >
         static_cast<FMFLOAT>(0));

  FMFLOAT tanHalfFovy = Tan(fovy / static_cast<FMFLOAT>(2));

  mat4 Result = mat4::zeros();
  Result[0][0] = -static_cast<FMFLOAT>(1) / (aspect * tanHalfFovy);
  Result[1][1] = -static_cast<FMFLOAT>(1) / (tanHalfFovy);
  Result[2][2] = zFar / (zFar - zNear);
  Result[2][3] = (zFar * zNear) / (zFar - zNear);
  Result[3][2] = static_cast<FMFLOAT>(1);
  return Result;
}

fm::mat4 FM_CALL perspectiveRHNO_InvZ(FMFLOAT fovy, FMFLOAT aspect,
                                      FMFLOAT zNear, FMFLOAT zFar) FMTHROW {

  mat4 Result = mat4::zeros();
  FMFLOAT tanHalfFovy = Tan(fovy / static_cast<FMFLOAT>(2));
  Result[0][0] = (1.) / (aspect * tanHalfFovy);
  Result[1][1] = (1.) / (tanHalfFovy);
  Result[3][2] = -(1.);
  Result[2][2] = -(zFar + zNear) / (zFar - zNear);
  Result[2][3] = -((2.) * zFar * zNear) / (zFar - zNear);
  return Result;
}

fm::mat4 FM_CALL perspectiveRHNO(FMFLOAT fovy, FMFLOAT aspect, FMFLOAT zNear,
                                 FMFLOAT zFar) FMTHROW {

  mat4 Result = mat4::zeros();
  FMFLOAT tanHalfFovy = Tan(fovy / static_cast<FMFLOAT>(2));
  Result[0][0] = -(1.) / (aspect * tanHalfFovy);
  Result[1][1] = -(1.) / (tanHalfFovy);
  Result[3][2] = (1.);
  Result[2][2] = -(zFar + zNear) / (zFar - zNear);
  Result[2][3] = -((2.) * zFar * zNear) / (zFar - zNear);
  return Result;
}

fm::mat4 FM_CALL perspectiveLHZO(FMFLOAT fovy, FMFLOAT aspect, FMFLOAT zNear,
                                 FMFLOAT zFar) FMTHROW {
  assert(abs(aspect - std::numeric_limits<FMFLOAT>::epsilon()) >
         static_cast<FMFLOAT>(0));

  FMFLOAT tanHalfFovy = Tan(fovy / static_cast<FMFLOAT>(2));

  mat4 Result = mat4::zeros();
  Result[0][0] = static_cast<FMFLOAT>(1) / (aspect * tanHalfFovy);
  Result[1][1] = static_cast<FMFLOAT>(1) / (tanHalfFovy);
  Result[2][2] = zFar / (zFar - zNear);
  Result[3][2] = static_cast<FMFLOAT>(1);
  Result[2][3] = -(zFar * zNear) / (zFar - zNear);
  return Result;
}

fm::mat4 FM_CALL perspectiveLHNO(FMFLOAT fovy, FMFLOAT aspect, FMFLOAT zNear,
                                 FMFLOAT zFar) FMTHROW {
  assert(abs(aspect - std::numeric_limits<FMFLOAT>::epsilon()) >
         static_cast<FMFLOAT>(0));

  FMFLOAT tanHalfFovy = tan(fovy / static_cast<FMFLOAT>(2));
  mat4 Result = mat4::zeros();
  Result[0][0] = (1.) / (aspect * tanHalfFovy);
  Result[1][1] = (1.) / (tanHalfFovy);
  Result[2][2] = (zFar + zNear) / (zFar - zNear);
  Result[2][3] = -((2.) * zFar * zNear) / (zFar - zNear);
  Result[3][2] = (1.);
  return Result;
}

fm::mat4 FM_CALL orthoLH_ZO(FMFLOAT const &left, FMFLOAT const &right,
                            FMFLOAT const &bottom, FMFLOAT const &top,
                            FMFLOAT const &zNear, FMFLOAT const &zFar) FMTHROW {
  mat4 Result = mat4::identity();
  Result[0][0] = 2. / (right - left);
  Result[1][1] = 2. / (top - bottom);
  Result[2][2] = 1. / (zFar - zNear);
  Result[0][3] = -(right + left) / (right - left);
  Result[1][3] = -(top + bottom) / (top - bottom);
  Result[2][3] = -zNear / (zFar - zNear);
  return Result;
}

fm::mat4 FM_CALL orthoLH_NO(FMFLOAT const &left, FMFLOAT const &right,
                            FMFLOAT const &bottom, FMFLOAT const &top,
                            FMFLOAT const &zNear, FMFLOAT const &zFar) FMTHROW {

  fm::mat4 Result = fm::mat4::identity();
  Result[0][0] = (2.) / (right - left);
  Result[1][1] = (2.) / (top - bottom);
  Result[2][2] = (2.) / (zFar - zNear);
  Result[0][3] = -(right + left) / (right - left);
  Result[1][3] = -(top + bottom) / (top - bottom);
  Result[2][3] = -(zFar + zNear) / (zFar - zNear);
  return Result;
}

fm::mat4 FM_CALL orthoRHZO_InvZ(FMFLOAT const &left, FMFLOAT const &right,
                                FMFLOAT const &bottom, FMFLOAT const &top,
                                FMFLOAT const &zNear,
                                FMFLOAT const &zFar) FMTHROW {
  mat4 Result = mat4::identity();
  Result[0][0] = (2.) / (right - left);
  Result[1][1] = (2.) / (top - bottom);
  Result[2][2] = -(1.) / (zFar - zNear);
  Result[0][3] = -(right + left) / (right - left);
  Result[1][3] = -(top + bottom) / (top - bottom);
  Result[2][3] = -zNear / (zFar - zNear);
  return Result;
}

fm::mat4 FM_CALL orthoRHZO(FMFLOAT const &left, FMFLOAT const &right,
                           FMFLOAT const &bottom, FMFLOAT const &top,
                           FMFLOAT const &zNear, FMFLOAT const &zFar) FMTHROW {
  mat4 Result = mat4::identity();
  Result[0][0] = (2.) / (right - left);
  Result[1][1] = (2.) / (top - bottom);
  Result[2][2] = -(1.) / (zFar - zNear);
  Result[0][3] = -(right + left) / (right - left);
  Result[1][3] = -(top + bottom) / (top - bottom);
  Result[2][3] = zNear / (zFar - zNear);
  return Result;
}

fm::mat4 FM_CALL orthoRHNO(FMFLOAT const &left, FMFLOAT const &right,
                           FMFLOAT const &bottom, FMFLOAT const &top,
                           FMFLOAT const &zNear, FMFLOAT const &zFar) FMTHROW {
  mat4 Result = mat4::identity();
  Result[0][0] = (2.) / (right - left);
  Result[1][1] = (2.) / (top - bottom);
  Result[2][2] = -(2.) / (zFar - zNear);
  Result[3][0] = -(right + left) / (right - left);
  Result[3][1] = -(top + bottom) / (top - bottom);
  Result[3][2] = (zFar + zNear) / (zFar - zNear);
  return Result;
}

fm::mat4 FM_CALL orthoRHNO_InvZ(FMFLOAT const &left, FMFLOAT const &right,
                                FMFLOAT const &bottom, FMFLOAT const &top,
                                FMFLOAT const &zNear,
                                FMFLOAT const &zFar) FMTHROW {
  mat4 Result = mat4::identity();
  Result[0][0] = (2.) / (right - left);
  Result[1][1] = (2.) / (top - bottom);
  Result[2][2] = -(2.) / (zFar - zNear);
  Result[3][0] = -(right + left) / (right - left);
  Result[3][1] = -(top + bottom) / (top - bottom);
  Result[3][2] = -(zFar + zNear) / (zFar - zNear);
  return Result;
}

fm::mat4 FM_CALL orthoLHZO(FMFLOAT const &left, FMFLOAT const &right,
                           FMFLOAT const &bottom, FMFLOAT const &top,
                           FMFLOAT const &zNear, FMFLOAT const &zFar) FMTHROW {
  mat4 Result = mat4::identity();
  Result[0][0] = (2.) / (right - left);
  Result[1][1] = (2.) / (top - bottom);
  Result[2][2] = (1.) / (zFar - zNear);
  Result[3][0] = -(right + left) / (right - left);
  Result[3][1] = -(top + bottom) / (top - bottom);
  Result[3][2] = -zNear / (zFar - zNear);
  return Result;
}

fm::mat4 FM_CALL orthoLHNO(FMFLOAT const &left, FMFLOAT const &right,
                           FMFLOAT const &bottom, FMFLOAT const &top,
                           FMFLOAT const &zNear, FMFLOAT const &zFar) FMTHROW {
  mat4 Result = mat4::identity();
  Result[0][0] = (2.) / (right - left);
  Result[1][1] = (2.) / (top - bottom);
  Result[2][2] = (2.) / (zFar - zNear);
  Result[3][0] = -(right + left) / (right - left);
  Result[3][1] = -(top + bottom) / (top - bottom);
  Result[3][2] = -(zFar + zNear) / (zFar - zNear);
  return Result;
}

} // namespace fm