#include <stdio.h>
#include <stdlib.h>
#include <openssl/aes.h>

#define BLOCKSIZE	16

int main(int argc, const char *argv[])
{
	int i, c;
	AES_KEY key;
	unsigned char buf[BLOCKSIZE], decrypted_buf[BLOCKSIZE + 1];
	FILE *file          = NULL;
	unsigned char *pass = (unsigned char *) "YELLOW SUBMARINE";

	if (argc != 2 || !(file = fopen(argv[1], "rb"))) {
		fputs("Usage: ./ecb <filename>\n", stderr);
		return 1;
	}

	AES_set_decrypt_key(pass, 128, &key);

	while (c != EOF) {
		for (i = 0; i < BLOCKSIZE; i++)
			if ((c = fgetc(file)) == EOF)
				break;
			else
				buf[i] = c;

		AES_decrypt(buf, decrypted_buf, &key);
		decrypted_buf[i] = '\0';
		fputs((char *) decrypted_buf, stdout);
	}

	if (file)
		fclose(file);
	return 0;
}

