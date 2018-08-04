LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := ase_1
LOCAL_SRC_FILES := jni_1.c jni_1_util.c

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := ase_2
LOCAL_SRC_FILES := jni_2.c jni_2_util.c

include $(BUILD_SHARED_LIBRARY)
