#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "buf_encrypt.h"
#include "randcrypt.h"
#include "oracle.h"

int main(int argc, const char *argv[])
{
	int           status, c;
	FILE          *file;
	long          filesize;
	size_t        pad, inlen, outlen;
	unsigned char *in, *out, *tmp;

	if (argc != 2) {
		fputs("Usage: ./test-oracle <filename>\n", stderr);
		return 1;
	} else if (!(file = fopen(argv[1], "rb"))) {
		fprintf(stderr, "Could not open file '%s'.\n", argv[3]);
		return 2;
	}

	fseek(file, 0L, SEEK_END);
	filesize = ftell(file);
	rewind(file);

	pad    = (BLOCK(filesize) > 0) ? BLOCKSIZE - (BLOCK(filesize)) : 0;
	inlen  = filesize + pad;
	out    = NULL;

	if (!(in = malloc(sizeof(unsigned char) * inlen))) {
		fputs("Could not allocate memory for input buffer.\n", stderr);
		status = -1;
		goto exit;
	}
	memset(in + filesize, '\0', pad);

	/* Read the data from the file. */
	tmp = in;
	while ((c = fgetc(file)) != EOF)
		*tmp++ = c;

	srand(time(NULL));
	if ((status = rand_crypt(&in, &inlen, &out, &outlen)) != 0)
		fprintf(stderr, "ecb_crypt failed: returned %d.\n", status);
	else
		printf("The oracle declares the buffer to be encrypted with %s!\n",
				PREDICTION_STRING(aes_oracle(out, outlen)));

exit: /* Fallthrough on success. */
	free(in);
	free(out);
	fclose(file);
	return status;
}

