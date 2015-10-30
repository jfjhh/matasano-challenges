#ifndef STRTOHEX_H
#define STRTOHEX_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Converts an ascii-encoded string of hex into the numeric equivalent.
 * 
 * E.g. "deadbeef" => <0xdeadbeef>.
 * 0000000: 6465 6164 6265 6566                      deadbeef
 * becomes:
 * 0000000: dead beef                                ....
 *
 * @param ascii  The ascii-encoded hex data.
 * @param outlen The length of the input ascii (2x as much as the hex bytes).
 *
 * @returns a malloc'd buffer to the hex bytes, or @c NULL on error.
 */
unsigned char *strtohex(const unsigned char *ascii, size_t inlen);

#endif /* STRTOHEX_H */

