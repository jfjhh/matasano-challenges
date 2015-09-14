CC = gcc
CFLAGS = --std=c99 -g -Wall -Werror -pedantic -O2 -I. -I.. -lm

all: xor

xor: xor-detect.c ../strtohex.c
	$(CC) $(CFLAGS) -o xor-detect xor-detect.c ../strtohex.c

clean:
	rm xor-detect

