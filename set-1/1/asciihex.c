/*
 * Converts ASCII encoded hex, like "24F" to actual hex, like 0x24F
 * Input string is given as the first (and only) argument.
 *
 * Alex Striff
 */

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

int main(int argc, const char *argv[])
{
	int i, c, d;

	if (argc != 2) {
		fprintf(stderr, "Requires one argument.\n");
		return 1;
	}

	for (i = 0; argv[1][i] != '\0'; i += 2) {
		c = tohex(argv[1][i]);
		d = tohex(argv[1][i + 1]);

		putchar((c << 4) | d); /* bits: CCCCDDDD */

		/* Check that d was not end of string */
		if (argv[1][i + 1] == '\0')
			break;
	}

	return 0;
}

