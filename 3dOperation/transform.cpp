#include "transform.h"

#include "../vector/vector3.h"

#include "../matrix/matrix4x4.h"
#include <cmath>
#include <corecrt_math.h>
#include <cstdlib>
#include <limits>

static constexpr FMFLOAT BIAS = 30 * std::numeric_limits<FMFLOAT>::min();

template <typename VecType>
static bool FM_INLINE isNormalized(const VecType &t) FMTHROW {
  return std::abs(t.length() - 1) < BIAS;
}

namespace fm {

fm::mat4 FM_CALL translate(
                           const fm::vector3 &vector) FMTHROW {
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
  tmp[3][3] *= vector[3];
  return tmp;
}

// Right hand system for default
// For left hand system should use -theta instead of theta.
// https://mathworld.wolfram.com/RodriguesRotationFormula.html
fm::mat4 FM_CALL rotate(const fm::vector3 &axis,
                        FMFLOAT angle) FMTHROW {
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

fm::mat4 FM_CALL rotate_mat_around_x(FMFLOAT angle) FMTHROW {
  mat4 tmp = mat4::identity();
  auto cosTheta = std::cos(angle);
  auto sinTheta = std::sin(angle);
  tmp[1][1] = cosTheta;
  tmp[1][2] = -sinTheta;
  tmp[2][1] = sinTheta;
  tmp[2][2] = cosTheta;
  return tmp;
}

fm::mat4 FM_CALL rotate_mat_around_y(FMFLOAT angle) FMTHROW {
  mat4 tmp = mat4::identity();
  auto cosTheta = std::cos(angle);
  auto sinTheta = std::sin(angle);
  tmp[0][0] = cosTheta;
  tmp[0][2] = sinTheta;
  tmp[2][0] = -sinTheta;
  tmp[2][2] = cosTheta;
  return tmp;
}

fm::mat4 FM_CALL rotate_mat_around_z(FMFLOAT angle) FMTHROW {
  mat4 tmp = mat4::identity();
  auto cosTheta = std::cos(angle);
  auto sinTheta = std::sin(angle);
  tmp[0][0] = cosTheta;
  tmp[0][1] = -sinTheta;
  tmp[1][0] = sinTheta;
  tmp[1][1] = cosTheta;
  return tmp;
}

} // namespace fm