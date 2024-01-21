#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "../FoxDef.h"

namespace fm {

class vector3;

class mat4;

fm::mat4 FM_CALL translate(const fm::vector3 &vector) FMTHROW;

fm::mat4 FM_CALL scale(const fm::vector3 &vector) FMTHROW;

fm::mat4 FM_CALL rotate(const fm::vector3 &axis, FMFLOAT angle) FMTHROW;

fm::mat4 FM_CALL rotate_mat_around_x(FMFLOAT angle) FMTHROW;

fm::mat4 FM_CALL rotate_mat_around_y(FMFLOAT angle) FMTHROW;

fm::mat4 FM_CALL rotate_mat_around_z(FMFLOAT angle) FMTHROW;

fm::mat4 FM_CALL lookAt(const vector3 &Eye, const vector3 &Center,
                        const vector3 &up);

fm::mat4 FM_CALL perspective(FMFLOAT fovy, FMFLOAT aspect, FMFLOAT zNear,
                             FMFLOAT zFar) FMTHROW;

fm::mat4 FM_CALL ortho(FMFLOAT const &left, FMFLOAT const &right,
                       FMFLOAT const &bottom, FMFLOAT const &top,
                       FMFLOAT const &zNear, FMFLOAT const &zFar) FMTHROW;
} // namespace fm

#endif