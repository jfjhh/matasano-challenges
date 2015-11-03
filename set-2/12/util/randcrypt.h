#ifndef RANDCRYPT_H
#define RANDCRYPT_H

#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

#include "buf_encrypt.h"

/**
 * Sets a buffer to have a random sequence of bytes.
 *
 * Assumes memory upto @p buflen is allocated.
 *
 * @param buf    The buffer to randomize.
 * @param buflen How many bytes of @p buf to randomize.
 */
void rand_bytes(unsigned char *buf, size_t buflen);

/**
 * Gets a random integer within a range.
 *
 * Assumes a previous call to @c srand().
 *
 * @param min The minimum value.
 * @param max The maximum value.
 *
 * @returns An @c int between @p min and @p max (inclusive).
 */
int rand_range(int min, int max);

/**
 * Randomly AES encrypts @p buf. Both prepends and appends [5, 10] bytes (chosen
 * randomly), and encrypts 50%/50% either in ECB or CBC mode (with random IVs).
 *
 * @p out will be malloc'd to the proper size, and @p outlen will be updated to
 * be this size. On error, @p out will be @c NULL and @p outlen @c 0.
 *
 * @param in     The buffer to encrypt.
 * @param inlen  The length of @p buf.
 * @param out    The encrypted buffer.
 * @param outlen The length (random) of the output buffer.
 *
 * @returns @c 0 on success and nonzero on error.
 */
int rand_crypt(unsigned char *const *restrict in, const size_t *inlen,
		unsigned char **restrict out, size_t *outlen);

#endif /* RANDCRYPT_H */

