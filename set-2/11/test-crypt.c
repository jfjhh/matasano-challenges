#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "buf_encrypt.h"

int main(int argc, const char *argv[])
{
	int           status, c;
	FILE          *file;
	long          filesize;
	size_t        pad, length;
	unsigned char passkey[KEYSIZE], *in, *out, *tmp;
	crypt_mode    mode;

	in = out = NULL;

	if (argc != 4) {
		fputs("Usage: ./test <'e'|'d'> <key> <filename>\n", stderr);
		return 1;
	} else if (!(file = fopen(argv[3], "rb"))) {
		fprintf(stderr, "Could not open file '%s'.\n", argv[3]);
		return 2;
	}

	memset(passkey, '\0',    KEYSIZE);
	memcpy(passkey, argv[2], KEYSIZE);

	mode = (argv[1][0] == 'e') ? ENCRYPT : DECRYPT;

	fseek(file, 0L, SEEK_END);
	filesize = ftell(file);
	rewind(file);

	pad = (BLOCK(filesize) > 0) ? BLOCKSIZE - (BLOCK(filesize)) : 0;
	length = filesize + pad;

	if (!(in = malloc(sizeof(unsigned char) * length))) {
		fputs("Could not allocate memory for input buffer.\n", stderr);
		status = -1;
		goto exit;
	}
	memset(in + filesize, '\0', pad);

	/* Read the data from the file. */
	tmp = in;
	while ((c = fgetc(file)) != EOF)
		*tmp++ = c;
	
	if (!(out = malloc(sizeof(unsigned char) * length))) {
		fputs("Could not allocate memory for output buffer.\n", stderr);
		status = -2;
		goto exit;
	}

	// if ((status = ecb_crypt(in, out, length, passkey, mode)) != 0) {
	if ((status = cbc_crypt(in, out, length, passkey, NULL, mode)) != 0) {
		fprintf(stderr, "ecb_crypt failed: returned %d.\n", status);
	} else {
		for (int i = 0; i < length; i++)
			fputc(out[i], stdout);
	}

exit: /* Fallthrough on success. */
	free(in);
	free(out);
	fclose(file);
	return status;
}

