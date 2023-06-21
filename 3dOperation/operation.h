#ifndef OPERATION_H_
#define OPERATION_H_
#include "../base/basic_def.h"
#include <algorithm>
namespace fm {

template<typename T>
T FM_CALL lerp( T a,T b,FMFLOAT t){
    return (1 - t) * a + t* b;
}
class vector4;
fm::vector4 FM_CALL lerp(const fm::vector4& a,const fm::vector4& b,FMFLOAT t);

class vector3;
fm::vector3 FM_CALL lerp(const fm::vector3& a,const fm::vector3& b,FMFLOAT t);

template<typename T>
T FM_CALL clamp( T a,T min,T max){
    return std::clamp(a, min,max);
}

vector4 FM_CALL clamp(const vector4 &a, const vector4 &max,
                      const vector4 &min);

vector3 FM_CALL clamp(const vector3 &a, const vector3 &max,
                      const vector3 &min);
}
#endif