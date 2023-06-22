#include "transform.h"

#include "../vector/vector3.h"

#include "../matrix/matrix4x4.h"
#include <cmath>
#include <corecrt_math.h>
#include <cstdlib>
#include <limits>

template <typename VecType>
static bool FM_INLINE isNormalized(const VecType &t) FMTHROW{
  return std::abs(t.length() - 1) < std::numeric_limits<FMFLOAT>::min();
}

namespace fm {

fm::mat4 FM_CALL translate(const fm::mat4 &in, const fm::vector3 &vector) FMTHROW{
  mat4 tmp = mat4::identity();
  tmp[0][3] = vector[0];
  tmp[1][3] = vector[1];
  tmp[2][3] = vector[2];
  return tmp * in;
}

fm::mat4 FM_CALL scale(const fm::mat4 &in, const fm::vector3 &vector) FMTHROW{
  mat4 tmp = mat4::identity();
  tmp[0][0] *= vector[0];
  tmp[1][1] *= vector[1];
  tmp[2][2] *= vector[2];
  tmp[3][3] *= vector[3];
  return tmp * in;
}


//Right hand system for default 
//For left hand system should use -theta instead of theta.
//https://mathworld.wolfram.com/RodriguesRotationFormula.html
fm::mat4 FM_CALL rotate(const fm::mat4 &in, const fm::vector3 &axis,
                        FMFLOAT angle) FMTHROW{
#if defined(FM_DEBUG)
  // Axis vector should be normalized.
  assert(isNormalized(axis));
#endif

  mat4 wslide = mat4::zeros();
  wslide[3] = vector4(0,0,0,1);
  wslide[0][1] = -axis[2];
  wslide[0][2] = axis[1];
  wslide[1][0] = axis[2];
  wslide[1][2] = -axis[0];
  wslide[2][0] = -axis[1];
  wslide[2][1] = axis[0];

  mat4 ret = mat4::identity() + wslide * std::sin(angle) +
             wslide * wslide * (FMFLOAT(1) - std::cos(angle));
  return ret * in;
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
} // namespace fm