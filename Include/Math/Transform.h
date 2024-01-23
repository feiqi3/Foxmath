#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "../FoxDef.h"

namespace fm {

class vector3;

class mat4;

fm::mat4 FM_CALL translate(const fm::vector3 &vector) FMTHROW;

fm::mat4 FM_CALL scale(const fm::vector3 &vector) FMTHROW;

fm::mat4 FM_CALL rotate(const fm::vector3 &axis, FMFLOAT angle) FMTHROW;

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
fm::mat4 FM_CALL perspectiveRHZO(FMFLOAT fovy, FMFLOAT aspect, FMFLOAT zNear,
                                 FMFLOAT zFar) FMTHROW;

mat4 FM_CALL perspectiveRHZO_InvZ(FMFLOAT fovy, FMFLOAT aspect, FMFLOAT zNear,
                                  FMFLOAT zFar);

fm::mat4 FM_CALL perspectiveRHNO_InvZ(FMFLOAT fovy, FMFLOAT aspect,
                                      FMFLOAT zNear, FMFLOAT zFar) FMTHROW;

fm::mat4 FM_CALL perspectiveRHNO(FMFLOAT fovy, FMFLOAT aspect, FMFLOAT zNear,
                                 FMFLOAT zFar) FMTHROW;

fm::mat4 FM_CALL perspectiveLHZO(FMFLOAT fovy, FMFLOAT aspect, FMFLOAT zNear,
                                 FMFLOAT zFar) FMTHROW;

fm::mat4 FM_CALL perspectiveLHNO(FMFLOAT fovy, FMFLOAT aspect, FMFLOAT zNear,
                                 FMFLOAT zFar) FMTHROW;

fm::mat4 FM_CALL orthoLH_InvZ(FMFLOAT const &left, FMFLOAT const &right,
                              FMFLOAT const &bottom, FMFLOAT const &top,
                              FMFLOAT const &zNear,
                              FMFLOAT const &zFar) FMTHROW;

fm::mat4 FM_CALL orthoLHZO(FMFLOAT const &left, FMFLOAT const &right,
                         FMFLOAT const &bottom, FMFLOAT const &top,
                         FMFLOAT const &zNear, FMFLOAT const &zFar) FMTHROW;

fm::mat4 FM_CALL orthoLHNO(FMFLOAT const &left, FMFLOAT const &right,
                         FMFLOAT const &bottom, FMFLOAT const &top,
                         FMFLOAT const &zNear, FMFLOAT const &zFar) FMTHROW;


fm::mat4 FM_CALL orthoRHZO_InvZ(FMFLOAT const &left, FMFLOAT const &right,
                              FMFLOAT const &bottom, FMFLOAT const &top,
                              FMFLOAT const &zNear,
                              FMFLOAT const &zFar) FMTHROW;

fm::mat4 FM_CALL orthoRHZO(FMFLOAT const &left, FMFLOAT const &right,
                         FMFLOAT const &bottom, FMFLOAT const &top,
                         FMFLOAT const &zNear, FMFLOAT const &zFar) FMTHROW;

fm::mat4 FM_CALL orthoRHNO(FMFLOAT const &left, FMFLOAT const &right,
                         FMFLOAT const &bottom, FMFLOAT const &top,
                         FMFLOAT const &zNear, FMFLOAT const &zFar) FMTHROW;


fm::mat4 FM_CALL orthoRHNO_InvZ(FMFLOAT const &left, FMFLOAT const &right,
                              FMFLOAT const &bottom, FMFLOAT const &top,
                              FMFLOAT const &zNear,
                              FMFLOAT const &zFar) FMTHROW;

} // namespace fm

#endif