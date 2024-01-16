#pragma once
#include "basic_def.h"
namespace fm {
    class VecBase{
        public:
        void* operator new(size_t size){
            return FM_ALIGN_MALLOC(size);
        }
    };
}