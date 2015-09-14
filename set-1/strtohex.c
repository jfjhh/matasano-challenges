#include "strtohex.h"

static int tohex(unsigned char c)
{
	if (c == '\0')
		return 0;
	else if (c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'a' && c <= 'f')
		return (c - 'a') + 0xA;
	else if (c >= 'A' && c <= 'F')
		return (c - 'A') + 0xA;
	else
		fprintf(stderr, "Recieved non-hex char: '%c' (hex: '%x')\n", c, c);

	return EOF;
}

unsigned char *strtohex(const unsigned char *ascii, int inlen)
{
	int i, c, d;
	unsigned char *out;

	if (!(out = malloc(sizeof(char) * (inlen / 2))))
		return NULL;

	for (i = 0; i < inlen; i += 2) {
		c = tohex(ascii[i]);
		d = tohex(ascii[i + 1]);

		if ((c == EOF) || (d == EOF)) {
			free(out);
			return NULL;
		}

		/* bits: CCCCDDDD */
		out[i/2] = ((unsigned char) c << 4) | (unsigned char) d;
	}

	return out;
}

