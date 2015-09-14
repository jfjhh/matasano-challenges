#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../strtohex.h"

const char *ctext =
"1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

// The space character is the '27th' character in this alphabet.
const float alphafreq[27] = {
	8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
	0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
	2.758, 0.978, 2.361, 0.150, 1.974, 0.074, 15.000,
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
	int letters[27], i, bad;
	double score = 0;
	bad = 0;

	for (i = 0; i < length; i++)
		if (islower(x[i]))
			letters[tolower(x[i]) - 'a']++;
		else if (x[i] == ' ')
			letters[26]++;
		else if (!isalnum(x[i]))
			bad++;

	for (i = 0; i < 27; i++)
		score += letters[i] * alphafreq[i];

	// Probably not a valid message if it has unprintable chars.
	score -= bad * 50;

	return score;
}

int main(void)
{
	int i, best_byte, inlen;
	float score, old_score;
	unsigned char *in, *out;

	inlen = strlen(ctext) / 2;
	in = out = NULL;
	score = best_byte = 0;

	if (!(out = malloc(sizeof(char) * inlen)))
		goto exit;
	if (!(in = strtohex(ctext, strlen(ctext))))
		goto exit;

	fprintf(stderr,
			"Input ciphertext (XOR'd against a byte): \"%s\".\n", ctext);

	for (i = 0; i < 256; i++) {
		xorbuf(in, out, (unsigned char) i, inlen);

		old_score = score;
		score = charfreq_score(out, inlen);

		best_byte = (score > old_score) ? i : best_byte;
	}

	xorbuf(in, out, (unsigned char) best_byte, inlen);
	fprintf(stderr, "Best match: (byte %d)\n\t\"", best_byte);
	for (i = 0; i < inlen; i++)
		putchar(out[i]);
	fprintf(stderr, "\".\n");

exit: // Falls through normally.
	free(in);
	free(out);
	return 0;
}

