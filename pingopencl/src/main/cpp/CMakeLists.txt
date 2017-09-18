cmake_minimum_required(VERSION 3.4.1)

add_library(pingopencl-jni SHARED
            pingopencl-jni.c)

include_directories("C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v8.0\\include")

# Include libraries needed for pingopencl-jni lib
target_link_libraries(pingopencl-jni
                      android
                      log)
