#ifndef OPERATION_H_
#define OPERATION_H_
#include "../base/basic_def.h"
#include "./constants.h"
#include <algorithm>
#include <cstdlib>
#include <type_traits>
namespace fm {

template <typename T>
T FM_FORCE_INLINE FM_CALL lerp(T a, T b, FMFLOAT t) FMTHROW {
  return (1 - t) * a + t * b;
}
class vector4;
vector4 FM_CALL lerp(const vector4 &a, const vector4 &b, FMFLOAT t) FMTHROW;

class vector3;
vector3 FM_CALL lerp(const vector3 &a, const vector3 &b, FMFLOAT t) FMTHROW;

template <typename T>
T FM_FORCE_INLINE FM_CALL clamp(T a, T min, T max) FMTHROW {
  return std::min(max, std::max(a, min));
}

vector4 FM_CALL clamp(const vector4 &a, const vector4 &max,
                      const vector4 &min) FMTHROW;

vector3 FM_CALL clamp(const vector3 &a, const vector3 &max,
                      const vector3 &min) FMTHROW;

FMFLOAT FM_FORCE_INLINE FM_CALL degToRad(FMFLOAT a) FMTHROW {
  static FMFLOAT inv180mulPI = PI / FMFLOAT(180);
  return a * inv180mulPI;
}

FMFLOAT FM_FORCE_INLINE FM_CALL radToDeg(FMFLOAT a) FMTHROW {
  static FMFLOAT F180DivPI = FMFLOAT(180) * INV_PI;
  return a * F180DivPI;
}

template <typename T> T FM_FORCE_INLINE FM_CALL abs(T a) { return std::abs(a); }

vector3 FM_CALL abs(const vector3 &vec) FMTHROW;

vector4 FM_CALL abs(const vector4 &vec) FMTHROW;

double FM_CALL __do_Sin(double x) FMTHROW;

template <typename T, typename std::enable_if<std::is_floating_point<T>::value,
                                              bool>::type = true>
FM_FORCE_INLINE T FM_CALL Sin(T ty) FMTHROW {
  return __do_Sin(static_cast<double>(ty));
}

double FM_CALL __do_Cos(double x) FMTHROW;

template <typename T, typename std::enable_if<std::is_floating_point<T>::value,
                                              bool>::type = true>
FM_FORCE_INLINE T FM_CALL Cos(T ty) FMTHROW {
  return __do_Cos(static_cast<double>(ty));
}

double FM_CALL __do_Tan(double x) FMTHROW;

template <typename T, typename std::enable_if<std::is_floating_point<T>::value,
                                              bool>::type = true>
FM_FORCE_INLINE T FM_CALL Tan(T ty) FMTHROW {
  return __do_Tan(static_cast<double>(ty));
}

double FM_CALL __do_Cot(double in) FMTHROW;
template <typename T, typename std::enable_if<std::is_floating_point<T>::value,
                                              bool>::type = true>
FM_FORCE_INLINE T FM_CALL Cot(T ty) FMTHROW {
  return __do_Cot(static_cast<double>(ty));
}

double FM_CALL __do_Arctan(double in) FMTHROW;
double FM_CALL __do_Cot(double in) FMTHROW;
template <typename T, typename std::enable_if<std::is_floating_point<T>::value,
                                              bool>::type = true>
FM_FORCE_INLINE T FM_CALL Arctan(T ty) FMTHROW {
  return __do_Arctan(static_cast<double>(ty));
}

double FM_CALL __do_Ln(double in) FMTHROW;
template <typename T, typename std::enable_if<std::is_floating_point<T>::value,
                                              bool>::type = true>
FM_FORCE_INLINE T FM_CALL Log(T ty) FMTHROW {
  return __do_Ln(ty);
}
double FM_CALL __do_Log2(double in) FMTHROW;
template <typename T, typename std::enable_if<std::is_floating_point<T>::value,
                                              bool>::type = true>
FM_FORCE_INLINE T FM_CALL Log2(T ty) FMTHROW {
  return __do_Log2(ty);
}

double FM_CALL __do_Log10(double in) FMTHROW;
template <typename T, typename std::enable_if<std::is_floating_point<T>::value,
                                              bool>::type = true>
FM_FORCE_INLINE T FM_CALL Log10(T ty) FMTHROW {
  return __do_Log10(ty);
}
} // namespace fm

#endif