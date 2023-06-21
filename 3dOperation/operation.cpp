#include "./operation.h"
#include "../base/fox_avx.h"
#include "../base/fox_pure.h"
#include "../base/fox_sse.h"
#include "../vector/vector3.h"
#include "../vector/vector4.h"

namespace fm {

fm::vector4 FM_CALL lerp(const fm::vector4 &a, const fm::vector4 &b,
                         FMFLOAT t) {
  return (1 - t) * a + t * b;
}

fm::vector3 FM_CALL lerp(const fm::vector3 &a, const fm::vector3 &b,
                         FMFLOAT t) {
  return (1 - t) * a + t * b;
}

vector3 FM_CALL clamp(const vector3 &a, const vector3 &max,
                      const vector3 &min) {
  auto veca = simd::fmLoadVecP(a.__data._v);
  auto vecMin = simd::fmLoadVecP(min.__data._v);
  auto vecMax = simd::fmLoadVecP(max.__data._v);
  veca = simd::fmVecMaxOfEachElem(veca, vecMin);
  veca = simd::fmVecMinOfEachElem(veca, vecMax);
  simd::fmAlignFLoat4 ret;
  simd::fmStoreVec(ret, veca);
  return ret;
}

vector4 FM_CALL clamp(const vector4 &a, const vector4 &max,
                      const vector4 &min) {
  auto veca = simd::fmLoadVecP(a.__data._v);
  auto vecMin = simd::fmLoadVecP(min.__data._v);
  auto vecMax = simd::fmLoadVecP(max.__data._v);
  veca = simd::fmVecMaxOfEachElem(veca, vecMin);
  veca = simd::fmVecMinOfEachElem(veca, vecMax);
  simd::fmAlignFLoat4 ret;
  simd::fmStoreVec(ret, veca);
  return ret;
}

} // namespace fm
