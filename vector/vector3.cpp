#include "vector3.h"
#include "../base/fox_avx.h"
#include "../base/fox_pure.h"
#include "../base/fox_sse.h"
namespace fm {
	fm::vector3::vector3() :__data({ 0,0,0,0 })
	{
	}

	fm::vector3::vector3(const FMFLOAT* in)
	{
		memcpy(__data._v, in, 3 * sizeof(FMFLOAT));
		__data._v[3] = 0;
	}

	vector3::vector3(const simd::fmAlignFLoat4& in)
	{
		memcpy(this->__data._v, in._v, 4 * sizeof(FMFLOAT));
		__data._v[3] = 0;
	}

	vector3::vector3(const simd::_fm_vec4& in)
	{
		simd::fmStroeVec(this->__data, in);
	}

	fm::vector3::vector3(const fm::vector3& in) FMTHROW {
		memcpy(this->__data._v, in.__data._v, 3 * sizeof(FMFLOAT));
	}

	FMFLOAT& FM_CALL  vector3::operator[](size_t t) FMTHROW {
#ifdef FM_DEBUG
		assert(t <= 2 && t >= 0);
#endif // FM_DEBUG
		return __data._v[t];
	}

	const vector3  FM_CALL vector3::operator+(const vector3& b) const FMTHROW {
		auto a = simd::fmLoadVecP(this->__data._v);
		auto bb = simd::fmLoadVecP(b.__data._v);
		return simd::fmVecAdd(a, bb);
	}

	const vector3  FM_CALL vector3::operator-(const vector3& b) const FMTHROW {
		auto a = simd::fmLoadVecP(this->__data._v);
		auto bb = simd::fmLoadVecP(b.__data._v);
		return simd::fmVecSub(a, bb);
	}

	const vector3  FM_CALL vector3::operator*(const vector3& b) const FMTHROW {
		auto a = simd::fmLoadVecP(this->__data._v);
		auto bb = simd::fmLoadVecP(b.__data._v);
		return simd::fmVecMul(a, bb);
	}

	const vector3  FM_CALL vector3::operator/(const vector3& b) const FMTHROW {
		auto a = simd::fmLoadVecP(this->__data._v);
		auto bb = simd::fmLoadVecP(b.__data._v);
		return simd::fmVecDiv(a, bb);
	}

	std::ostream& fm::operator<<(std::ostream& out, const vector3& s)
	{
		out << "(" << s.__data._v[0] << "," << s.__data._v[1] << "," << s.__data._v[2]
			<< ")";
		return out;
	}

	const vector3 FM_CALL fm::operator*(const vector3& a, FMFLOAT b) FMTHROW
	{
		auto bb = simd::fmSpreadVec(b);
		auto aa = simd::fmLoadVecP(a.__data._v);
	}



	const FMFLOAT& FM_CALL vector3::operator[](size_t t) const FMTHROW
	{
#ifdef FM_DEBUG
		assert(t <= 2 && t >= 0);
#endif // FM_DEBUG
		return __data._v[t];
	}


	const vector3 FM_CALL vector3::operator+(const vector3& b) const FMTHROW {
		simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
		simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
		simd::_fm_vec4 ret = simd::fmVecAdd(veca, vecb);
		return vector3(ret);
	}

	const vector3 FM_CALL vector3::operator-(const vector3& b) const FMTHROW {
		simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
		simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);

		simd::_fm_vec4 ret = simd::fmVecSub(veca, vecb);
		return vector3(ret);
	}

	const vector3 FM_CALL vector3::operator*(const vector3& b) const FMTHROW {
		simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
		simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
		simd::_fm_vec4 ret = simd::fmVecMul(veca, vecb);
		return vector3(ret);
	}

	const vector3 FM_CALL vector3::operator/(const vector3& b) const FMTHROW {
		simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
		simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
		simd::_fm_vec4 ret = simd::fmVecDiv(veca, vecb);
		return vector3(ret);
	}

	const FMFLOAT FM_CALL vector3::dot(const vector3& b) const FMTHROW {
#ifdef FM_DEBUG
		assert(__data._v[3] == 0 && b.__data._v[3] == 0);
#endif // FM_DEBUG

		simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
		simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
		return simd::fmVecDot(veca, vecb);
	}

	const vector3 FM_CALL vector3::cross(const vector3& b) const FMTHROW {
		simd::_fm_vec4 veca = simd::fmLoadVecP(__data._v);
		simd::_fm_vec4 vecb = simd::fmLoadVecP(b.__data._v);
		simd::_fm_vec4 ret = simd::fmVec3Cross(veca, vecb);
		return vector3(ret);
	}

	FMFLOAT FM_CALL vector3::maxElement() const FMTHROW {
		simd::_fm_vec4 vec = simd::fmLoadVec(__data._v[0], __data._v[1], __data._v[2], std::numeric_limits<FMFLOAT>::min());
		return simd::fmMaxElemOfVec(vec);
	}

	FMFLOAT FM_CALL vector3::minElement() const FMTHROW {
		simd::_fm_vec4 vec = simd::fmLoadVec(__data._v[0], __data._v[1], __data._v[2], std::numeric_limits<FMFLOAT>::max());
		return simd::fmMinElemOfVec(vec);
	}

	FMFLOAT FM_CALL vector3::length() const FMTHROW {
#ifdef FM_DEBUG
		assert(__data._v[3] == 0);
#endif // FM_DEBUG
		simd::_fm_vec4 vec = simd::fmLoadVecP(this->__data._v);
		FMFLOAT ff = simd::fmVecDot(vec, vec);
		return std::sqrt(ff);
	}

	vector3 FM_CALL vector3::square() const FMTHROW {
		simd::_fm_vec4 vec = simd::fmLoadVecP(this->__data._v);
		return vector3(simd::fmVecMul(vec, vec));
	}

	vector3 FM_CALL vector3::sqrt() const FMTHROW {
#ifdef FM_DEBUG
		assert(__data._v[3] == 0);
#endif // FM_DEBUG
		simd::_fm_vec4 vec = simd::fmLoadVecP(this->__data._v);
		return simd::fmVecSqrt(vec);
	}


	const vector3 FM_CALL operator*(const vector3& a, FMFLOAT b) FMTHROW {
		simd::_fm_vec4 veca = simd::fmLoadVecP(a.__data._v);
		simd::_fm_vec4 ret = simd::fmVecScale(veca, b);
		return vector3(ret);
	}

	const vector3 FM_CALL operator/(const vector3& a, FMFLOAT b) FMTHROW {
		FMFLOAT inv = ((FMFLOAT)1) / b;
		return a * inv;
	}

	const vector3 FM_CALL operator*(FMFLOAT b, const vector3& a) FMTHROW {
		return a * b;
	}

	bool FM_CALL hasNan(const vector3& in) FMTHROW {
		return std::isnan(in[0]) || std::isnan(in[1]) || std::isnan(in[2]);
	}
}