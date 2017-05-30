#ifndef _LZMA2_WRAPPER_H
#define _LZMA2_WRAPPER_H

#include <string>
#include "C/7zTypes.h"

#define buffer_cread_size 65536 // 1 < 16

/* ISeqInstream struct implementation */
struct seq_in_stream{
    ISeqInStream in_stream; // need this for implementation
    FILE * fd; // file to read from
};

/* ISeqInstream struct implementation */
struct seq_out_stream{
    ISeqOutStream out_stream; // need this for implementation
    FILE *fd; // file to write to
};

/* implementation of ISeqinstream, see ISeqInStream struct
 * for why we have these fields
 */
int in_stream_read(void *p, void *buf, size_t *size);

/* open a file and read raw data from it, then pass this data to
 * compress_data.
 * INPUT:
 * char *in_path - path to the file we want to open
 * char *out_path - path to file we will write compressed data to
 * OUTPUT:
 * 1 - success
 * 0 - failure
 */
int compress_file(char *in_path, char *out_path);

/* compress raw data, currently gonna use lzma ill update later to
 * use lzma2.
 * INPUT:
 * unsigned char *input - raw data that we will compress
 * unsigned char *output - destination of compressed data
 * OUTPUT:
 * 1 - success
 * 0 - failure
 * unsigned char *output will hold the compressed data
 */
int compress_data(unsigned char *input, size_t input_len,
                  unsigned char *output, size_t *output_len);

/* decompress raw data
 * INPUT:
 * unsigned char *input - raw data to decompress
 * size_t input_len - length of input
 * unsigned char *output - destination of decompressed data
 * size_t *output_len - size of buffer
 * RETURN:
 * 1 - success
 * 0 - failure
 * output_len will hold size of decompressed data
 */
int decompress_data(unsigned char *input, size_t input_len,
                    unsigned char *output, size_t *output_len);

/* compress data incrementally, it works using fn
 * callbacks that are implemented as static functions.
 * these functions just provide implementation for
 * Iseqinstream->read and Iseqoutstream->write
 * INPUT:
 * FILE *input - file stream to input file
 * FILE *output - file stream to ouput file
 * char *args - arguments to pass to the encode fn,
 * look at LzmaEnc.h for more info (props struct)
 * OUTPUT:
 * not implemented yet
 */
int compress_data_incr(FILE *input, FILE *output, char *args);

int decompress_data_incr(FILE *input, FILE *output);
#endif // _LZMA2_WRAPPER_H
