#include "oracle.h"

oracle_prediction aes_oracle(const unsigned char *buf, size_t buflen)
{
	const int blocks = buflen / BLOCKSIZE;
	int count, i, j, k;
	count = 0;

	/* Do all possible comparisons of blocks. The amount of comparisons is the
	 * (BLOCKS)-th Triangle Number. */
	for (i = count = 0; i < blocks; i++) {
		for (j = i + 1; j < blocks; j++) {
			count++;
			for (k = 0; k < BLOCKSIZE; k++) {
				if (*(buf + (i * BLOCKSIZE) + k)
						!= *(buf + (j * BLOCKSIZE) + k)) {
					count--;
					break;
				}
			}
		}
	}

	fprintf(stderr, "Oracle got %d duplicate blocks.\n", count);

	if (count > 2) /* Arbitrary similarities. */
		return ECB;
	else
		return CBC;
}

