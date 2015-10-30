#ifndef PKCS7_H
#define PKCS7_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Implements PKCS-7 (RFC 2315) padding.
 *
 * @param buf       The input buffer to pad.
 * @param buf_len   The length of the buffer.
 * @param blocksize The size of the blocks.
 *
 * @returns A malloc'd pointer to the padded buffer or @c NULL on error.
 */
unsigned char *restrict pkcs7_pad(const unsigned char *restrict buf,
		size_t buf_len, size_t blocksize);

#endif /* PKCS7_H */

