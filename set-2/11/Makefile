CC     = gcc
CFLAGS = -Wall -Werror -std=c99 -pedantic -g -O2 -lcrypto

all:           test-crypt test-oracle

buf_encrypt.o: buf_encrypt.c

oracle.o:      oracle.c

randcrypt.o:   randcrypt.c buf_encrypt.o

test-crypt:    test-crypt.c buf_encrypt.o

test-oracle:   test-oracle.c oracle.o randcrypt.o buf_encrypt.o

clean:
	rm test-oracle test-crypt buf_encrypt.o oracle.o randcrypt.o


