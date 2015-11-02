#include "randcrypt.h"

static void rand_bytes(unsigned char *buf, size_t buflen)
{
	for (int i = 0; i < buflen; i++)
		buf[i] = (unsigned char) rand();
}

static int rand_range(int min, int max)
{
	double scaled = (double) rand() / RAND_MAX;
	return (((max - min) + 1) * scaled) + min;
}

int rand_crypt(unsigned char *const *restrict in, const size_t *inlen,
		unsigned char **restrict out, size_t *outlen)
{
	int           status;
	size_t        before, after, modlen, padlen;
	unsigned char key[BLOCKSIZE], IV[BLOCKSIZE], *modified_in;
	enum          encryption_mode { ECB = 0, CBC = 1, } mode;

	/* Set to failure values by default. */
	*out    = NULL;
	*outlen = 0;

	/* Get BLOCKSIZE-aligned buffer lengths */
	before  = rand_range(5, 10);
	after   = rand_range(5, 10);
	modlen  = before + *inlen + after;
	padlen  = BLOCKSIZE - BLOCK(modlen); /* modlen is aligned to BLOCKSIZE. */
	modlen += padlen;

	if (!(modified_in = malloc(sizeof(unsigned char) * modlen)))
		return 1;

	/* Make modified_in look like { prepended, in, appended, <0-pad> }. */
	rand_bytes(modified_in, before);          /* Prepend `before`.      */
	memcpy(modified_in + before, *in, *inlen); /* Add in the body, `in`. */
	rand_bytes(modified_in + (before + *inlen), after);    /* Append `after`. */
	memset(modified_in + (modlen - padlen), '\0', padlen); /* Zero the rest.  */

	if (!(*out = malloc(sizeof(unsigned char) * modlen))) {
		free(modified_in);
		return 2;
	}
	*outlen = modlen;

	rand_bytes(key, BLOCKSIZE); /* Encrypt with a random key. */
	mode = rand_range(0, 1);    /* Random mode: ECB or CBC. */

	printf("rand_crypt: (%d) Enrypting with AES mode %s.\n",
			mode, (mode == ECB ? "ECB" : "CBC"));

	if (mode == ECB) {
		status = ecb_crypt(modified_in, *out, modlen, key,     ENCRYPT);
	} else {
		rand_bytes(IV, BLOCKSIZE); /* Encrypt with a random IV. */
		status = cbc_crypt(modified_in, *out, modlen, key, IV, ENCRYPT);
	}

	free(modified_in);
	return status;
}

