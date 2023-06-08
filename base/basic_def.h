#ifndef BASIC_DEF_H
#define BASIC_DEF_H

#include <stdint.h>
#define FM_DEBUG

//**NOTE** 
//There is only one calling convention under x86-64, a strange fastcall
//https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170

//Only works under x86
#if defined(_MSC_VER)
#define _FM_USE_VECTORCALL_  
#elif defined (__GNUC__) || defined (__clang__)
#define _FM_USE_FASTCALL_ 
#endif

#ifdef _FM_USE_VECTORCALL_
//MSVC only, fast than fastcall/stdcall
//https://learn.microsoft.com/en-us/cpp/cpp/vectorcall?view=msvc-170
    #define FM_CALL __vectorcall
#elif defined(_FM_USE_FASTCALL_)
    #define FM_CALL __fastcall
#else
    #define FM_CALL
#endif

#if defined (__SSSE3__)
    #define _FM_SSE3_
    #include "immintrin.h"
#endif

#if defined (__SSE4_2__)
    #define _FM_SSE3_
    #define _FM_SSE4_
    #include "immintrin.h"
#endif

#if defined (__AVX2__)
    #define _FM_AVX2_
    #define _FM_SSE3_
    #define _FM_SSE4_
    #include "immintrin.h"
#endif

#define FM_ALIGNED(x) struct alignas(x)

#define FM_INLINE inline

namespace fm{

namespace simd {

//Default use float as vector's element
#if !defined (_FM_USE_DOUBLE) && !defined (_FM_USE_FLOAT)
    #define _FM_USE_FLOAT
#endif

#if defined(_M_ARM) || defined(_M_ARM64)
    #error Arm is not supported now
#endif

#if (defined (_FM_PURE_))
    #warning SIMD Optimization is closed.
    #define FM_ALIGN_REQ 8
#endif

#if defined (_FM_USE_DOUBLE)
    #define FM_ALIGN_REQ 32
    #define FMFLOAT double
    #if defined (_FM_AVX2_)
        using _fm_vec4 = __m256d;
    #endif
#elif defined (_FM_USE_FLOAT)
    #define FM_ALIGN_REQ 16
    #define FMFLOAT float
    #if defined (_FM_SSE4_)
    using _fm_vec4 = __m128;
    #endif
#endif

#if defined (_FM_PURE_)
using _fm_vec4 = struct {
        FMFLOAT v[4];
    };
#endif
#include <cassert>
//Mem align check
void FM_INLINE FM_CALL MEM_ALIGN_CHECK(const void* ptr,size_t alignment){
    assert((int64_t)ptr % alignment == 0);
}

struct alignas(FM_ALIGN_REQ) fmAlignFLoat4{
    FMFLOAT _v[4];
    FMFLOAT& operator [](size_t t){
        return _v[t];
    }

};
}
}

#endif //BASIC_DEF_H