/**
 * block-transpose.c
 * Alex Striff
 *
 * Breaks multi-char key XOR crypto on a file, trying with a given keysize.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define EXIT(A)	status = A; goto exit;

static const size_t MAX_BLOCKSIZE = (1<<20);

// The space character is the '27th' character in this alphabet.
static const float alphafreq[27] = {
	8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
	0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
	2.758, 0.978, 2.361, 0.150, 1.974, 0.074, 15.000,
};

long charfreq_score(const unsigned char x)
{
	long score = 0L;

	if (isprint(x)) {
		score = 1L;
		if (isalpha(x))
			score = 4L * (long) alphafreq[tolower(x) - 'a'];
		else if (isdigit(x))
			score = 2L;
	}

	return score;
}

static void xorbuf(unsigned const char *restrict in,
		unsigned char *restrict out, unsigned char pad, int length)
{
	int i;

	for (i = 0; i < length; i++)
		*out++ = *in++ ^ pad;
}

int main(int argc, const char *argv[])
{
	FILE *file;
	int  keysize, status, block_size, block, total_size, i, c, byte_key;
	long filesize, old_score, score;
	char *blocks, *cur, *multibyte_key;

	file     = NULL;
	blocks   = cur = multibyte_key = NULL;
	filesize = 0L;
	status   = 0;

	if (argc != 3) { // Check args.
		fputs("Usage: `./block-transpose <keysize> <file>`.\n", stderr);
		EXIT(1)
	} else if ((keysize = atoi(argv[1])) < 1) {   // Get keysize and validate.
		fprintf(stderr, "Invalid keysize! (got: %d).\n", keysize);
		EXIT(2)
	} else if (!(file = fopen(argv[2], "rb"))) {  // Open XOR'd file to decrypt.
		fprintf(stderr, "Could not open file '%s'.\n", argv[1]);
		EXIT(3)
	} else if (fseek(file, 0L, SEEK_END) == -1) { // Go to the end of the file.
		perror("Could not seek to end of file");
		EXIT(4)
	} else if ((filesize = ftell(file)) == -1) {  // Get size of file.
		perror("Could not tell the offset into the file (from end)");
		EXIT(5)
	}
	rewind(file);

	block_size = ((filesize / keysize) > MAX_BLOCKSIZE)
		? MAX_BLOCKSIZE
		: (filesize / keysize);

	total_size = keysize * block_size;

	// Get memory for all the blocks.
	if (!(blocks = malloc(sizeof(char) * total_size))) {
		fputs("Cannot allocate memory for blocks.\n", stderr);
		EXIT(6)
	}
	memset(blocks, '\0', total_size);

	for (i = 0; i < total_size; i++) {
		if ((c = fgetc(file)) == EOF) {
			fputs("Could not read a character from the file.\n", stderr);
			EXIT(7)
		}
		block = (i < keysize) ? i : (i % keysize);
		cur   = blocks + ((block_size * block) + (i / keysize));
		*cur  = c;
	}

	// Get memory for the multibyte key.
	if (!(multibyte_key = malloc(sizeof(char) * (keysize + 1)))) {
		fputs("Cannot allocate memory for the multibyte key.\n", stderr);
		EXIT(7)
	}
	// memset(multibyte_key, '\0', keysize + 1); // Init all to zero.
	memset(multibyte_key, '*', keysize); // Init all values to '*'.
	multibyte_key[keysize] = '\0';

	fprintf(stderr, "Initialized multibyte_key: '%s'.\n", multibyte_key);

	// TODO: Solve individual blocks as one-byte XOR.
	for (block = 0; block < keysize; block++) {
		cur = blocks + (block * block_size);

		fprintf(stderr, "On block %d.\n", block);

		for (byte_key = 0, old_score = 0L; byte_key < (1<<8); byte_key++) {
			// fprintf(stderr,
			// 		"Trying byte_key %03d... ", (unsigned int) byte_key);

			for (i = 0, score = 0L; i < block_size; i++)
				score += charfreq_score(cur[i] ^ (unsigned char) byte_key);

			// fprintf(stderr, "Got score %.4f.\n", score);

			if (score > old_score) {
				old_score = score;
				multibyte_key[block] = byte_key;
				fprintf(stderr, "New best score (%d)! (byte_key: '%c')\n",
						old_score, byte_key);
			}
		}

		fprintf(stderr, "Best score: %d, for byte_key '%c'<0x%x>.\n",
				old_score, multibyte_key[block], multibyte_key[block]);
	}

	fprintf(stderr, "File: '%s'.\nKeysize: %d.\n\tFound multibyte key: '%s'.\n",
			argv[2], keysize, multibyte_key);

	puts(multibyte_key);

exit: // Fallthrough on success.
	if (file)
		fclose(file);
	free(blocks);
	free(multibyte_key);
	return 0;
}

