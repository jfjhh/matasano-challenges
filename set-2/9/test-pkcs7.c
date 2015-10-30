#include <stdio.h>

#include "pkcs7.h"

const unsigned char BUFFER[]  = { /* "YELLOW SUBMARINE". */
	0x59, 0x45, 0x4c, 0x4c,
	0x4f, 0x57, 0x20, 0x53,
	0x55, 0x42, 0x4d, 0x41,
	0x52, 0x49, 0x4e, 0x45,
};
const        size_t BUF_LEN    = 16;
const        size_t BS_LARGER  = 20;
const        size_t BS_SMALLER = 3;

int main(void) {
	int i;
	unsigned char *padded;

	fputs("\tBuffer:\n\t", stdout);
	for (i = 0; i < BUF_LEN; i++)
		printf("%#02x ", BUFFER[i]);
	puts("\n");

	if (!(padded = pkcs7_pad(BUFFER, BUF_LEN, BS_LARGER)))
		return 1;

	printf("Buffer Length: %d, Blocksize: %d, PKCS-7 Padded:\n",
			(int) BUF_LEN, (int) BS_LARGER);
	for (i = 0; i < BS_LARGER; i++)
		printf("%#02x ", padded[i]);
	puts("\n");

	free(padded);

	printf("Buffer Length: %d, Blocksize: %d, PKCS-7 Padded:\n",
			(int) BUF_LEN, (int) BS_SMALLER);
	if (!(padded = pkcs7_pad(BUFFER, BUF_LEN, BS_SMALLER)))
		return 1;

	for (i = 0; i < BUF_LEN + (BUF_LEN % BS_SMALLER); i++)
		printf("%#02x ", padded[i]);
	putchar('\n');

	free(padded);
	return 0;
}

