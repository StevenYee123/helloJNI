#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <jni.h>
//

#define gpio 124
#define IN 0
#define OUT 1
#define LOW 0
#define HIGH 1

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

    static int convertInt(int cols){
        return cols;
    }

JNIEXPORT jint JNICALL
Java_com_example_stevenyee_hellojni_MainActivity_rowsColumns(JNIEnv* env, jobject instance, jint rows, jint cols)
{
//    jint getCols = (*env)->SetIntField(env, "Columns",cols);
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
    printf("Hello");
//    int col = (int)cols;
 return cols;
}