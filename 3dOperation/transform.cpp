#include "transform.h"  

#include "../vector/vector3.h"

#include "../matrix/matrix4x4.h"
#include <vcruntime_string.h>

namespace fm {

fm::mat4 FM_CALL translate(const fm::mat4 &in, const fm::vector3 &vector){
    mat4 tmp = mat4::identity();
    tmp[0][3] = vector[0];
    tmp[1][3] = vector[1];
    tmp[2][3] = vector[2];
    return tmp * in;
}

fm::mat4 FM_CALL scale(const fm::mat4 &in, const fm::vector3 &vector){
    mat4 tmp = mat4::identity();
    tmp[0][0] *= vector[0];
    tmp[1][1] *= vector[1];
    tmp[2][2] *= vector[2];
    tmp[3][3] *= vector[3];
    return tmp * in;
}

fm::mat4 FM_CALL rotate(const fm::mat4 &in, const fm::vector3 &axis,
                        FMFLOAT angle){
                            //TODO: 
                        }

}