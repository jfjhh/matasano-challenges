#include "oracle.h"

static int duplicate_blocks(const unsigned char *buf, size_t buflen)
{
	int count, i, j, k;
	const int blocks = buflen / ORACLE_BLOCKSIZE;
	count            = 0;

	if (buflen < ORACLE_BLOCKSIZE)
		return 0;

	/* Do all possible comparisons of blocks. The amount of comparisons is the
	 * (BLOCKS)-th Triangle Number. */
	for (i = 0; i < blocks; i++) {
		for (j = i + 1; j < blocks; j++) {
			count++;
			for (k = 0; k < ORACLE_BLOCKSIZE; k++) {
				if (*(buf + (i * ORACLE_BLOCKSIZE) + k)
						!= *(buf + (j * ORACLE_BLOCKSIZE) + k)) {
					count--;
					break;
				}
			}
		}
	}

	return count;
}

static inline oracle_prediction weak_oracle(int ecb_count)
{
	if (ecb_count > 1) /* Assumes one duplicate block is indicative of ECB. */
		return ECB;
	else
		return CBC;
}

oracle_prediction aes_oracle(const unsigned char *buf, size_t buflen)
{
	unsigned char *out, zero_block[BLOCKSIZE];
	int ecb_count, cbc_count;

	/* Because ECB is stateless and deterministic, encrypting the same block
	 * with the same key produces the same ciphertext block. By assuming
	 * duplicate blocks in the plaintext, there will be that same number of
	 * dupliate blocks in the ciphertext, when encrypted in ECB mode. */
	ecb_count = duplicate_blocks(buf, buflen);
	fprintf(stderr, "Oracle got %d duplicate blocks (Assuming ECB).\n",
			ecb_count);

	if (!(out = malloc(sizeof(unsigned char) * buflen))) {
		fputs("Could not allocate memory for decryption buffer.\n", stderr);
		return weak_oracle(ecb_count);
	}
	memset(zero_block, '\0', BLOCKSIZE); /* A zero'd buffer. */

	/* With an improper IV, CBC will have only the first block be invalid.
	 * Otherwise, even with the wrong key, the decrypted buffer should have the
	 * same dupliation charactersistics as plain encrypted ECB mode does. */
	cbc_crypt(buf, out, buflen, zero_block, zero_block, DECRYPT);

	if (!out) {
		fputs("Could not do oracle decryption on buffer.\n", stderr);
		free(out);
		return ECB;
	}

	cbc_count = duplicate_blocks(out, buflen);
	fprintf(stderr, "Oracle got %d duplicate blocks (Assuming CBC).\n",
			cbc_count);

	free(out);

	if (ecb_count > cbc_count)
		return ECB;
	else
		return CBC;
}

