cmake_minimum_required(VERSION 3.10)
project(FoxMath CXX)
set (CMAKE_EXPORT_COMPILE_COMMANDS 1)

if(NOT "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU|MSVC")
    message(FATAL_ERROR "You are using a compiler not supported by FoxMath, you are using ${CMAKE_CXX_COMPILER_ID}")
endif(NOT "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU|MSVC")

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU")
#No use 
elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC" )
    #https://learn.microsoft.com/en-us/cpp/build/reference/zc-cplusplus?view=msvc-170
    message("Compile flags add \'/Zc:__cplusplus\'")
    endif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU")

option(FOX_SSE_SUPPORT "Enable sse support for programe." OFF)
option(FOX_AVX_SUPPORT "Enable avx/sse support for programe." OFF)
option(FOX_FORCE_PURE "Disable simd support for programe." OFF)
option(FOX_USE_FLOAT "Use float as vector element." OFF)
option(FOX_USE_DOUBLE "Use double as vector elements." OFF)
option(FOX_DEBUG "Use double as vector elements." OFF)

#Open this will add some check for FoxMath
if (FOX_DEBUG)
message("FoxMath debug mode now.")
add_definitions(-DFM_DEBUG)

    if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU")

    set(CMAKE_CXX_FLAGS "-g -fomit-frame-pointer ${CMAKE_CXX_FLAGS}")
    message("Compile flags add \'-g\'")
    message("Compile flags add \'-fomit-frame-pointer\'")

    else()
    set(CMAKE_CXX_FLAGS "/DEBUG:FULL /Oy /Zi ${CMAKE_CXX_FLAGS}")
    message("Compile flags add \'/DEBUG:FULL\'")
    message("Compile flags add \'/Oy\'")
    endif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU")

else()
message("FoxMath release mode now.")

#release

    if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU")
    set(CMAKE_CXX_FLAGS "-O3 ${CMAKE_CXX_FLAGS}")
    message("Compile flags add \'-O3\'")
    else()
    set(CMAKE_CXX_FLAGS "/Ox /Oi ${CMAKE_CXX_FLAGS}")
    message("Compile flags add \'/Ox\'")
    message("Compile flags add \'/Oi\'")
    endif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU")

endif(FOX_DEBUG)

#FoxMath use float as its vector element
if (FOX_USE_FLOAT)
    message("FoxMath use float as vector elements now.")
    add_definitions(-DFOX_USE_FLOAT)
    
    if(NOT FOX_FORCE_PURE AND ( FOX_SSE_SUPPORT OR FOX_AVX_SUPPORT))
        message("SSE instructions will be used.")
        # GNU/Clang sse flag and msvc sse flag
        if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU")
            set(CMAKE_CXX_FLAGS "-msse4.2 ${CMAKE_CXX_FLAGS}")
            message("Compile flags add \'-msse4.2\'")
        elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
            set(CMAKE_CXX_FLAGS "/arch:SSE2 /arch:AVX ${CMAKE_CXX_FLAGS}")
            message("Compile flags add \'/arch:SSE2\'")
            message("Compile flags add \'/arch:AVX\'")
            endif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU")
    else()
    #If float but no sse support then use pure mode
        set(FM_PURE on)
    endif(NOT FOX_FORCE_PURE AND ( FOX_SSE_SUPPORT OR FOX_AVX_SUPPORT))

else()
    message("FoxMath use double as vector elements now.")
    add_definitions(-DFOX_USE_DOUBLE)

    if(FOX_AVX_SUPPORT AND NOT FOX_FORCE_PURE )
        message("AVX2 instructions will be used.")
        # GNU/Clang AVX2 flag and msvc AVX2 flag
        if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU")
            set(CMAKE_CXX_FLAGS "-mavx2 ${CMAKE_CXX_FLAGS}")
            message("Compile flags add \'-mavx2\'")
        elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
            set(CMAKE_CXX_FLAGS "/arch:AVX2 ${CMAKE_CXX_FLAGS}")
            message("Compile flags add \'/arch:AVX2\'")
        endif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU")
    else()
    #If use double but no avx support then use pure mode
        set(FM_PURE on)
    endif(FOX_AVX_SUPPORT AND NOT FOX_FORCE_PURE)
endif(FOX_USE_FLOAT)

if(FM_PURE OR FOX_FORCE_PURE)
    add_definitions(-DFOX_PURE)
    message(WARNING "No simd instructions will be used.")
endif(FM_PURE OR FOX_FORCE_PURE)



file(GLOB SRC_LIST   "base/*.h" "base/*.hpp" "base/*.cpp" "vector/*.h" "vector/*.cpp" "matrix/*.h" "matrix/*.cpp")
add_library(FoxMath STATIC ${SRC_LIST})
enable_testing()
add_subdirectory(test)
