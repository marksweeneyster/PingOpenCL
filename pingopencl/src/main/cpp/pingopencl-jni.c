/**
 * This is based on the hello-jni Android example
 */

#include <string.h>
#include <jni.h>
#include <dlfcn.h>
#include <stdio.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

JNIEXPORT jstring JNICALL
Java_org_oedteq_pingopencl_PingOpenCL_stringFromJNI( JNIEnv* env,
                                                  jobject thiz )
{
#if defined(__arm__)
    #if defined(__ARM_ARCH_7A__)
    #if defined(__ARM_NEON__)
      #if defined(__ARM_PCS_VFP)
        #define ABI "armeabi-v7a/NEON (hard-float)"
      #else
        #define ABI "armeabi-v7a/NEON"
      #endif
    #else
      #if defined(__ARM_PCS_VFP)
        #define ABI "armeabi-v7a (hard-float)"
      #else
        #define ABI "armeabi-v7a"
      #endif
    #endif
  #else
   #define ABI "armeabi"
  #endif
#elif defined(__i386__)
#define ABI "x86"
#elif defined(__x86_64__)
#define ABI "x86_64"
#elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
#define ABI "mips64"
#elif defined(__mips__)
#define ABI "mips"
#elif defined(__aarch64__)
#define ABI "arm64-v8a"
#else
#define ABI "unknown"
#endif

    void* handle = dlopen("/vendor/lib/libOpenCL.so", RTLD_LAZY);

    if (!handle) {
        return (*env)->NewStringUTF(env, "Hello from PingOpenCL !\n load OpenCL FAIL.\n Compiled with ABI " ABI ".");
    } else {
        cl_device_id device_id = NULL;
        cl_context context = NULL;
        cl_command_queue command_queue = NULL;
        cl_mem memobj = NULL;
        cl_program program = NULL;
        cl_kernel kernel = NULL;
        cl_platform_id platform_id = NULL;
        cl_uint ret_num_devices;
        cl_uint ret_num_platforms;
        cl_int ret;

        cl_int (*getPlatformIdCount)(cl_uint,cl_platform_id *,cl_uint *);

        getPlatformIdCount = dlsym(handle, "clGetPlatformIDs");

        ret = (*getPlatformIdCount)(1, &platform_id, &ret_num_platforms);

        char str [16];

        sprintf(str, "%d", ret_num_platforms);

        dlclose(handle);

        jstring count = str;

        return (*env)->NewStringUTF(env, "Hello from PingOpenCL !\n load OpenCL SUCCESS.\n Compiled with ABI " ABI ".");
    }
}
