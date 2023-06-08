#ifndef FOX_SSE_H_
#define FOX_SSE_H_
#include "basic_def.h"
#if defined (_FM_SSE4_) && defined (_FM_USE_FLOAT)

namespace fm{

namespace simd {
_fm_vec4 FM_INLINE FM_CALL fmLoadVecP(const FMFLOAT* ps){
    //SSE Intinsics need 16 mem align
    #if defined (FM_DEBUG)
        MEM_ALIGN_CHECK(ps, 16);
    #endif
    return _mm_load_ps(ps);
}

_fm_vec4 FM_INLINE FM_CALL fmLoadVec(FMFLOAT a,FMFLOAT b,FMFLOAT c,FMFLOAT d){
    //In memory, its layout is like :
    // | a | b | c | d |
   return _mm_set_ps(d, c, b, a);
}

void FM_INLINE FM_CALL fmStroeVec(fmAlignFLoat4& ps,_fm_vec4 vec){
    _mm_store_ps(ps._v, vec);
}

FMFLOAT FM_INLINE FM_CALL fmGetElem(const _fm_vec4& vec,int pos){
    #if defined (FM_DEBUG)
        assert(pos >= 0 && pos <= 3);
    #endif
    fmAlignFLoat4 temp;
    fmStroeVec(temp, vec);
    return temp[pos];
}

_fm_vec4 FM_INLINE FM_CALL fmSpreadVec(FMFLOAT t){
    //_mm_broadcast_ss(&t) -> is a avx intrinsic, much faster than below
    return _mm_set1_ps(t);
}

_fm_vec4 FM_INLINE FM_CALL fmVecAdd(const _fm_vec4& veca,const _fm_vec4& vecb){
    return _mm_add_ps(veca,vecb);
}

_fm_vec4 FM_INLINE FM_CALL fmVecScale(const _fm_vec4& veca,FMFLOAT factor){
    return _mm_mul_ps(veca, fmSpreadVec(factor));
}

_fm_vec4 FM_INLINE FM_CALL fmVecMul(const _fm_vec4& veca,const _fm_vec4& vecb){
    return _mm_mul_ps(veca, vecb);
}

_fm_vec4 FM_INLINE FM_CALL fmVecSub(const _fm_vec4& veca,const _fm_vec4& vecb){
    return _mm_sub_ps(veca, vecb);
}

_fm_vec4 FM_INLINE FM_CALL fmVecDiv(const _fm_vec4& veca,const _fm_vec4& vecb){
    return _mm_div_ps(veca,vecb);
}

_fm_vec4 FM_INLINE FM_CALL fmVecCeil(const _fm_vec4& vec){
    return _mm_ceil_ps(vec);
}

_fm_vec4 FM_INLINE FM_CALL fmVecFloor(const _fm_vec4& vec){
    return _mm_floor_ps(vec);
}

_fm_vec4 FM_INLINE FM_CALL fmVecMaxOfEachElem(const _fm_vec4& veca,const _fm_vec4& vecb){
    return _mm_max_ps(veca, vecb);
}

_fm_vec4 FM_INLINE FM_CALL fmVecMinOfEachElem(const _fm_vec4& veca,const _fm_vec4& vecb){
    return _mm_min_ps(veca, vecb);
}

FMFLOAT FM_INLINE FM_CALL fmMaxElemOfVec(const _fm_vec4& vec){
        _fm_vec4 temp = vec;
    temp = _mm_shuffle_epi32(temp,_MM_SHUFFLE(0,1,2,3));
    /*
    origin:   | 3 | 2 | 1 | 0 |
    premuted: | 0 | 1 | 2 | 3 |
    */
    temp = fmVecMaxOfEachElem(temp,vec);
    /*
    temp:  | max(3,0) | max(2,1) | max(2,1) | max(3,0) |
    temp1: | max(2,1) | max(3,0) | max(3,0) | max(2,1) |
    */
    _fm_vec4 temp1 = _mm_shuffle_epi32(temp,_MM_SHUFFLE(2,3,0,1));
    temp =fmVecMaxOfEachElem(temp1, temp);
    /*
    | max | max | max | max |
    */
    return fmGetElem(temp, 0);
}

FMFLOAT FM_INLINE FM_CALL fmMinElemOfVec(const _fm_vec4& vec){
    _fm_vec4 temp = vec;
    temp = _mm_shuffle_epi32(temp,_MM_SHUFFLE(0,1,2,3));
    /*
    origin:   | 3 | 2 | 1 | 0 |
    premuted: | 0 | 1 | 2 | 3 |
    */
    temp = fmVecMinOfEachElem(temp,vec);
    /*
    temp:  | min(3,0) | min(2,1) | min(2,1) | min(3,0) |
    temp1: | min(2,1) | min(3,0) | min(3,0) | min(2,1) |
    */
    _fm_vec4 temp1 = _mm_shuffle_epi32(temp,_MM_SHUFFLE(2,3,0,1));
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
   _fm_vec4 temp1 = _mm_shuffle_epi32(temp,_MM_SHUFFLE(0, 1, 2, 3));

   // tmp:    | 3+0 | 2+1 | 1+2 | 0+3 |
   // temp1:  | 2+1 | 3+0 | 0+3 | 1+2 |

    temp = fmVecAdd(temp, temp1);
    temp1 = _mm_shuffle_epi32(temp,_MM_SHUFFLE(2, 3, 0, 1));
    return temp1;
*/

    _fm_vec4 ab = fmVecMul(veca, vecb);

    //veca(a,b,c,d) vecb(e,f,g,h)
    //_mm256_hadd_pd(veca,vecb) => (a+b,c+d,e+f,g+h)

    _fm_vec4 temp = _mm_hadd_ps(ab,ab);
    _fm_vec4 shuffle = _mm_shuffle_epi32(temp,_MM_SHUFFLE(0,1,2,3));
    return fmGetElem(fmVecAdd(shuffle, temp),0);
}

_fm_vec4 FM_INLINE FM_CALL fmVecSqrt(const _fm_vec4& vec){
    return _mm_sqrt_pd(vec);
}

//Two vec3 cross product
_fm_vec4 FM_INLINE FM_CALL fmVec3Cross(const _fm_vec4& veca,const _fm_vec4& vecb){
/*
//Naive version
//a.yzx * b.zxy - a.zxy * b.yzx
    _fm_vec4 aYZX = _mm_shuffle_epi32(veca,_MM_SHUFFLE(2, 1, 3, 0));
    _fm_vec4 aZXY = _mm_shuffle_epi32(veca,_MM_SHUFFLE(1, 3, 2, 0));
    _fm_vec4 bZXY = _mm_shuffle_epi32(vecb,_MM_SHUFFLE(1, 3, 2, 0));
    _fm_vec4 bYZX = _mm_shuffle_epi32(vecb,_MM_SHUFFLE(2, 1, 3, 0));
    return fmVecSub( fmVecMul(aYZX, bZXY) ,fmVecMul(aZXY, bYZX) );
*/
//Faster version, one shuffle less
    _fm_vec4 aYZX = _mm_shuffle_epi32(veca,_MM_SHUFFLE(2, 1, 3, 0));
    _fm_vec4 bYZX = _mm_shuffle_epi32(veca,_MM_SHUFFLE(2, 1, 3, 0));
    _fm_vec4 c = _mm_sub_pd(
        _mm_mul_pd(veca, bYZX),
        _mm_mul_pd(aYZX, vecb)
        );
    return _mm_shuffle_epi32(c,_MM_SHUFFLE(2, 1, 3, 0)); 
}

FMFLOAT FM_INLINE FM_CALL fmVec2Cross(const _fm_vec4& veca, const _fm_vec4& vecb){
    _fm_vec4 bYX = _mm_shuffle_epi32(veca,_MM_SHUFFLE(2, 3, 1, 0));
    _fm_vec4 temp = _mm_mul_pd(bYX, veca);
    _fm_vec4 hSub = _mm_hsub_pd(temp, temp);
    return fmGetElem(hSub, 0);
} 

FMFLOAT FM_INLINE FM_CALL fmVecSum(const _fm_vec4& vec){
    _fm_vec4 temp = _mm_shuffle_epi32(vec,_MM_SHUFFLE(0,1,2,3));
    _fm_vec4 sum = fmVecAdd(temp, vec);
    temp = _mm_hadd_epi32(sum,sum);
    return fmGetElem(temp, 0);
}

}
}
#endif

#endif//FOX_SSE_H_