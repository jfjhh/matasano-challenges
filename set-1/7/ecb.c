#include <stdio.h>
#include <stdlib.h>
#include <openssl/ssl.h>

int main(void)
{
	SSL *ssl;
	SSL_CTX *ctx;

	SSL_library_init();

	if (!(ctx = SSL_CTX_new(method))) {
		fputs("Could not make a SSL_CTX structure!\n");
		return 1;
	}

	if (!(ssl = SSL_new(ctx))) {
		fputs("Could not make a SSL structure!\n");
		return 1;
	}

	return 0;
}

