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



-------------------------------------------------------------------------------------------            
这个库原本是作为我毕业设计中数学计算的基石，但就现在看来，这个库也仅仅只能满足毕设，它存在很多不经推敲的漏洞。比如说：   
1. 缺少vec2，fvec，ivec，半精度类型，目前是都用double做计算，但是shader中的double计算一般是作为拓展的，存在跨平台的不确定性，还有内存占用过大的问题        
2. 对于vec3，目前其在内存上的分布实际上和vec4是一样的，也就是说会带来内存上的不紧凑，虽然d3d11确实需要这个功能，但是....还是通用点吧                  
3. 工程组织的过于随意了，特别是文件夹文件和类名...我原本在用的时候都很想吐槽自己     
4. 对于低精度但快速的函数需要和高精度函数做出些许区分     

最近我对Vulkan简单封装快到了尾声，也就意味着我要开始去写渲染器的上层了，这时候数学库的修改成了急切需求，目前底下的任务列表我尽量会保持一星期一个的速度去完成，分为必须和额外，额外的任务我可能不会实现，一切都看我的实际需求。       
毕竟目前还是以我的vk渲染器优先                

----------------------------------------------------------------------------------------------        


TODO List:     
These are musts      
1. a more compact memory alignment for vec3.        
2. support for vec2.     
3. support for fvec4, fvec3, fvec2 (aka fp32)       
3. support for hvec4, hvec3, hvec2 (aka half precision)     

These are optionals    
1. support for ivec     
2. simd optimaize on ARM      
3. math func on AABB 


