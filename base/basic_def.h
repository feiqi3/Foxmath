#ifndef BASIC_DEF_H
#define BASIC_DEF_H

#include <cassert>
#include <stdint.h>

#define FM_DEBUG

//**NOTE**
// There is only one calling convention under x86-64, a strange fastcall
// https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170

// Only works under x86
#if defined(_MSC_VER)
#define _FM_USE_VECTORCALL_
#elif defined(__GNUC__) || defined(__clang__)
#define _FM_USE_FASTCALL_
#endif

#define FMTHROW noexcept

#ifdef _FM_USE_VECTORCALL_
// MSVC only, fast than fastcall/stdcall
// https://learn.microsoft.com/en-us/cpp/cpp/vectorcall?view=msvc-170
#define FM_CALL __vectorcall
#elif defined(_FM_USE_FASTCALL_)
#define FM_CALL __fastcall
#else
#define FM_CALL
#endif

#if defined(__SSSE3__)
#define _FM_SSE3_
#include "immintrin.h"
#endif

#if defined(__SSE4_2__)
#define _FM_SSE3_
#define _FM_SSE4_
#include "immintrin.h"
#endif

#if defined(__AVX__)
#define _FM_AVX_
#define _FM_SSE3_
#define _FM_SSE4_
#include "immintrin.h"
#endif

#if defined(__AVX2__)
#define _FM_AVX_
#define _FM_AVX2_
#define _FM_SSE3_
#define _FM_SSE4_
#include "immintrin.h"
#endif

// MSVC does not support #warning #error
#if defined(_MSC_VER)
#define __AUX_STR_EXP(_exp_) #_exp_
/** Transform \a _exp_ to string format. */
#define ___AUX_STR(_exp_) __AUX_STR_EXP(_exp_)
/** location file name and file line */
#define __LOCATION_STR __FILE__ "(" ___AUX_STR(__LINE__) ")"
/** define warning message throw */
#define throw_warning(_code_, _message_)                                       \
  message(__LOCATION_STR ": warning C" ___AUX_STR(_code_) ": " _message_)
#define throw_error(_level_, _code_, _message_)                                \
  message(__LOCATION_STR ":" _level_                                           \
                         " error C" ___AUX_STR(_code_) ": " _message_)
#endif

#define FM_ALIGNED(x) struct alignas(x)

#define FM_INLINE inline

#if defined(_M_ARM) || defined(_M_ARM64)
#if !defined(_MSC_VER)
#error Arm is not supported now
#else
#pragma throw_error(10000, "FoxMath does not support arm.")
#endif
#endif

#if (defined(_FM_PURE_))
#if !defined(_MSC_VER)
#warning "SIMD Optimization is closed."
#else
#pragma throw_warning(10001, "SIMD Optimization is closed.")

#endif
#endif

namespace fm {

	namespace simd {

		// Default use float as vector's element
#if !defined(_FM_USE_DOUBLE) && !defined(_FM_USE_FLOAT)
#define _FM_USE_FLOAT
#endif

#if defined(_FM_USE_DOUBLE)
#define FMFLOAT double
#if defined(_FM_AVX2_)
#define FM_ALIGN_REQ 32
		using _fm_vec4 = __m256d;
#endif
#elif defined(_FM_USE_FLOAT)
#define FMFLOAT float
#if defined(_FM_SSE4_)
#define FM_ALIGN_REQ 16
		using _fm_vec4 = __m128;
#endif
#endif

#if defined(_FM_PURE_) || (!defined(_FM_SSE4_) && !defined(_FM_AVX2_))
#define FM_ALIGN_REQ 8
		using _fm_vec4 = struct {
			FMFLOAT v[4];
		};
#endif
		// Mem align check
		void FM_INLINE FM_CALL MEM_ALIGN_CHECK(const void* ptr, size_t alignment) {
			assert((int64_t)ptr % alignment == 0);
		}

		struct alignas(FM_ALIGN_REQ) fmAlignFLoat4 {
			FMFLOAT _v[4];
			FMFLOAT& operator[](size_t t) { return _v[t]; }
		};
	} // namespace simd
} // namespace fm

// | a | b | c | d | -> vec layout in memory
// | 0 | 1 | 2 | 3 | -> shuffle index
#define _FM_SHUFFLE(a, b, c, d) _MM_SHUFFLE(d, c, b, a)
// For Shuffle operation
/*--------------------------------------------*/
// The Shuffle Index is like below in _MM_SHUFFLE
//  | a | b | c | d |  -> _m256/_m128's layout in memory, load by
//  _mm256_set_pd(d, c, b, a)/_mm_set_ps(d, c, b, a) | 0 | 1 | 2 | 3 |  ->
//  shuffle index After using shuffle by _MM_SHUFFLE(0,1,2,3) We will get
//  (d,c,b,a) See, it inverse the vector after shuffling it

// Another example
// For a _m256 has a mem layout like below
//  | 0 | 1 | 2 | 3 |
//  Then use the shuffle sequence (0,1,2,3)
// will get the outcome
//  | 3 | 2 | 1 | 0 |

// The final example
//  Vector :
//  | 0 | 1 | 2 | 3 |
//  Shuffle sequence
//  | 3 | 0 | 2 | 1 |
//  Will get :
//  | 1 | 2 | 0 | 3 |
// Anyway I think _MM_SHUFFLE is a SUPER S/T/U/P/I/D function
// It is confusing and is a total chaos.
// So I leave a Macro and a long comment here
// To make EVERYTHING CLEAR

#if __cplusplus >= 201703L
#define FM_NEW new
#else
#if !defined(_MSC_VER)
#error                                                                         \
    "Under std:c++17, operator new cannot assure the alignment of struct, which may cause crash when using simd instruction"
#else
#pragma throw_warning(                                                         \
    10002,                                                                     \
    "Under c++17, operator new cannot assure the alignment of struct, which may cause crash when using simd instruction")
#endif

#endif

#endif // BASIC_DEF_H