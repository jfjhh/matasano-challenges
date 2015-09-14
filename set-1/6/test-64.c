#include <stdio.h>

#include "base64.h"

int main(int argc, const char *argv[])
{
	int i, ok, c, inlen, status;
	unsigned char x[4];

	if (argc == 2 && argv[1][0] == 'd')
		inlen = 4; // decode.
	else
		inlen = 3; // encode.

	ok = 1;
	while (ok) {
		for (i = 0; i < inlen; i++) {
			if ((c = getchar()) == EOF) {
				ok = 0;
				break;
			}

			if (inlen == 4)
				if (c == '\n') // decoding swallows newlines.
					continue;

			x[i] = (unsigned char) c;
		}

		if (inlen == 3)
			status = encode64(x, i);
		else
			status = decode64(x, i);

		if (!status)
			break;
	}

	return 0;
}

