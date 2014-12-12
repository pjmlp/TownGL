# Application build flags
APP_CPPFLAGS += -std=c++14 -DGLM_FORCE_RADIANS -Werror -Wall  -isystem jni/glm
APP_STL := gnustl_static
APP_ABI := armeabi-v7a x86

NDK_TOOLCHAIN_VERSION := 4.9