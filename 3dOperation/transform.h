#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "../base/basic_def.h"

namespace fm {

class vector3;

class mat4;

fm::mat4 FM_CALL translate(const fm::mat4 &in, const fm::vector3 &vector)FMTHROW;

fm::mat4 FM_CALL scale(const fm::mat4 &in, const fm::vector3 &vector)FMTHROW;

fm::mat4 FM_CALL rotate(const fm::mat4 &in, const fm::vector3 &axis,
                        FMFLOAT angle)FMTHROW;

fm::mat4 FM_CALL rotate_around_x(FMFLOAT angle)FMTHROW;

fm::mat4 FM_CALL rotate_around_y(FMFLOAT angle)FMTHROW;

fm::mat4 FM_CALL rotate_around_z(FMFLOAT angle)FMTHROW;

} // namespace fm

#endif