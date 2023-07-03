#ifndef VECTOR3_H_
#define VECTOR3_H_
#include "../base/basic_def.h"
#include <ostream>
namespace fm {
	class vector3 {
	public:
		vector3()FMTHROW;

		vector3(const FMFLOAT* in);

		vector3(FMFLOAT a, FMFLOAT b, FMFLOAT c) FMTHROW;

		vector3(const vector3& in) FMTHROW;

		FMFLOAT& FM_CALL  operator[](size_t t) FMTHROW;

		//constants
		static  vector3 FM_CALL ones() FMTHROW;
		static  vector3 FM_CALL right() FMTHROW;
		static  vector3 FM_CALL left() FMTHROW;
		static vector3 FM_CALL up() FMTHROW;
		static vector3 FM_CALL down() FMTHROW;
		static vector3 FM_CALL forward() FMTHROW;
		static vector3 FM_CALL back() FMTHROW;

		FMFLOAT& FM_CALL x() FMTHROW;
		FMFLOAT& FM_CALL y() FMTHROW;
		FMFLOAT& FM_CALL z() FMTHROW;

		const FMFLOAT& FM_CALL operator[](size_t t) const FMTHROW;

		const vector3  FM_CALL operator+(const vector3& b) const FMTHROW;

		const vector3  FM_CALL operator-(const vector3& b) const FMTHROW;

		const vector3  FM_CALL operator-() const FMTHROW;

		const vector3  FM_CALL operator*(const vector3& b) const FMTHROW;

		const vector3  FM_CALL operator/(const vector3& b) const FMTHROW;

		friend std::ostream& operator<<(std::ostream& out, const vector3& s);

		friend const vector3 FM_CALL operator*(const vector3& a, FMFLOAT b) FMTHROW;

		friend vector3 FM_CALL clamp(const vector3& a, const vector3& max, const vector3& min)FMTHROW;

		friend vector3 FM_CALL abs(const vector3& vec)FMTHROW;

		friend class vector4;

		FMFLOAT FM_CALL maxElement() const FMTHROW;
		FMFLOAT FM_CALL minElement() const FMTHROW;
		FMFLOAT FM_CALL length() const FMTHROW;
		vector3 FM_CALL square() const FMTHROW;
		vector3 FM_CALL sqrt() const FMTHROW;
		const FMFLOAT FM_CALL dot(const vector3& b) const FMTHROW;
		const vector3 FM_CALL cross(const vector3& b) const FMTHROW;
	protected:
		vector3(const simd::fmAlignFLoat4& in);
	private:
		fm::simd::fmAlignFLoat4 __data;

	};

	const vector3  FM_CALL operator*(const vector3& a, FMFLOAT b) FMTHROW;

	const vector3  FM_CALL operator*(FMFLOAT b, const vector3& a) FMTHROW;

	const vector3  FM_CALL operator/(const vector3& a, FMFLOAT b) FMTHROW;

	std::ostream& operator<<(std::ostream& out, const vector3& s);

	bool  FM_CALL hasNan(const vector3& in) FMTHROW;

}
#endif