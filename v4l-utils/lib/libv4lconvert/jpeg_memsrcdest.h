#include <jpeglib.h>

<<<<<<< HEAD
<<<<<<< HEAD
#if JPEG_LIB_VERSION < 80 && !defined(MEM_SRCDST_SUPPORTED)

=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
#if JPEG_LIB_VERSION < 80 && !defined(MEM_SRCDST_SUPPORTED)

>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
void
jpeg_mem_src (j_decompress_ptr cinfo, unsigned char * buffer,
	unsigned long bufsize);

void
jpeg_mem_dest (j_compress_ptr cinfo, unsigned char ** outbuffer,
	unsigned long * outsize);
<<<<<<< HEAD
<<<<<<< HEAD

#endif
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======

#endif
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
