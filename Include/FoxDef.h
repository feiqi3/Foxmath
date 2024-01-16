#ifndef BASIC_DEF_H
#define BASIC_DEF_H

#include <cassert>
#include <cstddef>
#include <stdint.h>

// Only works under x86
#if defined(_MSC_VER)
// MSVC only, fast than fastcall/stdcall
// https://learn.microsoft.com/en-us/cpp/cpp/vectorcall?view=msvc-170
#define FM_CALL __vectorcall

#define FM_FORCE_INLINE __forceinline

#elif defined(__GNUC__) || defined(__clang__)
#define FM_CALL __fastcall

// https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html
#define FM_FORCE_INLINE __attribute__((always_inline)) inline
#else
#define FM_CALL
#define FM_FORCE_INLINE
#endif

// There is the calling convention under x86-64,like a strange version of
// fastcall
// https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170
#if defined(__x86_64__)
#undef FM_CALL
#define FM_CALL
#endif

#define FMTHROW noexcept

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

#define FM_ALIGNED(x) struct alignas(x)

#if defined(_M_ARM) || defined(_M_ARM64)
#if !defined(_MSC_VER)
#error Arm is not supported now
#else

//////////

#endif
#endif

#if (defined(FOX_PURE))
#if !defined(_MSC_VER)
#warning "SIMD Optimization is closed."
#else
#pragma throw_warning(10001, "SIMD Optimization is closed.")

#endif
#endif

// Default use float as vector's element
#if !defined(FOX_USE_DOUBLE) && !defined(FOX_USE_FLOAT)
#define FOX_USE_FLOAT
#endif

#if defined(FOX_USE_DOUBLE)
#define FMFLOAT double
#define FM_ALIGN_REQ 32
#elif defined(FOX_USE_FLOAT)
#define FMFLOAT float
#define FM_ALIGN_REQ 16
#endif

#if defined(FOX_PURE) && (!defined(_FM_SSE4_) && !defined(_FM_AVX2_))
using _fm_vec4 = struct {
  FMFLOAT v[4];
};
#endif
// Mem align check
void FM_FORCE_INLINE FM_CALL MEM_ALIGN_CHECK(const void *ptr,
                                             size_t alignment) {
  assert(reinterpret_cast<unsigned long long>(ptr) % alignment == 0);
}
namespace fm {

namespace simd {
struct alignas(FM_ALIGN_REQ) fmAlignFLoat4 {
  FMFLOAT _v[4];
  FMFLOAT &operator[](size_t t) { return _v[t]; }
};
} // namespace simd
} // namespace fm

#define FM_ALIGN_NEW(x) new (_mm_malloc(sizeof(x), FM_ALIGN_REQ)) x
#define FM_ALIGN_MALLOC(x) (_mm_malloc(x, FM_ALIGN_REQ))
#define FM_DELETE(x) _mm_free(x)

namespace fm {
class VecBase {
public:
  void *operator new(size_t size) { return FM_ALIGN_MALLOC(size); }
};
} // namespace fm

#endif // BASIC_DEF_H