#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "util/aes_funcs.h"

void ecb_byte_decrypt(const char *buf, size_t buflen)
{
	/* Find blocksize of cipher.
	 * Detect mode is ECB.
	 * OTHER (see `README.md`).
	 */
}

int main(int argc, const char *argv[])
{
	int status, c;
	bool ok;
	FILE *file;
	long filesize;
	char *in, *out, *tmp;
	size_t inlen, outlen;

	status = 0;
	file   = NULL;
	in     = out = NULL;

	if (argc != 2) {
		fputs("Usage: byte-ecb-decrypt <base64-encoded secret file>\n", stderr);
		status = -1;
		goto exit;
	} else if (!(file = fopen(argv[1], "rb"))) {
		fprintf(stderr, "Could not open file '%s'!\n", argv[1]);
		status = 1;
		goto exit;
	}

	fseek(file, 0L, SEEK_END);
	filesize = ftell(file);
	rewind(file);

	if (!(in = malloc(sizeof(unsigned char) * filesize))) {
		fputs("Could not allocate memory to get input from the secret file.\n",
				stderr);
		status = 2;
		goto exit;
	}

	tmp = in;
	while ((c = fgetc(file)) != EOF)
		if (isbase64(c) || c == '=')
			*tmp++ = c;

	/* `tmp` should be before `in + filesize` (because '\0', pad, EOF, etc.). */
	inlen = tmp - in;

	if (!(ok = base64_decode_alloc(in, inlen, &out, &outlen))) {
		fputs("Input was not valid base64-encoded text!\n", stderr);
		status = 3;
		goto exit;
	} else if (!out) {
		fputs("Could not allocate memory for base64-decoded output!\n", stderr);
		status = 4;
		goto exit;
	}

	/* Free all that we can before doing (possibly) mem-expensive decryption. */
	free(in);
	fclose(file);
	in   = NULL;
	file = NULL;

	ecb_byte_decrypt(out, outlen);

exit: /* Fallthrough on success. */
	if (file)
		fclose(file);
	free(in);
	free(out);

	return status;
}

