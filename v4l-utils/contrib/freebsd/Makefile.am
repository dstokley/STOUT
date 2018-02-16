EXTRA_DIST = \
<<<<<<< HEAD
<<<<<<< HEAD
=======
	bsdify.sh \
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
	bsdify.sh \
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	include \
	patches

sync-with-kernel:
	rm -rf .pc

<<<<<<< HEAD
<<<<<<< HEAD
	for i in input.h input-event-codes.h ivtv.h uinput.h videodev2.h v4l2-controls.h v4l2-common.h; do \
=======
	for i in input.h ivtv.h uinput.h videodev2.h v4l2-controls.h v4l2-common.h dvb/{audio.h,ca.h,dmx.h,frontend.h,net.h,osd.h,version.h,video.h}; do \
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	    mkdir -p include/linux/$$(dirname $$i); \
	    cp $(KERNEL_DIR)/include/uapi/linux/$$i include/linux/$$i; \
	done

	for i in ivtv.h uinput.h videodev2.h dvb/{audio.h,ca.h,dmx.h,frontend.h,net.h,osd.h,version.h,video.h}; do \
=======
	for i in input.h input-event-codes.h ivtv.h uinput.h videodev2.h v4l2-controls.h v4l2-common.h; do \
	    mkdir -p include/linux/$$(dirname $$i); \
	    cp $(KERNEL_DIR)/usr/include/linux/$$i include/linux/$$i; \
	done

<<<<<<< HEAD
	for i in ivtv.h uinput.h videodev2.h dvb/{audio.h,ca.h,dmx.h,frontend.h,net.h,osd.h,version.h,video.h}; do \
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
	for i in ivtv.h uinput.h videodev2.h v4l2-common.h; do \
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	    sed -e 's/__u8/uint8_t/g' -e 's/__u16/uint16_t/g' -e 's/__u32/uint32_t/g' -e 's/__u64/uint64_t/g' -e 's/__s8/int8_t/g' -e 's/__s16/int16_t/g' -e 's/__s32/int32_t/g' -e 's/__s64/int64_t/g' -e 's/__le32/uint32_t/g' -e 's/__user//g' -i include/linux/$$i; \
	done

	quilt push -a
