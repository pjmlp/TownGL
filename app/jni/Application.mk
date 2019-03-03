# Application build flags
APP_CPPFLAGS += -std=c++14 -DGLM_FORCE_RADIANS -Werror -Wall  -isystem jni/glm
APP_STL := c++_static
APP_ABI := arm64-v8a