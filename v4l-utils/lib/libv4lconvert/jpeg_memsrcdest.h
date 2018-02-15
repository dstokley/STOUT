#include <jpeglib.h>

<<<<<<< HEAD
#if JPEG_LIB_VERSION < 80 && !defined(MEM_SRCDST_SUPPORTED)

=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
void
jpeg_mem_src (j_decompress_ptr cinfo, unsigned char * buffer,
	unsigned long bufsize);

void
jpeg_mem_dest (j_compress_ptr cinfo, unsigned char ** outbuffer,
	unsigned long * outsize);
<<<<<<< HEAD

#endif
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
