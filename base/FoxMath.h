#ifndef FOX_MATH_H_
#define FOX_MATH_H_

#include "basic_def.h"
#include <stdint.h>
#define _FM_USE_DOUBLE

#undef _FM_AVX2_

#define _FM_PURE_

//Default use float as vector's element
#if !defined (_FM_USE_DOUBLE) && !defined (_FM_USE_FLOAT)
    #define _FM_USE_FLOAT
#endif

#if defined(_M_ARM) || defined(_M_ARM64)
    #error Arm is not supported now
#endif

#if (defined (_FM_PURE_))
    #warning SIMD Optimization is closed.
#endif

#if defined (_FM_USE_DOUBLE)
    #define FMFLOAT double
    #if defined (_FM_AVX2_)
        using _fm_vec4 = __m256d;
    #elif defined (_FM_PURE_)
        struct _fm_vec4{
           double v[4];
        };
    #endif
#elif defined (_FM_USE_FLOAT)
    #define FMFLOAT float
    #if defined (_FM_SSE4_)

    //TODO: using sse float4 
    
    #include "immintrin.h"
    using _fm_vec4 = __m128;
    #elif defined (_FM_PURE_)
        struct _fm_vec4{
           float v[4];
        };
    #endif
#endif

#include <cassert>
//Mem align check
void FM_INLINE FM_CALL MEM_ALIGN_CHECK(const void* ptr,size_t alignment){
    assert((int64_t)ptr % alignment == 0);
}

#endif
