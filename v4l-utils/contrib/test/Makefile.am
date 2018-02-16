noinst_PROGRAMS = \
	ioctl-test		\
	sliced-vbi-test		\
	sliced-vbi-detect	\
<<<<<<< HEAD
<<<<<<< HEAD
=======
	vbi-test 		\
	v4lgrab			\
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	v4l2grab		\
	driver-test		\
=======
	v4l2grab		\
	driver-test		\
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
	mc_nextgen_test		\
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	stress-buffer		\
	capture-example

if HAVE_X11
noinst_PROGRAMS += pixfmt-test
endif

if HAVE_GLU
noinst_PROGRAMS += v4l2gl
endif

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
if HAVE_SDL
noinst_PROGRAMS += sdlcam
endif

<<<<<<< HEAD
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
driver_test_SOURCES = driver-test.c
driver_test_LDADD = ../../utils/libv4l2util/libv4l2util.la

pixfmt_test_SOURCES = pixfmt-test.c
pixfmt_test_CFLAGS = $(X11_CFLAGS)
pixfmt_test_LDFLAGS = $(X11_LIBS)

v4l2grab_SOURCES = v4l2grab.c
<<<<<<< HEAD
<<<<<<< HEAD
=======
v4l2grab_LDADD = ../../lib/libv4l2/libv4l2.la ../../lib/libv4lconvert/libv4lconvert.la

v4l2gl_SOURCES = v4l2gl.c
v4l2gl_LDFLAGS = $(X11_LIBS) $(GL_LIBS) $(GLU_LIBS)
v4l2gl_LDADD = ../../lib/libv4l2/libv4l2.la ../../lib/libv4lconvert/libv4lconvert.la

=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
v4l2grab_LDFLAGS = $(ARGP_LIBS)
v4l2grab_LDADD = ../../lib/libv4l2/libv4l2.la ../../lib/libv4lconvert/libv4lconvert.la -lpthread

v4l2gl_SOURCES = v4l2gl.c
v4l2gl_LDFLAGS = $(X11_LIBS) $(GL_LIBS) $(GLU_LIBS) $(ARGP_LIBS)
v4l2gl_LDADD = ../../lib/libv4l2/libv4l2.la ../../lib/libv4lconvert/libv4lconvert.la

sdlcam_LDFLAGS = $(JPEG_LIBS) $(SDL2_LIBS) -lm -ldl -lrt
sdlcam_CFLAGS = -I../.. $(SDL2_CFLAGS)
sdlcam_LDADD = ../../lib/libv4l2/libv4l2.la  ../../lib/libv4lconvert/libv4lconvert.la

mc_nextgen_test_CFLAGS = $(LIBUDEV_CFLAGS)
mc_nextgen_test_LDFLAGS = $(LIBUDEV_LIBS)


<<<<<<< HEAD
=======
v4l2grab_LDADD = ../../lib/libv4l2/libv4l2.la ../../lib/libv4lconvert/libv4lconvert.la

v4l2gl_SOURCES = v4l2gl.c
v4l2gl_LDFLAGS = $(X11_LIBS) $(GL_LIBS) $(GLU_LIBS)
v4l2gl_LDADD = ../../lib/libv4l2/libv4l2.la ../../lib/libv4lconvert/libv4lconvert.la

>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
ioctl_test_SOURCES = ioctl-test.c ioctl-test.h ioctl_32.h ioctl_64.h

sliced_vbi_test_SOURCES = sliced-vbi-test.c

sliced_vbi_detect_SOURCES = sliced-vbi-detect.c

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
vbi_test_SOURCES = vbi-test.c

v4lgrab_SOURCES = v4lgrab.c

<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
stress_buffer_SOURCES = stress-buffer.c

capture_example_SOURCES = capture-example.c

ioctl-test.c: ioctl-test.h

sync-with-kernel:
	./gen_ioctl_list.pl --gen_ioctl_numbers >.tmp_ioctl.c
	gcc -I ../../include/ .tmp_ioctl.c -o tmp_ioctl32 -m32
	gcc -I ../../include/ .tmp_ioctl.c -o tmp_ioctl64 -m64
	./tmp_ioctl32 32 >ioctl_32.h
	./tmp_ioctl64 64 >ioctl_64.h
	rm .tmp_ioctl.c tmp_ioctl32 tmp_ioctl64
	./gen_ioctl_list.pl >ioctl-test.h

EXTRA_DIST = \
	gen_ioctl_list.pl
