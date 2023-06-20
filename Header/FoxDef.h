#ifndef FOXDEF_H_
#define FOXDEF_H_

#include <cassert>
#include <cstdint>



#if defined(_MSC_VER)
#define _FM_USE_VECTORCALL_
#elif defined(__GNUC__) || defined(__clang__)
#define _FM_USE_FASTCALL_
#endif

#define FMTHROW noexcept

#ifdef _FM_USE_VECTORCALL_
#define FM_CALL __vectorcall
#elif defined(_FM_USE_FASTCALL_)
#define FM_CALL __fastcall
#else
#define FM_CALL
#endif

#define FM_ALIGNED(x) struct alignas(x)

#define FM_INLINE __forceinline

namespace fm {

namespace simd {

#if defined(_FM_USE_DOUBLE)
#define FMFLOAT double
extern inline constexpr size_t FM_ALIGN_REQ = 32;
#elif defined(_FM_USE_FLOAT)
extern inline constexpr size_t FM_ALIGN_REQ = 16;
#define FMFLOAT float
#else
#define FMFLOAT float
extern inline constexpr size_t FM_ALIGN_REQ = 16;
#endif

struct alignas(FM_ALIGN_REQ) fmAlignFLoat4 {
  FMFLOAT _v[4];
  FMFLOAT &operator[](size_t t) { return _v[t]; }
};

void FM_INLINE FM_CALL MEM_ALIGN_CHECK(const void *ptr, size_t alignment) {
  assert(((long long)ptr) % alignment == 0);
}
} // namespace simd
} // namespace fm

#if __cplusplus >= 201703L
#define FM_ALIGN_NEW(x) new x
#define FM_DELETE(x) delete x
#else
#define FM_ALIGN_NEW(x) new (_mm_malloc(sizeof(x), fm::simd::FM_ALIGN_REQ)) x
#define FM_DELETE(x) _mm_free(x)
#if !defined(_MSC_VER)
#warning                                                                       \
    "Under std:c++17, operator new cannot assure the alignment of struct, using FM_ALIGN_NEW(x) instead when allocating memory for vector/mat"
#else
#pragma message(__FILE__ "(" #__LINE__ ")" ": warning C" #_code_ ": " "Under std:c++17, operator new cannot assure the alignment of struct, using FM_ALIGN_NEW(x) instead when allocating memory for vector/mat")
#endif
#endif


#endif // BASIC_DEF_H