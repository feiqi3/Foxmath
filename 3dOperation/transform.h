#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "../base/basic_def.h"

namespace fm {

class vector3;

class mat4;

fm::mat4 FM_CALL translate(const fm::vector3 &vector)FMTHROW;

fm::mat4 FM_CALL scale(const fm::vector3 &vector)FMTHROW;

fm::mat4 FM_CALL rotate(const fm::vector3 &axis,
                        FMFLOAT angle)FMTHROW;

fm::mat4 FM_CALL rotateX_LH(FMFLOAT angle) FMTHROW;
fm::mat4 FM_CALL rotateX_RH(FMFLOAT angle) FMTHROW;
fm::mat4 FM_CALL rotateY_LH(FMFLOAT angle) FMTHROW;
fm::mat4 FM_CALL rotateY_RH(FMFLOAT angle) FMTHROW;
fm::mat4 FM_CALL rotateZ_LH(FMFLOAT angle) FMTHROW;
fm::mat4 FM_CALL rotateZ_RH(FMFLOAT angle) FMTHROW;

fm::mat4 FM_CALL lookAtRH(const vector3 &eye, const vector3 &center,
                          const vector3 &up);
fm::mat4 FM_CALL lookAtLH(const vector3 &eye, const vector3 &center,
                          const vector3 &up);
fm::mat4 FM_CALL perspectiveRH(FMFLOAT fovy, FMFLOAT aspect, FMFLOAT zNear,
                               FMFLOAT zFar) FMTHROW;

mat4 FM_CALL perspectiveRH_InvZ(FMFLOAT fovy, FMFLOAT aspect, FMFLOAT zNear,
                                FMFLOAT zFar);

fm::mat4 FM_CALL perspectiveLH(FMFLOAT fovy, FMFLOAT aspect, FMFLOAT zNear,
                               FMFLOAT zFar) FMTHROW;

fm::mat4 FM_CALL perspectiveLH_InvZ(FMFLOAT fovy, FMFLOAT aspect, FMFLOAT zNear,
                                    FMFLOAT zFar) FMTHROW;

fm::mat4 FM_CALL orthoLH_InvZ(FMFLOAT const &left, FMFLOAT const &right,
                              FMFLOAT const &bottom, FMFLOAT const &top,
                              FMFLOAT const &zNear,
                              FMFLOAT const &zFar) FMTHROW;

fm::mat4 FM_CALL orthoLH(FMFLOAT const &left, FMFLOAT const &right,
                         FMFLOAT const &bottom, FMFLOAT const &top,
                         FMFLOAT const &zNear, FMFLOAT const &zFar) FMTHROW;

fm::mat4 FM_CALL orthoRH_InvZ(FMFLOAT const &left, FMFLOAT const &right,
                              FMFLOAT const &bottom, FMFLOAT const &top,
                              FMFLOAT const &zNear,
                              FMFLOAT const &zFar) FMTHROW;

fm::mat4 FM_CALL orthoRH(FMFLOAT const &left, FMFLOAT const &right,
                         FMFLOAT const &bottom, FMFLOAT const &top,
                         FMFLOAT const &zNear, FMFLOAT const &zFar) FMTHROW;
} // namespace fm

#endif