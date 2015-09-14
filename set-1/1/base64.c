#include <stdio.h>

#define BASE64_TABLE \
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

#define BASE64_PAD '='

unsigned char ato64(unsigned char c)
{
	if (c < 64) // Validate that it is a 6-bit value.
		return BASE64_TABLE[c];
	else // Is the pad char.
		return BASE64_PAD;
}

void putchars64(const unsigned char *x, int bytes)
{
	unsigned char a, b, c, d;
	unsigned char y, z;

	if (!bytes)
		return;

	y = x[1];
	z = x[2];
	// if (bytes == 2) {
	// 	y = x[1];
	// 	z = x[2];
	// } else if (bytes == 1) {
	// 	y = x[1];
	// 	z = 0;
	// } else {
	// 	y = z = 0;
	// }

	a = x[0] >> 2;
	b = ((x[0] << 4) + (y >> 4)) & 0x3F;
	c = ((y << 2) + (z >> 6)) & 0x3F;
	d = z & 0x3F;

	if (bytes == 1)
		printf("%c%c==", ato64(a), ato64(b));
	else if (bytes == 2)
		printf("%c%c%c=", ato64(a), ato64(b), ato64(c));
	else
		printf("%c%c%c%c", ato64(a), ato64(b), ato64(c), ato64(d));
}

int main(void)
{
	int i, ok, c;
	unsigned char x[3];

	ok = 1;
	while (ok) {
		for (i = 0; i < 3; i++) {
			if ((c = getchar()) == EOF) {
				ok = 0;
				break;
			}
			x[i] = (unsigned char) c;
		}
		putchars64(x, i);
	}

	return 0;
}

