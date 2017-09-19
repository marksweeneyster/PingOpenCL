cmake_minimum_required(VERSION 3.4.1)

add_library(pingopencl-jni SHARED
            pingopencl-jni.c)

# CL folder with OpenCL headers is in CMake root
include_directories(${CMAKE_SOURCE_DIR})


# Include libraries needed for pingopencl-jni lib
target_link_libraries(pingopencl-jni
                      android
                      log)
