<<<<<<< HEAD
if WITH_DYN_LIBV4L
=======
if WITH_LIBV4L
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
lib_LTLIBRARIES = libv4l2.la
include_HEADERS = ../include/libv4l2.h ../include/libv4l-plugin.h
pkgconfig_DATA = libv4l2.pc
LIBV4L2_VERSION = -version-info 0
if WITH_V4L_WRAPPERS
libv4l2priv_LTLIBRARIES = v4l2convert.la

install-exec-hook:
<<<<<<< HEAD
	$(mkdir_p) $(DESTDIR)/$(libdir)
=======
	$(MKDIR_P) $(DESTDIR)/$(libdir)
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
	(cd $(DESTDIR)/$(libdir) && rm -f v4l2convert.so && $(LN_S) $(libv4l2subdir)/v4l2convert.so v4l2convert.so)

endif
else
noinst_LTLIBRARIES = libv4l2.la
endif

<<<<<<< HEAD
libv4l2_la_SOURCES = libv4l2.c log.c libv4l2-priv.h
if WITH_V4L_PLUGINS
libv4l2_la_SOURCES += v4l2-plugin.c
endif

=======
libv4l2_la_SOURCES = libv4l2.c v4l2-plugin.c log.c libv4l2-priv.h
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
libv4l2_la_CPPFLAGS = $(CFLAG_VISIBILITY) $(ENFORCE_LIBV4L_STATIC)
libv4l2_la_LDFLAGS = $(LIBV4L2_VERSION) -lpthread $(DLOPEN_LIBS) $(ENFORCE_LIBV4L_STATIC)
libv4l2_la_LIBADD = ../libv4lconvert/libv4lconvert.la

v4l2convert_la_SOURCES = v4l2convert.c
v4l2convert_la_LIBADD = libv4l2.la
v4l2convert_la_LDFLAGS = -avoid-version -module -shared -export-dynamic
v4l2convert_la_LIBTOOLFLAGS = --tag=disable-static
<<<<<<< HEAD

EXTRA_DIST = Android.mk v4l2-plugin-android.c
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
