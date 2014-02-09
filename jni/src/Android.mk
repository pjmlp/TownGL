LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

GLM_PATH := ../glm

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include $(LOCAL_PATH)/$(GLM_PATH)

# Application files
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	townsdl.cpp town.cpp world.cpp mesh.cpp diskprimitive.cpp boxprimitive.cpp \
	arcprimitive.cpp roofprimitive.cpp arctunnelprimitive.cpp buildingprimitive.cpp \
	primitive.cpp floorprimitive.cpp tunnelprimitive.cpp roadprimitive.cpp windmillprimitive.cpp \
	cylinderprimitive.cpp

LOCAL_SHARED_LIBRARIES := SDL2

LOCAL_LDLIBS := -lGLESv1_CM -llog

include $(BUILD_SHARED_LIBRARY)
