<<<<<<< HEAD
<<<<<<< HEAD
if WITH_DYN_LIBV4L
=======
if WITH_LIBV4L
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
if WITH_LIBV4L
=======
if WITH_DYN_LIBV4L
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
lib_LTLIBRARIES = libv4l2rds.la
include_HEADERS = ../include/libv4l2rds.h
pkgconfig_DATA = libv4l2rds.pc
LIBV4L2RDS_VERSION = -version-info 0
else
noinst_LTLIBRARIES = libv4l2rds.la
endif

libv4l2rds_la_SOURCES = libv4l2rds.c
libv4l2rds_la_CPPFLAGS = $(CFLAG_VISIBILITY) $(ENFORCE_LIBV4L_STATIC)
libv4l2rds_la_LDFLAGS = $(LIBV4L2RDS_VERSION) -lpthread $(ENFORCE_LIBV4L_STATIC)
