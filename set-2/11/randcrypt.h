#ifndef RANDCRYPT_H
#define RANDCRYPT_H

#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

#include "buf_encrypt.h"

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

