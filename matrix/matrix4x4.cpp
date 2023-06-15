#include "./matrix4x4.h"

namespace fm {
	mat4::mat4() :__data{ vector4(0,0,0,0),vector4(0,0,0,0),vector4(0,0,0,0),vector4(0,0,0,0) }
	{}

	mat4::mat4(FMFLOAT _m00, FMFLOAT _m01, FMFLOAT _m02, FMFLOAT _m03, FMFLOAT _m10, FMFLOAT _m11, FMFLOAT _m12, FMFLOAT _m13, FMFLOAT _m20, FMFLOAT _m21, FMFLOAT _m22, FMFLOAT _m23, FMFLOAT _m30, FMFLOAT _m31, FMFLOAT _m32, FMFLOAT _m33)
		:__data{ vector4(_m00,_m01,_m02,_m03),vector4(_m10,_m11,_m12,_m13),vector4(_m20,_m21,_m22,_m23),vector4(_m30,_m31,_m32,_m33) }
	{
	}

	mat4::mat4(const vector4& vec0, const vector4& vec1, const vector4& vec2, const vector4& vec3)
		:__data{ vec0,vec1,vec2,vec3 }
	{
	}

	mat4::mat4(const std::initializer_list<FMFLOAT>& in)
	{
#if defined(FM_DEBUG)
		assert(in.size() == 16);
#endif
		auto lp = in.begin();
		for (char i = 0; i < 3; i++)
		{
			for (char j = 0; j < 3; j++, ++lp)
			{
				__data[i][j] = *lp;
			}
		}
	}
}