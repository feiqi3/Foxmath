cmake_minimum_required(VERSION 3.10)
project(FOXMATH CXX)
set (CMAKE_EXPORT_COMPILE_COMMANDS 1)

if(NOT "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU|MSVC")
    message(FATAL_ERROR "You are using a compiler not supported by FoxMath, you are using ${CMAKE_CXX_COMPILER_ID}")
endif(NOT "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU|MSVC")

#Set C++ standard to 17
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU")
    set(CMAKE_CXX_FLAGS "-std=c++17 ${CMAKE_CXX_FLAGS}")
    message("Compile flags add \'-std=c++17\'")

elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC" )
    set(CMAKE_CXX_FLAGS "/std:c++17 ${CMAKE_CXX_FLAGS}")
    message("Compile flags add \'/std:c++17\'")
endif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU")

option(FM_SSE_SUPPORT "Enable sse support for programe." OFF)
option(FM_AVX_SUPPORT "Enable avx support for programe." OFF)
option(FM_FORCE_PURE "Enable avx support for programe." OFF)
option(FM_USE_FLOAT "Use float as vector element." OFF)
option(FM_USE_DOUBLE "Use double as vector elements." OFF)

#FoxMath use float as its vector element
if (FM_USE_FLOAT)
    message("FoxMath use float as vector elements now.")
    add_definitions(-D_FM_USE_FLOAT)
    
    if(NOT FM_FORCE_PURE AND ( FM_SSE_SUPPORT OR FM_AVX_SUPPORT))
        message("SSE instructions will be used.")
        # GNU/Clang sse flag and msvc sse flag
        if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU")
            set(CMAKE_CXX_FLAGS "-msse4.2 ${CMAKE_CXX_FLAGS}")
            message("Compile flags add \'-msse4.2\'")
        elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
            set(CMAKE_CXX_FLAGS "/arch:SSE2 ${CMAKE_CXX_FLAGS}")
            message("Compile flags add \'/arch:SSE2\'")
        endif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU")
    else()
    #If float but no sse support then use pure mode
        set(FM_PURE on)
    endif(NOT FM_FORCE_PURE AND ( FM_SSE_SUPPORT OR FM_AVX_SUPPORT))

else()
    message("FoxMath use double as vector elements now.")
    add_definitions(-D_FM_USE_DOUBLE)

    if(FM_AVX_SUPPORT AND NOT FM_FORCE_PURE )
        message("AVX2 instructions will be used.")
        # GNU/Clang AVX2 flag and msvc AVX2 flag
        if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU")
            set(CMAKE_CXX_FLAGS "-mavx2 ${CMAKE_CXX_FLAGS}")
            message("Compile flags add \'-mavx2\'")
        elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
            set(CMAKE_CXX_FLAGS "/arch:SSE2 ${CMAKE_CXX_FLAGS}")
            message("Compile flags add \'/arch:SSE2\'")
        endif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU")
    else()
    #If double but no avx support then use pure mode
        set(FM_PURE on)
    endif(FM_AVX_SUPPORT AND NOT FM_FORCE_PURE)
endif(FM_USE_FLOAT)

if(FM_PURE OR FM_FORCE_PURE)
    add_definitions(-D_FM_PURE_)
    message(WARNING "No simd instructions will be used.")
endif(FM_PURE OR FM_FORCE_PURE)



file(GLOB SRC_LIST   "base/*.h" "base/*.hpp" "base/*.cpp")
add_library(FOXMATH ${SRC_LIST})
enable_testing()
add_subdirectory(test)