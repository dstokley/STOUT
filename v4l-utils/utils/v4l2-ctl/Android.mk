LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := v4l2-ctl
LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS += -DNO_LIBV4L2
LOCAL_CFLAGS += -Wno-missing-field-initializers
LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../.. \
    $(LOCAL_PATH)/../../include \
<<<<<<< HEAD
<<<<<<< HEAD
    $(LOCAL_PATH)/../common \
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
    $(LOCAL_PATH)/../common \
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
    bionic \
    external/stlport/stlport

LOCAL_SHARED_LIBRARIES := libstlport

LOCAL_SRC_FILES := \
    v4l2-ctl.cpp v4l2-ctl.h v4l2-ctl-common.cpp v4l2-ctl-tuner.cpp \
    v4l2-ctl-io.cpp v4l2-ctl-stds.cpp v4l2-ctl-vidcap.cpp v4l2-ctl-vidout.cpp \
    v4l2-ctl-overlay.cpp v4l2-ctl-vbi.cpp v4l2-ctl-selection.cpp v4l2-ctl-misc.cpp \
<<<<<<< HEAD
<<<<<<< HEAD
    v4l2-ctl-streaming.cpp v4l2-ctl-sdr.cpp v4l2-ctl-edid.cpp v4l2-ctl-modes.cpp \
    v4l2-tpg-colors.c v4l2-tpg-core.c v4l-stream.c
=======
    v4l2-ctl-streaming.cpp v4l2-ctl-test-patterns.cpp v4l2-ctl-sdr.cpp \
    v4l2-ctl-edid.cpp

>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
    v4l2-ctl-streaming.cpp v4l2-ctl-test-patterns.cpp v4l2-ctl-sdr.cpp \
    v4l2-ctl-edid.cpp

=======
    v4l2-ctl-streaming.cpp v4l2-ctl-sdr.cpp v4l2-ctl-edid.cpp v4l2-ctl-modes.cpp \
    v4l2-tpg-colors.c v4l2-tpg-core.c v4l-stream.c
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
include $(BUILD_EXECUTABLE)
