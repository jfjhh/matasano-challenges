#include <stdio.h>
#include <string.h>

static int ham_byte(unsigned char a, unsigned char b)
{
	int distance    = 1;
	unsigned char c = a ^ b;

	if (a == b)
		return 0;

	/* A number AND'ed with itself minus one deletes the rightmost 1-bit from
	   the number. When the number is zero, all 1-bits have been deleted. */
	while (c &= (c - 1))
		distance++;

	return distance;
}

int hamming_distance(unsigned char *restrict a, unsigned char *restrict b,
		int alen, int blen)
{
	int i, distance, x, y;
	unsigned char *restrict q, *restrict u;

	if (alen < blen) {
		x = alen;
		y = blen;
		q = a;
		u = b;
	} else {
		x = blen;
		y = alen;
		q = b;
		u = a;
	}

	// for (i = distance = 0; i <= x; i++)
	// 	distance += ham_byte(q[i], u[i]);
	// for (; i <= y; i++)
	// 	distance += ham_byte(0,    u[i]);
	for (i = distance = 0; i < x; i++)
		distance += ham_byte(q[i], u[i]);
	for (; i < y; i++)
		distance += ham_byte(0,    u[i]);

	return distance;
}

