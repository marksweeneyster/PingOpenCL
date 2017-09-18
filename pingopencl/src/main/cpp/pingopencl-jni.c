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
        return (*env)->NewStringUTF(env, "PingOpenCL: load OpenCL FAIL.\n Compiled with ABI " ABI ".");
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

        char name[1024];
        char version[1024];
        char driver[1024];

        char rtnString[2048];

        cl_int (*getPlatformIdCount)(cl_uint,cl_platform_id *,cl_uint *);
        cl_int (*getDeviceIDs)(cl_platform_id,cl_device_type,cl_uint,cl_device_id *,cl_uint *);
        cl_int (*getDeviceInfo)(cl_device_id    /* device */,
                        cl_device_info  /* param_name */,
                        size_t          /* param_value_size */,
                        void *          /* param_value */,
                        size_t *        /* param_value_size_ret */);

        getPlatformIdCount = dlsym(handle, "clGetPlatformIDs");
        getDeviceIDs       = dlsym(handle, "clGetDeviceIDs");
        getDeviceInfo      = dlsym(handle, "clGetDeviceInfo");

        ret = (*getPlatformIdCount)(1, &platform_id, &ret_num_platforms);

        char str [16];

        sprintf(str, "%d", ret_num_platforms);

        ret = (*getDeviceIDs)(platform_id, CL_DEVICE_TYPE_GPU,1,&device_id,&ret_num_devices);

        ret = getDeviceInfo(device_id, CL_DEVICE_NAME, sizeof(name), name, NULL);
        ret = getDeviceInfo(device_id, CL_DEVICE_VERSION, sizeof(version), version, NULL);
        ret = getDeviceInfo(device_id, CL_DRIVER_VERSION, sizeof(driver), driver, NULL);

        sprintf(rtnString,"PingOpenCL load OpenCL SUCCESS.\n");
        sprintf(rtnString+strlen(rtnString),"Compiled with ABI %s.\n\n", ABI);
        sprintf(rtnString+strlen(rtnString),"GPU\n");
        sprintf(rtnString+strlen(rtnString)," - Name: %s\n", name);
        sprintf(rtnString+strlen(rtnString)," - Version: %s\n", version);
        sprintf(rtnString+strlen(rtnString)," - Driver: %s\n", driver);

        dlclose(handle);

        return (*env)->NewStringUTF(env, rtnString);
    }
}
