# FoxMath

## Introduction  
A mini 3D math library with basic vector/matrix operation written by C++11.  
Currently support x86 architecture, optimized by SSE, AVX2 instructions.     

## How to use    

Firstly, use cmake to generate project on your system.  
FoxMath has several compile options.   
- `FOX_USE_FLOAT`, Tell FoxMath to use float32 as the main element of vector/matrix.  
- `FOX_USE_DOUBLE`, Tell FoxMath to use float64 as the main element of vector/matrix.   
- `FOX_AVX_SUPPORT`, Need CPU support AVX2,tell FoxMath to use AVX or SSE to optimize code. 
- `FOX_SSE_SUPPORT`, Need CPU support SSE4.1 ,tell FoxMath to use SSE to optimize code (only under float32 mode).  
- `FOX_FORCE_PURE`, Force FoxMath to use pure soft code to do vector operation, low performance.    
- `FOX_DEBUG`, Open debug mode for FoxMath and some extra checks and symbols will be add to FoxMath when set to 'ON', And will open release mode when set to 'OFF'.

Under command line, these options can be set like below. In this example, I used double as FoxMath's element type and enabled avx2 support for it.    
```shell  
mkdir build
cd build
cmake ../ -DFOX_USE_DOUBLE=on -DFOX_USE_FLOAT=off  -DFOX_AVX_SUPPORT=on  
```    

Then compile it. When using g++ you will get "libFoxMath.a". Or you will get "FoxMath.lib" under target binary folder like "Debug" when using Visual Studio.    

Copy the lib file and the Header folder to your project folder, then link the lib and add Header to include folder.   

If use float as main element, Macro "FOX_USE_FLOAT" should be defined before including FoxMath header.    

If use double as main element, Macro "FOX_USE_DOUBLE" should be defined.
