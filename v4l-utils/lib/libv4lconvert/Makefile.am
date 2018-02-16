<<<<<<< HEAD
<<<<<<< HEAD
if WITH_DYN_LIBV4L
=======
if WITH_LIBV4L
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
lib_LTLIBRARIES = libv4lconvert.la
libv4lconvertpriv_PROGRAMS = ov511-decomp ov518-decomp
=======
if WITH_DYN_LIBV4L
lib_LTLIBRARIES = libv4lconvert.la
if HAVE_LIBV4LCONVERT_HELPERS
libv4lconvertpriv_PROGRAMS = ov511-decomp ov518-decomp
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
endif
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
include_HEADERS = ../include/libv4lconvert.h
pkgconfig_DATA = libv4lconvert.pc
LIBV4LCONVERT_VERSION = -version-info 0
else
noinst_LTLIBRARIES = libv4lconvert.la
endif

libv4lconvert_la_SOURCES = \
  libv4lconvert.c tinyjpeg.c sn9c10x.c sn9c20x.c pac207.c  mr97310a.c \
  flip.c crop.c jidctflt.c spca561-decompress.c \
  rgbyuv.c sn9c2028-decomp.c spca501.c sq905c.c bayer.c hm12.c \
  stv0680.c cpia1.c se401.c jpgl.c jpeg.c jl2005bcd.c \
  control/libv4lcontrol.c control/libv4lcontrol.h control/libv4lcontrol-priv.h \
  processing/libv4lprocessing.c processing/whitebalance.c processing/autogain.c \
  processing/gamma.c processing/libv4lprocessing.h processing/libv4lprocessing-priv.h \
<<<<<<< HEAD
<<<<<<< HEAD
  helper-funcs.h libv4lconvert-priv.h libv4lsyscall-priv.h \
=======
  helper.c helper-funcs.h libv4lconvert-priv.h libv4lsyscall-priv.h \
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
  helper.c helper-funcs.h libv4lconvert-priv.h libv4lsyscall-priv.h \
=======
  helper-funcs.h libv4lconvert-priv.h libv4lsyscall-priv.h \
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
  tinyjpeg.h tinyjpeg-internal.h
if HAVE_JPEG
libv4lconvert_la_SOURCES += jpeg_memsrcdest.c jpeg_memsrcdest.h
endif
<<<<<<< HEAD
<<<<<<< HEAD
if HAVE_LIBV4LCONVERT_HELPERS
libv4lconvert_la_SOURCES += helper.c
endif
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
if HAVE_LIBV4LCONVERT_HELPERS
libv4lconvert_la_SOURCES += helper.c
endif
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
libv4lconvert_la_CPPFLAGS = $(CFLAG_VISIBILITY) $(ENFORCE_LIBV4L_STATIC)
libv4lconvert_la_LDFLAGS = $(LIBV4LCONVERT_VERSION) -lrt -lm $(JPEG_LIBS) $(ENFORCE_LIBV4L_STATIC)

ov511_decomp_SOURCES = ov511-decomp.c

ov518_decomp_SOURCES = ov518-decomp.c

<<<<<<< HEAD
<<<<<<< HEAD
EXTRA_DIST = Android.mk
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
EXTRA_DIST = Android.mk
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
