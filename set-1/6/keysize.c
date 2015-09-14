#include "keysize.h"

int main(int argc, const char *argv[])
{
	int key, block, c, i, sum_ham, norm_ham, prev_ham, min_ham_key, end;
	unsigned char blocks[BLOCKS][MAX_KEY];
	int distances[KEYS];
	FILE *file;

	// Check args.
	if (argc != 2) {
		fprintf(stderr, "Need the file to determine the keysize of!\n");
		return 1;
	}

	// Open the file to check.
	if (!(file = fopen(argv[1], "rb"))) {
		fprintf(stderr, "Could not open the file!\n");
		return 2;
	}

	// Print params.
	// fprintf(stderr, "MIN_KEY: %d, MAX_KEY: %d, KEYS: %d, BLOCKS: %d\n",
	// 		MIN_KEY, MAX_KEY, KEYS, BLOCKS);

	// Zero buffers.
	memset(distances,  0,  KEYS          * sizeof(int));
	memset(blocks,     0,  KEYS * BLOCKS * sizeof(char));

	// All the keys.
	for (key = min_ham_key = MIN_KEY, norm_ham = 0; key <= MAX_KEY; key++) {
		rewind(file);

		// All the blocks.
		for (block = sum_ham = end = 0; block < BLOCKS && !end; block++) {

			// Read keysize bytes into block.
			for (i = 0; i < key; i++) {
				if ((c = fgetc(file)) == EOF) { // At EOF, zero rest of block.
					memset(blocks[block] + i, 0, sizeof(char) * (key - i));
					end = 1;
					break;
				}
				blocks[block][i] = (unsigned char) c;
			}

			// Consecutive hamming distances of blocks.
			if (block > 0)
				sum_ham += hamming_distance(blocks[block - 1],
						blocks[block], key, key);
		}

		// Keep track of minimum hamming distance.
		prev_ham    = norm_ham;
		norm_ham    = NORM_HAMS(sum_ham, key);
		min_ham_key = (norm_ham < prev_ham) ? key : min_ham_key;
	}

	printf("The best found keysize was %d.\n", min_ham_key);

	fclose(file);

	return 0;
}

