#ifndef KEYSIZE_H
#define KEYSIZE_H

#include <stdio.h>
#include <string.h>

#include "hamming.h"

// Parameters. Play with them for better results.

#ifndef MIN_KEY
#define MIN_KEY	2
#endif /* MIN_KEY */

#ifndef MAX_KEY
#define MAX_KEY	40
#endif /* MAX_KEY */

#ifndef KEYS
#define KEYS	(MAX_KEY - MIN_KEY)
#endif /* KEYS */

#ifndef BLOCKS
#define BLOCKS	8
#endif /* BLOCKS */

// The first block is not counted for calculating adjacent (consec.) hams.
#ifndef CONSEC_HAMS
#define CONSEC_HAMS	(BLOCKS - 1)
#endif /* CONSEC_HAMS */

// Average of all consecutive hams: the average hamming distance of blocks
// keysize big.
#ifndef AVG_CONSEC_HAMS
#define AVG_CONSEC_HAMS(A)	(A / CONSEC_HAMS)
#endif /* AVG_CONSEC_HAMS */

// Normalizes hamming differences. A is the sum of consecutive hams from all
// adjacent blocks, B is the keysize. Therefore the normalized hamming distance
// is the average of the consecutive hams divided by the keysize.
#ifndef NORM_HAMS
#define NORM_HAMS(A, B)	(AVG_CONSEC_HAMS(A) / B)
#endif /* NORM_HAMS */

#endif /* KEYSIZE_H */

