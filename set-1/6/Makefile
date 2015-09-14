CC     = gcc
CFLAGS = --std=c99 -g -Wall -Werror -pedantic -O2

blocks  ?= 8
min_key ?= 2
max_key ?= 40

CFLAGS += -D BLOCKS=$(blocks)
CFLAGS += -D MIN_KEY=$(min_key)
CFLAGS += -D MAX_KEY=$(max_key)

all: test-64 test-hamming keysize

test-64: base64.c test-64.c

test-hamming: hamming.c test-hamming.c

keysize: hamming.c keysize.c

clean:
	rm test-hamming test-64 keysize
