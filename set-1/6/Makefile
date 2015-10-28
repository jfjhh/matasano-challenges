CC     = gcc
CFLAGS = --std=c99 -g -Wall -Werror -pedantic -O2

all: keysize block-transpose

keysize: hamming.c keysize.c

block-transpose: block-transpose.c

clean:
	rm keysize block-transpose
