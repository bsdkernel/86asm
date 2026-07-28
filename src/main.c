#include <stdio.h>
#include <string.h>

#include "lexer.h"

void
print_usage(char *argv[])
{
	printf("Usage: %s (source file) -o (output binary file)\n",
		argv[0]);
}

int
file_exists(const char *path)
{
	FILE *f = fopen(path, "r");
	if (f)
	{
		fclose(f);
		return 1;
 	}
	return 0;
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

	/* Check for the existence of the source file */
	if (!file_exists(argv[1]))
	{
		printf("Error: file '%s' does not exist.\n",
			argv[1]);
		return 1;
	}

	/* TODO */

	return 0;
}