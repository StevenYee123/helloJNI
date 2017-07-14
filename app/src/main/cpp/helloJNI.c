#include <string.h>
#include <jni.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define gpio 124
#define IN 0
#define OUT 1
#define LOW 0
#define HIGH 1

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   hello-jni/app/src/main/java/com/example/hellojni/HelloJni.java
 */

static int GPIODirection (int pin, int dir)
{
    static const char s_directions_str[] = "in\0out";
#define DIRECTION_MAX 35
    char path[DIRECTION_MAX];
    int fd;
    
    snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
    fd = open(path, O_WRONLY);
    if(-1 == fd)
    {
        printf("Failed to open file direction");
        return(-1);
    }

    if(-1 == write(fd, &s_directions_str[IN == dir ? 0 : 3], IN == dir ? 2 : 3))
    {
        printf("Failed to write direction");
        return(-1);
    }

    close(fd);
    return (0);
}

static int GPIOWrite (int pin, int value)
{
#define VALUE_MAX 30

    static const char s_values_str[] = "01";
    char path[VALUE_MAX];
    int fd;

    snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
    fd = open(path, O_WRONLY);
    if(-1 == fd)
    {
        printf("Failed to open file value");
        return(-1);
    }

    if(-1 == write(fd, &s_values_str[LOW == value? 0: 1], 1))
    {
        printf("Failed to write value");
        return(-1);
    }

    close(fd);
    return(0);
}

JNIEXPORT jstring JNICALL
Java_com_example_stevenyee_hellojni_MainActivity_helloJNI( JNIEnv* env,
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

    if(-1 == GPIODirection(gpio, OUT))
    {
        printf("Direction main failed 1");
        return (*env)->NewStringUTF(env, "Dir open failed.");
    }
//	else if(-2 == GPIODirection(gpio, OUT))
//    {
//        printf("Direction main failed 2");
//        return (*env)->NewStringUTF(env, "Dir open failed 2");
//    }
    if(-1 == GPIOWrite(gpio, HIGH) )
    {
        printf("Write file open failed");
        return (*env)->NewStringUTF(env, "Write open failed. 1");
    }

    sleep(5);

    if(-1 == GPIOWrite(gpio, LOW))
    {
        printf("Write open failed");
        return(*env)->NewStringUTF(env, "Write open failed. 2");
    }

    sleep(5);

    if(-1 == GPIOWrite(gpio, HIGH))
    {
        printf("write open failed");
        return(*env)->NewStringUTF(env, "write open failed. 3");
    }
//    if(-4 == GPIOWrite(gpio, HIGH))
    return (*env)->NewStringUTF(env, "GPIO toggle finished");
}
