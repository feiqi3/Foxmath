#ifndef MATRIX_4X4_H_
#define MATRIX_4X4_H_
#include "../vector/vector4.h"
#include <ostream>
namespace fm {

	// Forward declaration

	class mat4 {
	public:
		mat4();
		mat4(const std::initializer_list<FMFLOAT>& in);
		mat4(FMFLOAT _m00, FMFLOAT _m01, FMFLOAT _m02, FMFLOAT _m03, FMFLOAT _m10,
			FMFLOAT _m11, FMFLOAT _m12, FMFLOAT _m13, FMFLOAT _m20, FMFLOAT _m21,
			FMFLOAT _m22, FMFLOAT _m23, FMFLOAT _m30, FMFLOAT _m31, FMFLOAT _m32,
			FMFLOAT _m33);
		mat4(const vector4& vec0, const vector4& vec1, const vector4& vec2,
			const vector4& vec3);

		vector4& FM_CALL operator[](size_t t) noexcept;

		const vector4& FM_CALL operator[](size_t t) const noexcept;

		const mat4 FM_CALL operator*(const mat4& b) const noexcept;

		const mat4 FM_CALL operator+(const mat4& b) const noexcept;

		const mat4 FM_CALL operator-(const mat4& b) const noexcept;


		friend std::ostream& operator<<(std::ostream& out, const mat4& s);

		static FM_CALL mat4 ones();

		friend vector4;
	private:
		fm::vector4 __data[4];
	};

	const fm::vector4 FM_CALL operator*(const fm::vector4& veca,
		const fm::mat4& matb) noexcept;


	const fm::vector4 FM_CALL operator*(const fm::mat4& mata,
		const fm::vector4& vecb) noexcept;


} // namespace fm


#endif