#ifndef STRTOHEX_H
#define STRTOHEX_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Converts an ascii-encoded string of hex into the numeric equivalent.
// E.g. "deadbeef" => 0xdeadbeef .
// The returned buffer is malloc'd and must be freed by the caller.
// Returns NULL on error.
unsigned char *strtohex(const unsigned char *ascii, int outlen);

#endif /* STRTOHEX_H */

