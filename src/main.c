#include <stdio.h>
#include <string.h>

void
print_usage(char *argv[])
{
	printf("Usage: %s (source file) -o (output binary file)\n",
																										argv[0]);
}

int
main (int argc, char *argv[])
{
	/* Argument check */
	if (argc != 4 ||
			strcmp(argv[2], "-o") != 0) 
	{
		print_usage(argv);
		return 1;
	}

	/* TODO */

	return 0;
}