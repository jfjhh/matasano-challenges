#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define IN_LINES	204
#define LINE_LEN	320
#define BLOCK_SIZE	8

#define HEX_LEN		(LINE_LEN / 2)
#define BLOCKS		(LINE_LEN / BLOCK_SIZE)

const unsigned char pass[] = {
	0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,
	0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf,
};

static int tohex(unsigned char c)
{
	if (c == '\0')
		return 0; else if (c >= '0' && c <= '9')
			return c - '0';
	else if (c >= 'a' && c <= 'f')
		return (c - 'a') + 0xA;
	else if (c >= 'A' && c <= 'F')
		return (c - 'A') + 0xA;
	else
		return EOF;
}

static int count_equal(unsigned char *buf)
{
	int count, i, j, k;
	count = 0;

	/* Do all possible comparisons of blocks. The amount of comparisons is the
	 * (BLOCKS)-th Triangle Number. */
	for (i = count = 0; i < BLOCKS; i++) {
		for (j = i + 1; j < BLOCKS; j++) {
			count++;
			for (k = 0; k < BLOCK_SIZE; k++) {
				if (*(buf + (i * BLOCK_SIZE) + k)
						!= *(buf + (j * BLOCK_SIZE) + k)) {
					count--;
					break;
				}
			}
		}
	}

	return count;
}

int main(int argc, const char *argv[])
{
	int i, j, x, y, candidate, candidate_equal, new_equal;
	unsigned char buf[IN_LINES][HEX_LEN];
	FILE *file = NULL;

	if (argc != 2 || !(file = fopen(argv[1], "rb"))) { // Check args.
		fputs("Usage: `./ecb-detect <filename>`,\n"
				"File contains ascii-encoded hex, one encrypted with AES in "
				"ECB mode, separated by newlines (see './README.md').\n",
				stderr);
		return 1;
	}

	candidate = candidate_equal = new_equal = 0;
	memset(buf, '\0', IN_LINES * HEX_LEN);

	// Convert ASCII-encoded hex lines to (raw hex) byte arrays.
	for (i = 0; i < IN_LINES; i++) {
		for (j = 0; j < HEX_LEN; j++) {
			x = fgetc(file);
			y = fgetc(file);
			if (x == EOF || y == EOF) {
				fputs("Hit EOF!\n", stderr);
				fclose(file);
				return 2;
			}

			x = tohex(x);
			y = tohex(y);
			if (x == EOF || y == EOF) {
				fputs("Found non-hex char!\n", stderr);
				fclose(file);
				return 3;
			}

			buf[i][j] = (x << 4) | y;
		}
		fgetc(file); // Swallow newline.
	}

	/* Compare all the internal blocks with eachother. The more that are
	 * equal, the more likely that the buffer was encrypted in ECB, because ECB
	 * is stateless and deterministic. */
	for (i = 0; i < IN_LINES; i++) {
		new_equal = count_equal(buf[i]);
		fprintf(stderr, "line %03d: count_equal == %d.\n", i + 1, new_equal);
		if (new_equal > candidate_equal) {
			candidate_equal = new_equal;
			candidate       = i;
		}
	}

	// Print the result.
	printf("Best found candidate for being encrypted with ECS (line %d):\n",
			candidate + 1);
	for (j = 0; j < HEX_LEN; j++)
		printf("%02x", buf[candidate][j]);
	putchar('\n');

	fclose(file);
	return 0;
}

