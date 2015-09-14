#include <stdio.h>
#include <string.h>

#include "hamming.h"

int main(int argc, const char *argv[])
{
	int distance;

	if (argc != 3) {
		fprintf(stderr, "Need the two strings to ham!\n");
		return 1;
	}
	fprintf(stderr, "Using strings '%s' and '%s'.\n", argv[1], argv[2]);

	distance = hamming_distance((unsigned char *) argv[1],
			(unsigned char *) argv[2],
			strlen(argv[1]), strlen(argv[2]));

	printf("The hamming distance between\n\"%s\"\nand\n\"%s\"\n... is %d.\n",
			argv[1], argv[2], distance);

	return 0;
}


