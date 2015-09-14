#ifndef BASE64_H
#define BASE64_H

#include <stdio.h>
#include <ctype.h>

#define BASE64_TABLE \
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

#define BASE64_PAD	'='

// Return either 1 on success, or 0 on failure.
// Both print their results to stdout.
int encode64(const unsigned char *x, int bytes);
int decode64(const unsigned char *x, int bytes);

#endif /* BASE64_H */

