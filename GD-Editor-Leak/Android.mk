LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE          := cocos2dcpp
LOCAL_SRC_FILES := $(LOCAL_PATH)/lib/libcocos2dcpp.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/includes/cocos2d_x/

include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_CPP_FEATURES := rtti
LOCAL_MODULE := dobby
LOCAL_SRC_FILES := lib/libdobby.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include/libzip
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_CPP_FEATURES := rtti
LOCAL_MODULE := hooking
LOCAL_SHARED_LIBRARIES := dobby
LOCAL_SRC_FILES := lib/libhooking.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include/libzip
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := gdkit
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include/ $(LOCAL_PATH)/include/core $(LOCAL_PATH)/include/cocos2d_x/ $(LOCAL_PATH)/include/gd/

LOCAL_SRC_FILES:= src/inlineHook.c src/relocate.c src/gdmk.cpp src/main.cpp
LOCAL_LDLIBS := -llog
LOCAL_STATIC_LIBRARIES := cocos2dcpp hooking dobby

include $(BUILD_SHARED_LIBRARY)
