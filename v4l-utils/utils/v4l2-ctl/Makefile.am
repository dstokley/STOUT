<<<<<<< HEAD
bin_PROGRAMS = v4l2-ctl
man_MANS = v4l2-ctl.1
DEFS :=
=======
bin_PROGRAMS = cx18-ctl ivtv-ctl v4l2-ctl

cx18_ctl_SOURCES = cx18-ctl.c

ivtv_ctl_SOURCES = ivtv-ctl.c
ivtv_ctl_LDFLAGS = -lm
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2

v4l2_ctl_SOURCES = v4l2-ctl.cpp v4l2-ctl.h v4l2-ctl-common.cpp v4l2-ctl-tuner.cpp \
	v4l2-ctl-io.cpp v4l2-ctl-stds.cpp v4l2-ctl-vidcap.cpp v4l2-ctl-vidout.cpp \
	v4l2-ctl-overlay.cpp v4l2-ctl-vbi.cpp v4l2-ctl-selection.cpp v4l2-ctl-misc.cpp \
<<<<<<< HEAD
	v4l2-ctl-streaming.cpp v4l2-ctl-sdr.cpp v4l2-ctl-edid.cpp v4l2-ctl-modes.cpp \
	v4l2-tpg-colors.c v4l2-tpg-core.c v4l-stream.c v4l2-ctl-meta.cpp
v4l2_ctl_CPPFLAGS = -I$(top_srcdir)/utils/common

if WITH_V4L2_CTL_LIBV4L
v4l2_ctl_LDADD = ../../lib/libv4l2/libv4l2.la ../../lib/libv4lconvert/libv4lconvert.la -lrt -lpthread
else
DEFS += -DNO_LIBV4L2
endif

if !WITH_V4L2_CTL_STREAM_TO
DEFS += -DNO_STREAM_TO
endif

EXTRA_DIST = Android.mk v4l2-ctl.1
=======
	v4l2-ctl-streaming.cpp v4l2-ctl-test-patterns.cpp v4l2-ctl-sdr.cpp \
	v4l2-ctl-edid.cpp
v4l2_ctl_LDADD = ../../lib/libv4l2/libv4l2.la ../../lib/libv4lconvert/libv4lconvert.la
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
