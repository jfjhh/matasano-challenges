#include <stdio.h>

char tohex(char c)
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

	return 0;
}

void hexencode(const char *restrict ascii, char *restrict hex)
{
	int i;
	char c, d;

	for (i = 0; ascii[i] != '\0'; i += 2) {
		c = tohex(ascii[i]);
		d = tohex(ascii[i + 1]);

		hex[i/2] = (c << 4) | d; /* bits: CCCCDDDD */

		/* Check that d was not end of string */
		if (ascii[i + 1] == '\0')
			break;
	}
}

void xor(const char *restrict input, const char *restrict pad)
{
	while (putchar(*input++ ^ *pad++))
		;
}

int main(void)
{
	const char *input = "1c0111001f010100061a024b53535009181c";
	const char *pad   = "686974207468652062756c6c277320657965";

	char inhex[64], padhex[64];
	hexencode(input, inhex);
	hexencode(pad, padhex);

	xor(inhex, padhex);
}

