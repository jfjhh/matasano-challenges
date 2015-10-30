#include "pkcs7.h"

unsigned char *restrict pkcs7_pad(const unsigned char *restrict buf,
		size_t buf_len, size_t blocksize)
{
	int i;
	unsigned char *padded;
	size_t padded_len, pad_chars;

	pad_chars  = (buf_len > blocksize)
		? (buf_len   % blocksize)
		: (blocksize - buf_len);
	padded_len = buf_len + pad_chars;

	if (!(padded = malloc(sizeof(unsigned char) * padded_len)))
		return NULL;
	else if (!memcpy(padded, buf, buf_len))
		return NULL;

	for (i = buf_len; i < padded_len; i++)
		padded[i] = pad_chars;

	return padded;
}

