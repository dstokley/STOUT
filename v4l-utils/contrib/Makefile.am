if LINUX_OS
<<<<<<< HEAD
SUBDIRS = test
=======
SUBDIRS = test xc3028-firmware

if HAVE_LINUX_I2C_DEV
SUBDIRS += \
	rds-saa6588
endif

>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
else
SUBDIRS = freebsd
endif

<<<<<<< HEAD
EXTRA_DIST = \
	parse-sniffusb2.pl \
	parse_tcpdump_log.pl \
	parse-usbsnoop.php \
	usbmon2usbsnoop.pl \
	v4l_rec.pl \
	\
	az6007 \
	cx231xx \
	cx25821 \
	em28xx \
	m920x \
	pci_traffic \
	qv4l2-qt3 \
	saa7134 \
	sn9c201 \
	tm6000 \
	usb_parse
=======
if WITH_GCONV
SUBDIRS += gconv
endif

if WITH_GCONV
SUBDIRS += gconv
endif

SUBDIRS += decode_tm6000


EXTRA_DIST = \
	cobalt-ctl \
	parsers \
	pci_traffic \
	v4l_rec.pl
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
