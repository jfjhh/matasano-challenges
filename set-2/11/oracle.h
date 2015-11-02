#ifndef ORACLE_H
#define ORACLE_H

#include <stdlib.h>
#include <stdio.h>

#include "aes_info.h"
#include "buf_encrypt.h"

#define ORACLE_BLOCKSIZE	BLOCKSIZE

typedef enum {
	ECB,
	CBC,
} oracle_prediction;

/**
 * Turns the oracle's pure *e*numeric revelation into a lowly human-readable
 * form.
 *
 * @param A An @c oracle_prediction.
 *
 * @note Depreciated for transcribing prophecies.
 */
#define PREDICTION_STRING(A) ((A == ECB) ? "ECB" : "CBC")

/**
 * Determines if @p buf was encrypted in CBC or ECB mode AES.
 *
 * @param buf    The buffer to check.
 * @param buflen The length of @p buf.
 *
 * @returns an oracle_prediction of the AES mode.
 */
oracle_prediction aes_oracle(const unsigned char *buf, size_t buflen);

#endif /* ORACLE_H */

