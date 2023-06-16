#include "vector4.h"
#include <cmath>
namespace fm {
	vector4::vector4(FMFLOAT* vec) {
		std::memcpy(this->__data._v, vec, 4 * sizeof(FMFLOAT));
	}

	vector4::vector4() noexcept :__data{ 0,0,0,0 } {}

	vector4::vector4(const std::initializer_list<FMFLOAT>& list)
	{
#if defined(FM_DEBUG)
		assert(list.size() == 4);
#endif//FM_DEBUG
		auto lp = list.begin();
		for (char i = 0; i < 4; ++i, ++lp) {
			__data[i] = *lp;
		}
	}

	vector4::vector4(FMFLOAT a) noexcept :__data{ a,a,a,a } {
	}

	vector4::vector4(const vector4& in)
	{
		memcpy(this->__data._v, in.__data._v, sizeof(__data));
	}

	FMFLOAT& FM_CALL vector4::operator[](size_t t) noexcept
	{
#ifdef FM_DEBUG
		assert(t <= 3 && t >= 0);
#endif // FM_DEBUG

		return __data._v[t];
	}

	const FMFLOAT& FM_CALL vector4::operator[](size_t t) const noexcept
	{
#ifdef FM_DEBUG
		assert(t <= 3 && t >= 0);
#endif // FM_DEBUG
		return __data._v[t];
	}

	vector4::vector4(FMFLOAT a, FMFLOAT b, FMFLOAT c, FMFLOAT d) noexcept :__data{ a,b,c,d }
	{
	}

	const vector4 FM_CALL vector4::operator+(const vector4& b) const noexcept {
		simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
		simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
		simd::_fm_vec4 ret = simd::fmVecAdd(veca, vecb);
		return vector4(ret);
	}

	const vector4 FM_CALL vector4::operator-(const vector4& b) const noexcept {
		simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
		simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);

		simd::_fm_vec4 ret = simd::fmVecSub(veca, vecb);
		return vector4(ret);
	}

	const vector4 FM_CALL vector4::operator*(const vector4& b) const noexcept {
		simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
		simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
		simd::_fm_vec4 ret = simd::fmVecMul(veca, vecb);
		return vector4(ret);
	}

	const vector4 FM_CALL vector4::operator/(const vector4& b) const noexcept {
		simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
		simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
		simd::_fm_vec4 ret = simd::fmVecDiv(veca, vecb);
		return vector4(ret);
	}

	const FMFLOAT FM_CALL vector4::dot(const vector4& b) const noexcept {
		simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
		simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
		return simd::fmVecDot(veca, vecb);
	}

	const vector4 FM_CALL vector4::cross(const vector4& b) const noexcept {
		simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
		simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
		simd::_fm_vec4 ret = simd::fmVec3Cross(veca, vecb);
		return vector4(ret);
	}

	FMFLOAT FM_CALL vector4::maxElement() const noexcept {
		simd::_fm_vec4 vec = simd::fmLoadVecP(__data._v);
		return simd::fmMaxElemOfVec(vec);
	}

	FMFLOAT FM_CALL vector4::minElement() const noexcept {
		simd::_fm_vec4 vec = simd::fmLoadVecP(__data._v);
		return simd::fmMinElemOfVec(vec);
	}

	FMFLOAT FM_CALL vector4::length() const noexcept {
		simd::_fm_vec4 vec = simd::fmLoadVecP(this->__data._v);
		FMFLOAT ff = simd::fmVecDot(vec, vec);
		return std::sqrt(ff);
	}

	vector4 FM_CALL vector4::square() const noexcept {
		simd::_fm_vec4 vec = simd::fmLoadVecP(this->__data._v);
		return vector4(simd::fmVecMul(vec, vec));
	}

	vector4 FM_CALL vector4::sqrt() const noexcept {
		simd::_fm_vec4 vec = simd::fmLoadVecP(this->__data._v);
		return simd::fmVecSqrt(vec);
	}

	vector4::vector4(const simd::fmAlignFLoat4& in) : __data(in) {}

	vector4::vector4(const simd::_fm_vec4& in)
	{
		simd::fmStroeVec(this->__data, in);
	}

	std::ostream& operator<<(std::ostream& out, const vector4& s) {
		out << "(" << s.__data._v[0] << "," << s.__data._v[1] << "," << s.__data._v[2]
			<< "," << s.__data._v[3] << ")";
		return out;
	}

	const vector4 FM_CALL operator*(const vector4& a, FMFLOAT b) noexcept {
		simd::_fm_vec4 veca = simd::fmLoadVecP(a.__data._v);
		simd::_fm_vec4 ret = simd::fmVecScale(veca, b);
		return vector4(ret);
	}

	const vector4 FM_CALL operator/(const vector4& a, FMFLOAT b) noexcept {
		FMFLOAT inv = ((FMFLOAT)1) / b;
		return a * inv;
	}

	const vector4 FM_CALL operator*(FMFLOAT b, const vector4& a) noexcept {
		return a * b;
	}

	bool FM_CALL hasNan(const vector4& in) noexcept {
		return std::isnan(in[0]) || std::isnan(in[1]) || std::isnan(in[2]) ||
			std::isnan(in[3]);
	}

} // namespace fm