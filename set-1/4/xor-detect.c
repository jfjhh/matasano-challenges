#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "../strtohex.h"

#define LINELEN	60
#define INLEN	(LINELEN / 2)

// The space character is the '27th' character in this alphabet.
const float alphafreq[27] = {
	8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
	0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
	2.758, 0.978, 2.361, 0.150, 1.974, 0.074, 13.000,
};

void xorbuf(unsigned const char *restrict in,
		unsigned char *restrict out, unsigned char pad, int length)
{
	int i;

	for (i = 0; i < length; i++)
		*out++ = *in++ ^ pad;
}

float charfreq_score(const unsigned char *x, int length)
{
	int letters[27], i, words;
	float score;

	score = 0;
	memset(letters, 0, 27 * sizeof(int));

	for (i = words = 0; i < length; i++)
		if (isalpha(x[i]) && islower(x[i]))
			letters[tolower(x[i]) - 'a']++;
		else if (x[i] == ' ')
			// else if (isspace(x[i]))
			letters[26]++, words++;
		else if (!isalnum(x[i]) && !isspace(x[i])
				&& x[i] != ',' && x[i] != '.' && x[i] != '!' && x[i] != '?'
				&& x[i] != '-' && x[i] != '/' && x[i] != '\\' && x[i] != ';'
				&& x[i] != ':' && x[i] != '\'' && x[i] != '\"')
			return 0; // No infrequent characters allowed, so kill the score.

	for (i = 0; i < 27; i++)
		score += letters[i] * alphafreq[i];

	// expect around 6 words, so be good to those ones.
	if (words >= 4 && words <= 8)
		score += (-abs(words - 6) + 3) * 30;

	return score;
}

int main(int argc, const char *argv[])
{
	FILE *file;
	int i, c, best_byte, best_line, count, magic_byte;
	float score, old_score, max_score;
	unsigned char *in, *out, line[LINELEN];

	file = NULL;
	in = out = NULL;

	// Check args.
	if (argc != 2) {
		fprintf(stderr, "NEEDS THE FILE ARGUMENT.\n");
		goto exit;
	}

	// Open files.
	if (!(file = fopen(argv[1], "r"))) {
		fprintf(stderr, "COULD NOT OPEN FILE '%s'.\n", argv[1]);
		goto exit;
	}

	for (count = magic_byte = best_line = 0; count < 1000; count++) {
		max_score = score = best_byte = 0;
		in = out = NULL;

		// Read the input line.
		for (i = 0; i < LINELEN; i++)
			if ((c = fgetc(file)) == EOF)
				goto done;
			else
				line[i] = c;
		fgetc(file); // Swallow newline.

		// Allocate buffers.
		if (!(out = malloc(sizeof(char) * INLEN))) {
			fprintf(stderr, "MEMORY ERROR.\n");
			goto exit;
		}
		if (!(in = strtohex(line, LINELEN))) {
			fprintf(stderr, "HEX DECODING ERROR.\n");
			goto exit;
		}

		// fprintf(stderr, "Input line %03d:\t", count);
		// for (i = 0; i < LINELEN; i++)
		// 	fputc(line[i], stderr);
		// fputc('\n', stderr);

		for (i = 0; i < 256; i++) {
			xorbuf(in, out, (unsigned char) i, INLEN);

			old_score = score;
			score = charfreq_score(out, INLEN);

			best_byte = (score > old_score) ? i     : best_byte;

			if (score > max_score) {
				max_score = score;
				best_line = count;
				magic_byte = best_byte;
			}
		}

		// Write the best result to stdout.
		// xorbuf(in, out, (unsigned char) best_byte, INLEN);
		// for (i = 0; i < INLEN; i++)
		// 	putchar(out[i]);

		// Write a result heading to stderr.
		// fprintf(stderr, "Best match:\t[0x%x] (dec. %d) (score: %f).\n",
		// 		(unsigned char) best_byte, best_byte, max_score);

		// Write the best result to stderr, too.
		// xorbuf(in, out, (unsigned char) best_byte, INLEN);
		// for (i = 0; i < INLEN; i++)
		// 	fputc(out[i], stderr);

		free(in);
		free(out);
	}

done: // On read EOF.

	// Go to the line in the file and re-read and xor it.
	// fseek(file, (best_line - 1) * (LINELEN + 1), SEEK_SET);
	fseek(file, best_line * (LINELEN + 1), SEEK_SET);
	for (i = 0; i < LINELEN; i++)
		if ((c = fgetc(file)) == EOF)
			goto exit;
		else
			line[i] = c;

	if (!(out = malloc(sizeof(char) * INLEN))) {
		fprintf(stderr, "MEMORY ERROR.\n");
		goto exit;
	}
	if (!(in = strtohex(line, LINELEN))) {
		fprintf(stderr, "HEX DECODING ERROR.\n");
		goto exit;
	}

	xorbuf(in, out, (unsigned char) magic_byte, INLEN);

	// The magic result.
	printf("The XOR'd line is line %d, the byte is 0x%x.\n"
			"Original string: \"",
			best_line, magic_byte);
	for (i = 0; i < LINELEN; i++)
		putchar(line[i]);
	printf("\".\nDecoded string: \"");
	for (i = 0; i < INLEN; i++)
		putchar(out[i]);
	printf("\".\n");

exit: // Falls through normally.
	free(in);
	free(out);
	if (file)
		fclose(file);

	return 0;
}

