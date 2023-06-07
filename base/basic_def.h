#ifndef BASIC_DEF_H
#define BASIC_DEF_H

#define FM_DEBUG

//**NOTE** There is only one calling convention under x86-64, a strange fastcall

//Only works under x86
#if defined(_MSC_VER) && !defined(_M_ARM) && !defined(_M_ARM64)
#define _FM_USE_VECTORCALL_  
#endif

#if defined (__GNUC__)
#define _FM_USE_FASTCALL_ 
#endif

#ifdef _FM_USE_VECTORCALL_
    //only msvc
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

#endif //BASIC_DEF_H