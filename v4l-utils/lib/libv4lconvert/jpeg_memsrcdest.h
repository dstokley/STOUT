#include <jpeglib.h>

<<<<<<< HEAD
=======
#if JPEG_LIB_VERSION < 80 && !defined(MEM_SRCDST_SUPPORTED)

>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
void
jpeg_mem_src (j_decompress_ptr cinfo, unsigned char * buffer,
	unsigned long bufsize);

void
jpeg_mem_dest (j_compress_ptr cinfo, unsigned char ** outbuffer,
	unsigned long * outsize);
<<<<<<< HEAD
=======

#endif
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
