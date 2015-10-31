#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <openssl/aes.h>

/* Index within a block. */
#define BLOCK(A)	((A >= BLOCKSIZE) ? (A % BLOCKSIZE) : A)

static const size_t BLOCKSIZE = 16;

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
	AES_KEY key;
	FILE *file;
	int i, j, c, encrypt;
	unsigned char in_buf[BLOCKSIZE],   out_buf[BLOCKSIZE],
				  prev_buf[BLOCKSIZE], passkey[BLOCKSIZE];

	if (argc != 4) {
		fputs("Usage: ./cbc-mode <'e'|'d'> <key> <filename|'-'>\n", stderr);
		return 1;
	} else if (argv[3][0] == '-') {
		file = stdin;
	} else if (!(file = fopen(argv[3], "rb"))) {
		fprintf(stderr, "Could not open file '%s'.\n", argv[3]);
		return 2;
	}

	memset(passkey, '\0',    BLOCKSIZE);
	memcpy(passkey, argv[2], BLOCKSIZE);

	encrypt = (argv[1][0] == 'e') ? 1 : 0;

	if (encrypt)
		AES_set_encrypt_key(passkey, 128, &key);
	else
		AES_set_decrypt_key(passkey, 128, &key);

	for (i = 0; (c = fgetc(file)) != EOF; i++) { /* Get the data. */
		in_buf[BLOCK(i)] = c;
		fprintf(stderr, "%02d:\t0x%02x  %c\n",
				i, c, (isprint(c) ? c : '\0'));

		if (i % BLOCKSIZE == (BLOCKSIZE - 1) && i > 0) {
			fprintf(stderr, "%scrypting, on byte %d.\n",
					(encrypt ? "En" : "De"), i);

			if (i == BLOCKSIZE - 1) /* Setup XOR block to chain with. */
				memcpy(prev_buf, IV,      BLOCKSIZE);
			/* else if (encrypt) */
			/* 	memcpy(prev_buf, out_buf, BLOCKSIZE); */

			fputs("\tPrevious buffer:\n\t", stderr);
			for (j = 0; j < BLOCKSIZE; j++)
				fprintf(stderr, "0x%02x ", prev_buf[j]);
			fputs("\n\n", stderr);

			if (encrypt) { /* Encrypt or Decrypt the block. */
				xorbuf(prev_buf,    in_buf,  BLOCKSIZE);
				AES_encrypt(in_buf, out_buf, &key);

				/* Prepare for next block. */
				memcpy(prev_buf, out_buf, BLOCKSIZE);
			} else {
				AES_decrypt(in_buf, out_buf,  &key);
				xorbuf(prev_buf,    out_buf,  BLOCKSIZE);

				/* Prepare for next block. */
				memcpy(prev_buf, in_buf,  BLOCKSIZE);
			}

			for (j = 0; j < BLOCKSIZE; j++) /* Output block to stdout. */
				fputc(out_buf[j], stdout);
		}
	}

	fclose(file);
	return 0;
}

