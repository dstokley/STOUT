LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := v4l2-compliance
LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS += -DNO_LIBV4L2
LOCAL_CFLAGS += -Wno-missing-braces
LOCAL_CFLAGS += -Wno-missing-field-initializers
LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../.. \
    $(LOCAL_PATH)/../../include \
<<<<<<< HEAD
    $(LOCAL_PATH)/../common \
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
    bionic \
    external/stlport/stlport

LOCAL_SHARED_LIBRARIES := libstlport

LOCAL_SRC_FILES := \
    v4l2-compliance.cpp v4l2-test-debug.cpp v4l2-test-input-output.cpp \
    v4l2-test-controls.cpp v4l2-test-io-config.cpp v4l2-test-formats.cpp \
<<<<<<< HEAD
    v4l2-test-buffers.cpp v4l2-test-codecs.cpp v4l2-test-colors.cpp
=======
    v4l2-test-buffers.cpp v4l2-test-codecs.cpp
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2

include $(BUILD_EXECUTABLE)
