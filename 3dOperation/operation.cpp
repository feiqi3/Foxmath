#include "./operation.h"
#include "../base/fox_avx.h"
#include "../base/fox_pure.h"
#include "../base/fox_sse.h"
#include "../vector/vector3.h"
#include "../vector/vector4.h"

namespace fm {

fm::vector4 FM_CALL lerp(const fm::vector4 &a, const fm::vector4 &b,
                         FMFLOAT t) FMTHROW{
  return (1 - t) * a + t * b;
}

fm::vector3 FM_CALL lerp(const fm::vector3 &a, const fm::vector3 &b,
                         FMFLOAT t) FMTHROW{
  return (1 - t) * a + t * b;
}

vector3 FM_CALL clamp(const vector3 &a, const vector3 &max,
                      const vector3 &min) FMTHROW{
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
                      const vector4 &min) FMTHROW{
  auto veca = simd::fmLoadVecP(a.__data._v);
  auto vecMin = simd::fmLoadVecP(min.__data._v);
  auto vecMax = simd::fmLoadVecP(max.__data._v);
  veca = simd::fmVecMaxOfEachElem(veca, vecMin);
  veca = simd::fmVecMinOfEachElem(veca, vecMax);
  simd::fmAlignFLoat4 ret;
  simd::fmStoreVec(ret, veca);
  return ret;
}

FM_CALL vector3 abs(const vector3& vec) FMTHROW{
  auto t = simd::fmLoadVecP(vec.__data._v);
  t = simd::fmVecAbs(t);
  simd::fmAlignFLoat4 ret;
  simd::fmStoreVec(ret, t); 
  return ret;
}

FM_CALL vector4 abs(const vector4& vec) FMTHROW{
  auto t = simd::fmLoadVecP(vec.__data._v);
  t = simd::fmVecAbs(t);
  simd::fmAlignFLoat4 ret;
  simd::fmStoreVec(ret, t); 
  return ret;
}

} // namespace fm
