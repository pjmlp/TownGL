LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

GLM_PATH := ../glm

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include $(LOCAL_PATH)/$(GLM_PATH)

# Application files
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	townsdl.cpp app.cpp world.cpp mesh.cpp diskprimitive.cpp boxprimitive.cpp \
	arcprimitive.cpp roofprimitive.cpp arctunnelprimitive.cpp primitive.cpp effect.cpp \
	tunnelprimitive.cpp windmillprimitive.cpp cylinderprimitive.cpp sailprimitive.cpp

LOCAL_SHARED_LIBRARIES := SDL2

LOCAL_LDLIBS := -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
