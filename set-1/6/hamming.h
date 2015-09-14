#ifndef HAMMING_H
#define HAMMING_H

#include <stdio.h>

int hamming_distance(unsigned char *restrict a, unsigned char *restrict b,
		int alen, int blen);

#endif /* HAMMING_H */

