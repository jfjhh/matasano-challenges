#include "buf_encrypt.h"

static inline void xorbuf(unsigned const char *restrict in,
		unsigned char *restrict out, int length)
{
	for (int i = 0; i < length; i++)
		out[i] ^= in[i];
}

int ecb_crypt(const unsigned char *restrict in,
		unsigned char *restrict out, size_t len,
		unsigned char *restrict passkey, crypt_mode mode)
{
	unsigned char in_block[BLOCKSIZE], out_block[BLOCKSIZE];
	AES_KEY key;

	if (!in || !out || !passkey || len < BLOCKSIZE) /* Check parameters. */
		return 1;
	else if (mode != ENCRYPT && mode != DECRYPT)    /* Check mode. */
		return 2;

	if (mode == ENCRYPT)
		AES_set_encrypt_key(passkey, KEYSIZE, &key);
	else
		AES_set_decrypt_key(passkey, KEYSIZE, &key);

	for (int i = 0; i < len; i += BLOCKSIZE) {
		memcpy(in_block, in + i, BLOCKSIZE);

		if (mode == ENCRYPT)
			AES_encrypt(in_block, out_block, &key);
		else
			AES_decrypt(in_block, out_block, &key);

		memcpy(out + i, out_block, BLOCKSIZE);
	}

	return 0;
}

int cbc_crypt(const unsigned char *restrict in,
		unsigned char *restrict out, size_t len,
		unsigned char *restrict passkey, unsigned char *restrict IV,
		crypt_mode mode)
{
	unsigned char in_block[BLOCKSIZE], out_block[BLOCKSIZE],
				  prev_buf[BLOCKSIZE], IV_buf[BLOCKSIZE];
	AES_KEY key;

	if (!in || !out || !passkey || len < BLOCKSIZE) /* Check parameters. */
		return 1;
	else if (mode != ENCRYPT && mode != DECRYPT)    /* Check mode. */
		return 2;

	if (mode == ENCRYPT)
		AES_set_encrypt_key(passkey, KEYSIZE, &key);
	else
		AES_set_decrypt_key(passkey, KEYSIZE, &key);

	if (!IV) /* If IV is NULL, just use all zeros. */
		memset(IV_buf, '\0',   BLOCKSIZE);
	else
		memcpy(IV_buf, IV,     BLOCKSIZE);

	memcpy(prev_buf,   IV_buf, BLOCKSIZE); /* The initial XOR is with the IV. */

	for (int i = 0; i < len; i += BLOCKSIZE) {
		memcpy(in_block, in + i, BLOCKSIZE);

		if (mode == ENCRYPT) {
			xorbuf(prev_buf,      in_block,  BLOCKSIZE);
			AES_encrypt(in_block, out_block, &key);
			memcpy(prev_buf,      out_block, BLOCKSIZE); /* Prepare next XOR. */
		} else {
			AES_decrypt(in_block, out_block, &key);
			xorbuf(prev_buf,      out_block, BLOCKSIZE);
			memcpy(prev_buf,      in_block,  BLOCKSIZE); /* Prepare next XOR. */
		}

		memcpy(out + i, out_block, BLOCKSIZE);
	}

	return 0;
}

