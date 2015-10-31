#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

/* Index within a block. */
#define BLOCK(A)	((A >= BLOCKSIZE) ? (A % BLOCKSIZE) : A)

static const size_t BLOCKSIZE = 16;

static const unsigned char PASSKEY[] = { /* "YELLOW SUBMARINE". */
	0x59, 0x45, 0x4c, 0x4c, 0x4f, 0x57, 0x20, 0x53,
	0x55, 0x42, 0x4d, 0x41, 0x52, 0x49, 0x4e, 0x45,
};

static const unsigned char IV[] = { /* Initialization Vector (all 0x0). */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static inline void xorbuf(unsigned const char *restrict in,
		unsigned char *restrict out, int length)
{
	int i;
	for (i = 0; i < length; i++)
		out[i] = out[i] ^ in[i];
}

int main(int argc, const char *argv[])
{
	int i, j, c, encrypt;
	unsigned char c_buf[BLOCKSIZE], p_buf[BLOCKSIZE], prev_buf[BLOCKSIZE];
	FILE *file = NULL;
	AES_KEY key;

	if (argc != 3 || !(file = fopen(argv[1], "rb"))) {
		fputs("Usage: ./ecb <filename> <encrypt?>\n", stderr);
		return 1;
	}
	encrypt = (argv[2][0] == 'e') ? 1 : 0;

	/* IDK what I'm doing, zero all the things. */
	memset(c_buf,    '\0', BLOCKSIZE);
	memset(p_buf,    '\0', BLOCKSIZE);
	memset(prev_buf, '\0', BLOCKSIZE);
	i = j = c = 0;

	if (encrypt)
		AES_set_encrypt_key(PASSKEY, 128, &key);
	else
		AES_set_decrypt_key(PASSKEY, 128, &key);

	i = 0;
	while ((c = fgetc(file)) != EOF) { // Get the data.
		if (c == '\n') /* Ignore line breaks in data. */
			continue;

		c_buf[BLOCK(i)] = c;
		fputc(c_buf[BLOCK(i)], stderr);

		// if (i == (BLOCKSIZE - 1) || i % (BLOCKSIZE - 1) == 0) {
		// 	if (i == BLOCKSIZE - 1)
		// 		memcpy(prev_buf, IV,    BLOCKSIZE);
		// 	else
		// 		memcpy(prev_buf, c_buf, BLOCKSIZE);

		// 	if (encrypt) {
		// 		xorbuf(prev_buf,    p_buf,  BLOCKSIZE);
		// 		AES_encrypt(p_buf,  c_buf,  &key);
		// 	} else {
		// 		AES_decrypt(c_buf,  p_buf,  &key);
		// 		xorbuf(prev_buf,    p_buf,  BLOCKSIZE);
		// 	}

		// 	for (j = 0; j < BLOCKSIZE; j++)
		// 		fputc(p_buf[j], stdout);
		// }
		i++;
	}

	fclose(file);
	return 0;
}

