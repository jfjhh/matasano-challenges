#!/bin/bash

for i in $*; do
	KEY="`./block-transpose $i XOR-file 2> /dev/null`"
	echo "Testing keysize $i, which gave XOR key '$KEY'."
	../5/repeat-xor "$KEY" < XOR-file > decrypted/${i}.out
done

