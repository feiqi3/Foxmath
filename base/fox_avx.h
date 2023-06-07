#ifndef FOX_AVX_H__
#define FOX_AVX_H__
#include "FoxMath.h"
#include"basic_def.h"

#if defined (_FM_AVX2_)

_fm_vec4 FM_INLINE FM_CALL fmLoadVecP(const FMFLOAT* pd){
    //AVX Intinsics need 32 mem align
    #if defined (FM_DEBUG)
        MEM_ALIGN_CHECK(pd, 32);
    #endif
   return _mm256_load_pd(pd);
}



_fm_vec4 FM_INLINE FM_CALL fmLoadVec(double a,double b,double c,double d){
    //In memory, its layout is like :
    // | a | b | c | d |
    return _mm256_set_pd(d, c, b, a);
}

void FM_INLINE FM_CALL fmStroeVec(FMFLOAT * pd,_fm_vec4 vec){
    _mm256_store_pd(pd, vec);
}

FMFLOAT FM_INLINE FM_CALL fmGetElem(const _fm_vec4& vec,int pos){
    #if defined (FM_DEBUG)
        assert(pos >= 0 && pos <= 3);
    #endif
    //May get a bad asm
    /*return ((double*)(&vec))[pos];*/
    
    //Use intrinsic to get element
    FMFLOAT temp[4];
    fmStroeVec(temp,vec);
    return temp[pos];
}

//https://www.intel.com/content/www/us/en/docs/cpp-compiler/developer-guide-reference/2021-8/mm256-broadcast-sd.html
//Loads scalar double-precision floating-point values from the specified address a, and broadcasts it to all four elements in the destination vector.
_fm_vec4 FM_INLINE FM_CALL fmSpreadVec(FMFLOAT t){
     return _mm256_broadcast_sd(&t);
}

_fm_vec4 FM_INLINE FM_CALL fmVecAdd(const _fm_vec4& veca,const _fm_vec4& vecb){
    return _mm256_add_pd(veca, vecb);
}

_fm_vec4 FM_INLINE FM_CALL fmVecScale(const _fm_vec4& veca,FMFLOAT factor){
    return _mm256_mul_pd(veca, fmSpreadVec(factor));
}

_fm_vec4 FM_INLINE FM_CALL fmVecMul(const _fm_vec4& veca,const _fm_vec4& vecb){
    return _mm256_mul_pd(veca, vecb);
}

_fm_vec4 FM_INLINE FM_CALL fmVecSub(const _fm_vec4& veca,const _fm_vec4& vecb){
    return _mm256_sub_pd(veca,vecb);
}

_fm_vec4 FM_INLINE FM_CALL fmVecDiv(const _fm_vec4& veca,const _fm_vec4& vecb){
    return _mm256_div_pd(veca, vecb);
}

_fm_vec4 FM_INLINE FM_CALL fmVecCeil(const _fm_vec4& vec){
    return  _mm256_ceil_pd(vec);
}

_fm_vec4 FM_INLINE FM_CALL fmVecFloor(const _fm_vec4& vec){
    return _mm256_floor_pd(vec);
}

_fm_vec4 FM_INLINE FM_CALL fmVecMaxOfEachElem(const _fm_vec4& veca,const _fm_vec4& vecb){
    return _mm256_max_pd(veca, vecb);
}

_fm_vec4 FM_INLINE FM_CALL fmVecMinOfEachElem(const _fm_vec4& veca,const _fm_vec4& vecb){
    return _mm256_min_pd(veca, vecb);
}


FMFLOAT FM_INLINE FM_CALL fmMaxElemOfVec(const _fm_vec4& vec){
    _fm_vec4 temp = vec;
    temp = _mm256_permute4x64_pd(temp,_MM_SHUFFLE(0,1,2,3));
    /*
    origin:   | 3 | 2 | 1 | 0 |
    premuted: | 0 | 1 | 2 | 3 |
    */
    temp = fmVecMaxOfEachElem(temp,vec);
    /*
    temp:  | max(3,0) | max(2,1) | max(2,1) | max(3,0) |
    temp1: | max(2,1) | max(3,0) | max(3,0) | max(2,1) |
    */
    _fm_vec4 temp1 = _mm256_permute4x64_pd(temp,_MM_SHUFFLE(2,3,0,1));
    temp =fmVecMaxOfEachElem(temp1, temp);
    /*
    | max | max | max | max |
    */
    return fmGetElem(temp, 0);
}


FMFLOAT FM_INLINE FM_CALL fmMinElemOfVec(const _fm_vec4& vec){
    _fm_vec4 temp = vec;
    temp = _mm256_permute4x64_pd(temp,_MM_SHUFFLE(0,1,2,3));
    /*
    origin:   | 3 | 2 | 1 | 0 |
    premuted: | 0 | 1 | 2 | 3 |
    */
    temp = fmVecMinOfEachElem(temp,vec);
    /*
    temp:  | min(3,0) | min(2,1) | min(2,1) | min(3,0) |
    temp1: | min(2,1) | min(3,0) | min(3,0) | min(2,1) |
    */
    _fm_vec4 temp1 = _mm256_permute4x64_pd(temp,_MM_SHUFFLE(2,3,0,1));
    temp =fmVecMinOfEachElem(temp1, temp);
    /*
    | min | min | min | min |
    */
    return fmGetElem(temp, 0);
}

FMFLOAT FM_INLINE FM_CALL fmVecDot(const _fm_vec4& veca,const _fm_vec4& vecb){

/*    
   // origin:   | 3 | 2 | 1 | 0 |
   // premuted: | 0 | 1 | 2 | 3 |

   _fm_vec4 temp = fmVecMul(veca, vecb);
   _fm_vec4 temp1 = _mm256_permute4x64_pd(temp,_MM_SHUFFLE(0, 1, 2, 3));

   // tmp:    | 3+0 | 2+1 | 1+2 | 0+3 |
   // temp1:  | 2+1 | 3+0 | 0+3 | 1+2 |

    temp = fmVecAdd(temp, temp1);
    temp1 = _mm256_permute4x64_pd(temp,_MM_SHUFFLE(2, 3, 0, 1));
    return temp1;
*/

    _fm_vec4 ab = fmVecMul(veca, vecb);

    //veca(a,b,c,d) vecb(e,f,g,h)
    //_mm256_hadd_pd(veca,vecb) => (a+b,c+d,e+f,g+h)

    _fm_vec4 temp = _mm256_hadd_pd(ab,ab);
    _fm_vec4 shuffle = _mm256_permute4x64_pd(temp,_MM_SHUFFLE(0,1,2,3));
    return fmGetElem(fmVecAdd(shuffle, temp),0);
}

_fm_vec4 FM_INLINE FM_CALL fmVecSqrt(const _fm_vec4& vec){
    return _mm256_sqrt_pd(vec);
}

//Two vec3 cross product
_fm_vec4 FM_INLINE FM_CALL fmVec3Cross(const _fm_vec4& veca,const _fm_vec4& vecb){
/*
//Naive version
//a.yzx * b.zxy - a.zxy * b.yzx
    _fm_vec4 aYZX = _mm256_permute4x64_pd(veca,_MM_SHUFFLE(2, 1, 3, 0));
    _fm_vec4 aZXY = _mm256_permute4x64_pd(veca,_MM_SHUFFLE(1, 3, 2, 0));
    _fm_vec4 bZXY = _mm256_permute4x64_pd(vecb,_MM_SHUFFLE(1, 3, 2, 0));
    _fm_vec4 bYZX = _mm256_permute4x64_pd(vecb,_MM_SHUFFLE(2, 1, 3, 0));
    return fmVecSub( fmVecMul(aYZX, bZXY) ,fmVecMul(aZXY, bYZX) );
*/
//Faster version, one shuffle less
    _fm_vec4 aYZX = _mm256_permute4x64_pd(veca,_MM_SHUFFLE(2, 1, 3, 0));
    _fm_vec4 bYZX = _mm256_permute4x64_pd(veca,_MM_SHUFFLE(2, 1, 3, 0));
    _fm_vec4 c = _mm256_sub_pd(
        _mm256_mul_pd(veca, bYZX),
        _mm256_mul_pd(aYZX, vecb)
        );
    return _mm256_permute4x64_pd(c,_MM_SHUFFLE(2, 1, 3, 0)); 
}

FMFLOAT FM_INLINE FM_CALL fmVec2Cross(const _fm_vec4& veca, const _fm_vec4& vecb){
    _fm_vec4 bYX = _mm256_permute4x64_pd(veca,_MM_SHUFFLE(2, 3, 1, 0));
    _fm_vec4 temp = _mm256_mul_pd(bYX, veca);
    _fm_vec4 hSub = _mm256_hsub_pd(temp, temp);
    return fmGetElem(hSub, 0);
} 

#endif

#endif