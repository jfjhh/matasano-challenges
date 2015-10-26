#!/bin/bash
#
# Tests various key size finding parameters to keysize.c
# Alex Striff
#

[ -f keysize ] && rm keysize

for i in {2,4,8,16}; do
	for j in {10,20,30,40}; do
		make blocks=${i} max_key=${j} keysize && \
			echo -en "\033[0;32m" && \
			./keysize 6.txt.decoded && \
			echo -e "\033[0m"
		[ -f keysize ] && rm keysize
	done
done \
	| grep "The best found keysize was " \
	| sort \
	| sed 's/The best found keysize was /size: /' \
	| uniq -c \
	| sort -nr

