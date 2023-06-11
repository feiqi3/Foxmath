#ifndef VECTOR4_H_
#define VECTOR4_H_

#include "../base/fox_avx.h"
#include "../base/fox_pure.h"
#include "../base/fox_sse.h"
#include <cmath>
#include <cstring>
#include <ostream>

namespace fm {
	class vector4 {
	public:
		vector4();
		vector4(FMFLOAT* vec);
		vector4(FMFLOAT a, FMFLOAT b, FMFLOAT c, FMFLOAT d);
		vector4(FMFLOAT a);
		FM_INLINE FMFLOAT& FM_CALL  operator[](size_t t) { return __data._v[t]; }
		FM_INLINE const FMFLOAT& FM_CALL operator[](size_t t) const { return __data._v[t]; }

		const vector4  FM_CALL operator+(const vector4& b) const noexcept;

		const vector4  FM_CALL operator-(const vector4& b) const noexcept;

		const vector4  FM_CALL operator*(const vector4& b) const noexcept;

		const vector4  FM_CALL operator/(const vector4& b) const noexcept;

		const FMFLOAT  FM_CALL dot(const vector4& b) const noexcept;

		//There's an interesting thing I just realized
		//Cross product is not coordinate system related.
		//In the right hand system, right-hand rule should Be used.
		//Vice versa, Left-hand rule should be used in left-hand system.
		const vector4  FM_CALL cross(const vector4& b) const noexcept;

		FMFLOAT  FM_CALL maxElement() const noexcept;

		FMFLOAT  FM_CALL minElement() const noexcept;

		FMFLOAT  FM_CALL length() const noexcept;

		vector4  FM_CALL square() const noexcept;

		vector4  FM_CALL sqrt() const noexcept;

		friend const vector4  FM_CALL operator*(const vector4& a,
			FMFLOAT b) noexcept;
		friend const vector4  FM_CALL operator/(const vector4& a,
			FMFLOAT b) noexcept;

		friend std::ostream& operator<<(std::ostream& out, const vector4& s);

	protected:
		vector4(const simd::fmAlignFLoat4& in) : __data(in) {}

		vector4(const simd::_fm_vec4& in) { simd::fmStroeVec(this->__data, in); }

	private:
		simd::fmAlignFLoat4 __data;
	};

	const vector4  FM_CALL operator*(const vector4& a, FMFLOAT b) noexcept;

	const vector4  FM_CALL operator*(FMFLOAT b, const vector4& a) noexcept;

	const vector4  FM_CALL operator/(const vector4& a, FMFLOAT b) noexcept;

	std::ostream& operator<<(std::ostream& out, const vector4& s);

	bool  FM_CALL hasNan(const vector4& in) noexcept;

} // namespace fm

#endif