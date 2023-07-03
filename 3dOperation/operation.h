#ifndef OPERATION_H_
#define OPERATION_H_
#include "../base/basic_def.h"
#include "./constants.h"
#include <algorithm>
#include <cstdlib>
namespace fm {

template<typename T>
T FM_CALL FM_FORCE_INLINE lerp( T a,T b,FMFLOAT t) FMTHROW{
    return (1 - t) * a + t* b;
}
class vector4;
fm::vector4 FM_CALL lerp(const fm::vector4& a,const fm::vector4& b,FMFLOAT t)FMTHROW;

class vector3;
fm::vector3 FM_CALL lerp(const fm::vector3& a,const fm::vector3& b,FMFLOAT t)FMTHROW;

template<typename T>
T FM_CALL FM_FORCE_INLINE clamp( T a,T min,T max){
    return std::min(max,std::max(a, min));
}

vector4 FM_CALL clamp(const vector4 &a, const vector4 &max,
                      const vector4 &min)FMTHROW;

vector3 FM_CALL clamp(const vector3 &a, const vector3 &max,
                      const vector3 &min)FMTHROW;

FM_CALL FMFLOAT FM_FORCE_INLINE degToRad(FMFLOAT a)FMTHROW{
    static FMFLOAT inv180mulPI = FMFLOAT(1)/FMFLOAT(180)*PI;
    return a * PI * inv180mulPI;
}

FM_CALL FMFLOAT FM_FORCE_INLINE radToDeg(FMFLOAT a) FMTHROW{
    static FMFLOAT F180DivPI = FMFLOAT(180)*INV_PI;
    return a * F180DivPI;

}

template <typename T>
FM_CALL T FM_FORCE_INLINE abs(T a){
    return std::abs(a);
}

FM_CALL vector3 abs(const vector3& vec)FMTHROW;

FM_CALL vector4 abs(const vector4& vec)FMTHROW;

}


#endif