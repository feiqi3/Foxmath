#ifndef VECTOR4_H_
#define VECTOR4_H_

#include "../base/fox_avx.h"
#include "../base/fox_pure.h"
#include "../base/fox_sse.h"
#include <cmath>
#include <cstring>
#include <initializer_list>
#include <ostream>

// Forward declaration

namespace fm {
	class vector4 {
	public:
		vector4()noexcept;
		vector4(const std::initializer_list<FMFLOAT>& list);
		vector4(FMFLOAT* vec);
		vector4(FMFLOAT a, FMFLOAT b, FMFLOAT c, FMFLOAT d) noexcept;
		vector4(FMFLOAT a)noexcept;
		vector4(const vector4& in);
		FMFLOAT& FM_CALL  operator[](size_t t) noexcept;



		const FMFLOAT& FM_CALL operator[](size_t t) const noexcept;

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

		friend class mat4;

		friend const fm::vector4 FM_CALL operator*(const fm::vector4& veca,
			const fm::mat4& matb) noexcept;


		friend const fm::vector4 FM_CALL operator*(const fm::mat4& mata,
			const fm::vector4& vecb) noexcept;

	protected:
		vector4(const simd::fmAlignFLoat4& in);

		vector4(const simd::_fm_vec4& in);

	protected:
		simd::fmAlignFLoat4 __data;
	};

	const vector4  FM_CALL operator*(const vector4& a, FMFLOAT b) noexcept;

	const vector4  FM_CALL operator*(FMFLOAT b, const vector4& a) noexcept;

	const vector4  FM_CALL operator/(const vector4& a, FMFLOAT b) noexcept;

	std::ostream& operator<<(std::ostream& out, const vector4& s);

	bool  FM_CALL hasNan(const vector4& in) noexcept;

} // namespace fm

#endif