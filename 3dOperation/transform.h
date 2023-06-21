#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "../base/basic_def.h"

namespace fm {

class vector3;

class mat4;

fm::mat4 FM_CALL translate(const fm::mat4 &in, const fm::vector3 &vector);

fm::mat4 FM_CALL scale(const fm::mat4 &in, const fm::vector3 &vector);

fm::mat4 FM_CALL rotate(const fm::mat4 &in, const fm::vector3 &axis,
                        FMFLOAT angle);

fm::mat4 FM_CALL rotate_around_x(FMFLOAT angle);

fm::mat4 FM_CALL rotate_around_y(FMFLOAT angle);

fm::mat4 FM_CALL rotate_around_z(FMFLOAT angle);

} // namespace fm

#endif