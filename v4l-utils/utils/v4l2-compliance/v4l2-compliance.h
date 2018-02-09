/*
    V4L2 API compliance test tool.

    Copyright (C) 2008, 2010  Hans Verkuil <hverkuil@xs4all.nl>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335  USA
 */

#ifndef _V4L2_COMPLIANCE_H_
#define _V4L2_COMPLIANCE_H_

#include <stdarg.h>
#include <cerrno>
#include <string>
#include <list>
#include <set>
#include <linux/videodev2.h>

#ifndef NO_LIBV4L2
#include <libv4l2.h>
#else
#define v4l2_open(file, oflag, ...) (-1)
#define v4l2_close(fd) (-1)
#define v4l2_read(fd, buffer, n) (-1)
#define v4l2_write(fd, buffer, n) (-1)
#define v4l2_ioctl(fd, request, ...) (-1)
#define v4l2_mmap(start, length, prot, flags, fd, offset) (MAP_FAILED)
#define v4l2_munmap(_start, length) (-1)
#endif

#include <cv4l-helpers.h>

#if !defined(ENODATA) && (defined(__FreeBSD__) || defined(__FreeBSD_kernel__))
#define ENODATA ENOTSUP
#endif

extern bool show_info;
extern bool show_warnings;
extern bool wrapper;
extern int kernel_version;
extern unsigned warnings;

struct test_queryctrl: v4l2_queryctrl {
	__u64 menu_mask;
};

typedef std::list<test_queryctrl> qctrl_list;
typedef std::set<__u32> pixfmt_set;

struct node;

struct node {
	struct v4l_fd vfd;
	bool is_video;
	bool is_radio;
	bool is_vbi;
	bool is_sdr;
	bool is_m2m;
	bool is_planar;
	bool can_capture;
	bool can_output;
	const char *device;
	unsigned caps;
	struct node *node2;	/* second open filehandle */
	bool has_outputs;
	bool has_inputs;
	unsigned tuners;
	unsigned modulators;
	unsigned inputs;
	unsigned audio_inputs;
	unsigned outputs;
	unsigned audio_outputs;
	unsigned std_controls;
	unsigned priv_controls;
	qctrl_list controls;
	__u32 fbuf_caps;
	pixfmt_set buftype_pixfmts[V4L2_BUF_TYPE_SDR_CAPTURE + 1];
	__u32 valid_buftypes;
	__u32 valid_buftype;
	__u32 valid_memorytype;
};

#define info(fmt, args...) 					\
	do {							\
		if (show_info)					\
 			printf("\t\tinfo: " fmt, ##args);	\
	} while (0)

#define warn(fmt, args...) 					\
	do {							\
		warnings++;					\
		if (show_warnings)				\
 			printf("\t\twarn: %s(%d): " fmt, __FILE__, __LINE__, ##args);	\
	} while (0)

#define fail(fmt, args...) 						\
({ 									\
 	printf("\t\tfail: %s(%d): " fmt, __FILE__, __LINE__, ##args);	\
	1;								\
})

#define fail_on_test(test) 				\
	do {						\
	 	if (test)				\
			return fail("%s\n", #test);	\
	} while (0)

static inline int test_open(const char *file, int oflag)
{
 	return wrapper ? v4l2_open(file, oflag) : open(file, oflag);
}

static inline int test_close(int fd)
{
	return wrapper ? v4l2_close(fd) : close(fd);
}

static inline void reopen(struct node *node)
{
	test_close(node->vfd.fd);
	if ((node->vfd.fd = test_open(node->device, O_RDWR)) < 0) {
		fprintf(stderr, "Failed to open %s: %s\n", node->device,
			strerror(errno));
		exit(1);
	}
}

static inline ssize_t test_read(int fd, void *buffer, size_t n)
{
	return wrapper ? v4l2_read(fd, buffer, n) : read(fd, buffer, n);
}

static inline ssize_t test_write(int fd, const void *buffer, size_t n)
{
	return wrapper ? v4l2_write(fd, buffer, n) : write(fd, buffer, n);
}

static inline int test_ioctl(int fd, unsigned long cmd, ...)
{
	void *arg;
	va_list ap;

	va_start(ap, cmd);
	arg = va_arg(ap, void *);
	va_end(ap);
	return wrapper ? v4l2_ioctl(fd, cmd, arg) : ioctl(fd, cmd, arg);
}

static inline void *test_mmap(void *start, size_t length, int prot, int flags,
		int fd, int64_t offset)
{
 	return wrapper ? v4l2_mmap(start, length, prot, flags, fd, offset) :
		mmap(start, length, prot, flags, fd, offset);
}

static inline int test_munmap(void *start, size_t length)
{
 	return wrapper ? v4l2_munmap(start, length) : munmap(start, length);
}

static inline int check_fract(const struct v4l2_fract *f)
{
	if (f->numerator && f->denominator)
		return 0;
	return 1;
}

static inline double fract2f(const struct v4l2_fract *f)
{
	return (double)f->numerator / (double)f->denominator;
}

int doioctl_name(struct node *node, unsigned long int request, void *parm,
		 const char *name, bool no_wrapper = false);
#define doioctl(n, r, p) doioctl_name(n, r, p, #r)
#define doioctl_no_wrap(n, r, p) doioctl_name(n, r, p, #r, true)

std::string cap2s(unsigned cap);
std::string buftype2s(int type);
static inline std::string buftype2s(enum v4l2_buf_type type)
{
       return buftype2s((int)type);
}

const char *ok(int res);
int check_string(const char *s, size_t len);
int check_ustring(const __u8 *s, int len);
int check_0(const void *p, int len);

// Debug ioctl tests
int testRegister(struct node *node);
int testLogStatus(struct node *node);

// Input ioctl tests
int testTuner(struct node *node);
int testTunerFreq(struct node *node);
int testTunerHwSeek(struct node *node);
int testEnumInputAudio(struct node *node);
int testInput(struct node *node);
int testInputAudio(struct node *node);

// Output ioctl tests
int testModulator(struct node *node);
int testModulatorFreq(struct node *node);
int testEnumOutputAudio(struct node *node);
int testOutput(struct node *node);
int testOutputAudio(struct node *node);

// Control ioctl tests
int testQueryControls(struct node *node);
int testSimpleControls(struct node *node);
int testExtendedControls(struct node *node);
int testControlEvents(struct node *node);
int testJpegComp(struct node *node);

// I/O configuration ioctl tests
int testStd(struct node *node);
int testTimings(struct node *node);
int testTimingsCap(struct node *node);
int testEdid(struct node *node);

// Format ioctl tests
int testEnumFormats(struct node *node);
int testParm(struct node *node);
int testFBuf(struct node *node);
int testGetFormats(struct node *node);
int testTryFormats(struct node *node);
int testSetFormats(struct node *node);
int testSlicedVBICap(struct node *node);

// Codec ioctl tests
int testEncoder(struct node *node);
int testEncIndex(struct node *node);
int testDecoder(struct node *node);

// Buffer ioctl tests
int testReqBufs(struct node *node);
int testReadWrite(struct node *node);
int testExpBuf(struct node *node);
int testMmap(struct node *node, unsigned frame_count);
int testUserPtr(struct node *node, unsigned frame_count);
int testDmaBuf(struct node *expbuf_node, struct node *node, unsigned frame_count);

#endif
