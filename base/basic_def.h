#ifndef BASIC_DEF_H
#define BASIC_DEF_H

#include <stdint.h>
#include <cassert>
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

#if defined (__AVX__)
#define _FM_AVX_
#define _FM_SSE3_
#define _FM_SSE4_
#include "immintrin.h"
#endif

#if defined (__AVX2__)
#define _FM_AVX_
#define _FM_AVX2_
#define _FM_SSE3_
#define _FM_SSE4_
#include "immintrin.h"
#endif

#define FM_ALIGNED(x) struct alignas(x)

#define FM_INLINE inline

namespace fm {

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

#if defined (_FM_PURE_) || (!defined (_FM_SSE4_) && !defined (_FM_AVX2_) )
		using _fm_vec4 = struct {
			FMFLOAT v[4];
		};
#endif
		//Mem align check
		void FM_INLINE FM_CALL MEM_ALIGN_CHECK(const void* ptr, size_t alignment) {
			assert((int64_t)ptr % alignment == 0);
		}

		struct alignas(FM_ALIGN_REQ) fmAlignFLoat4 {
			FMFLOAT _v[4];
			FMFLOAT& operator [](size_t t) {
				return _v[t];
			}

		};
	}
}

// | a | b | c | d | -> vec layout in memory
// | 0 | 1 | 2 | 3 | -> shuffle index
#define _FM_SHUFFLE(a,b,c,d) _MM_SHUFFLE(d,c,b,a)
//For Shuffle operation 
/*--------------------------------------------*/
//The Shuffle Index is like below in _MM_SHUFFLE
// | a | b | c | d |  -> _m256/_m128's layout in memory, load by _mm256_set_pd(d, c, b, a)
// | 0 | 1 | 2 | 3 |  -> shuffle index
// After using shuffle by _MM_SHUFFLE(0,1,2,3)
// We will get (d,c,b,a)
// See, it inverse the vector after shuffle it

//Another example 
//For a _m256 has a mem layout like below 
// | 0 | 1 | 2 | 3 |
// Then use the shuffle sequence (0,1,2,3)
//will get the outcome 
// | 3 | 2 | 1 | 0 |

//The final example 
// Vector : 
// | 0 | 1 | 2 | 3 |
// Shuffle sequence
// | 3 | 0 | 2 | 1 |
// Will get :
// | 1 | 2 | 0 | 3 |
//Anyway I think _MM_SHUFFLE and shuffle operation ar SUPER S/T/U/P/I/D function
//It makes no sense.
//This has confused me for hours.
//So I leave a Macro and a long comment here
//To make EVERY THING CLEAR


#endif //BASIC_DEF_H