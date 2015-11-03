CC     = gcc
CFLAGS = -Wall -Werror -std=c99 -pedantic -g -O2 -lcrypto -Iutil/

all: byte-ecb-decrypt

byte-ecb-decrypt: byte-ecb-decrypt.c \
	util/randcrypt.c util/coreutils-base64.c \
	util/oracle.c util/buf_encrypt.c

clean:
	rm byte-ecb-decrypt

