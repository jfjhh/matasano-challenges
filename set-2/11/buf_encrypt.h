#ifndef BUF_ENCRYPT_H
#define BUF_ENCRYPT_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <openssl/aes.h>

#include "aes_info.h"

typedef enum {
	ENCRYPT = true,
	DECRYPT = false,
} crypt_mode;

int ecb_crypt(const unsigned char *restrict in,
		unsigned char *restrict out, size_t len,
		unsigned char *restrict passkey, crypt_mode mode);

int cbc_crypt(const unsigned char *restrict in,
		unsigned char *restrict out, size_t len,
		unsigned char *restrict passkey, unsigned char *restrict IV,
		crypt_mode mode);


#endif /* BUF_ENCRYPT_H */

