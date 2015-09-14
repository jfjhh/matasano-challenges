CC = gcc
CFLAGS = --std=c99 -g -Wall -Werror -pedantic -O2 -I. -I..

all: xor

xor: byte-xor.c ../strtohex.c
	$(CC) $(CFLAGS) -o byte-xor byte-xor.c ../strtohex.c

clean:
	rm byte-xor

