#include "base64.h"

static int atobase64(unsigned char c)
{
	if (c < 64) // Validate that it is a 6-bit value.
		return BASE64_TABLE[c];
	else
		return -1;
}

static int base64toa(unsigned char c)
{
	if (isupper(c))
		return c - 'A';
	else if (islower(c))
		return (c - 'a') + 26;
	else if (isdigit(c))
		return (c - '0') + (26 * 2);
	else if (c == '+')
		return 62;
	else if (c == '/')
		return 63;
	else if (c == '=')
		return 0;
	else
		return -1;
}

int encode64(const unsigned char *x, int bytes)
{
	unsigned char a, b, c, d;

	if (!bytes)
		return 0;

	a = x[0] >> 2;
	b = ((x[0] << 4) + (x[1] >> 4)) & 0x3F;
	c = ((x[1] << 2) + (x[2] >> 6)) & 0x3F;
	d = x[2] & 0x3F;

	if (bytes == 1)
		printf("%c%c==",
				atobase64(a), atobase64(b));
	else if (bytes == 2)
		printf("%c%c%c=",
				atobase64(a), atobase64(b), atobase64(c));
	else
		printf("%c%c%c%c",
				atobase64(a), atobase64(b), atobase64(c), atobase64(d));

	return 1;
}

int decode64(const unsigned char *x, int bytes)
{
	unsigned char a, b, c;
	int i, j, k, l;

	if (bytes % 4 != 0 || bytes == 0)
		return 0;

	i = base64toa(x[0]);
	j = base64toa(x[1]);
	k = base64toa(x[2]);
	l = base64toa(x[3]);

	if (i == -1 || j == -1 || k == -1 || l == -1)
		return 0;

	// a = (i << 2) + (j >> 4);
	// b = (j << 4) + (k >> 2);
	// c = (k << 6) + l;
	a = ((unsigned char) i << 2) + ((unsigned char) j >> 4);
	b = ((unsigned char) j << 4) + ((unsigned char) k >> 2);
	c = ((unsigned char) k << 6) + (unsigned char) l;

	if (x[2] == '=') // 2 pad chars.
		printf("%c", a);
	else if (x[3] == '=') // 1 pad char.
		printf("%c%c", a, b);
	else
		printf("%c%c%c", a, b, c);

	return 1;
}

