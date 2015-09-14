#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	int i, c, len;

	if (argc != 2) {
		fprintf(stderr, "Need the repeating key as first argument!\n");
		return 1;
	}

	len = strlen(argv[1]);

	i = 0;
	while ((c = getchar()) != EOF) {
		if (i == len)
			i = 0;
		putchar(c ^ argv[1][i++]);
	}

	return 0;
}

