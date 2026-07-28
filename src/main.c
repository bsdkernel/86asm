#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

char
*read_file(const char *filename)
{
	FILE *file = fopen(filename, "rb");

	if (file == NULL) 
	{
		fprintf(stderr, "Cannot open file: %s\n", filename);
		return NULL;
	}

	if (fseek(file, 0, SEEK_END) != 0)
	{
		fprintf(stderr, "Cannot seek file\n");
		fclose(file);
		return NULL;
	}

	long file_size = ftell(file);

	if (file_size < 0)
	{
		fprintf(stderr, "Cannot determine file size\n");
		fclose(file);
		return NULL;
	}

	rewind(file);

	char *source = malloc((size_t)file_size + 1);

	if (source == NULL)
	{
		fprintf(stderr, "Cannot allocate memory\n");
		fclose(file);
		return NULL;
	}

	size_t bytes_read = fread(source, 1,
		(size_t)file_size, file);

	fclose(file);

	if (bytes_read != (size_t)file_size) {
		fprintf(stderr, "Cannot read entire file\n");
		free(source);
		return NULL;
	}

	source[bytes_read] = '\0';

	return source;
}

/* TODO: DEBUG FUNCTION, PLS DELETE */
const char *
token_type_name(TokenType type)
{
	switch (type)
	{
	case TOKEN_IDENTIFIER:
		return "TOKEN_IDENTIFIER";

	case TOKEN_NUMBER:
		return "TOKEN_NUMBER";

	case TOKEN_COMMA:
		return "TOKEN_COMMA";

	case TOKEN_NEWLINE:
		return "TOKEN_NEWLINE";

	case TOKEN_EOF:
		return "TOKEN_EOF";

	case TOKEN_INVALID:
		return "TOKEN_INVALID";

	case TOKEN_LBRACKET:
		return "TOKEN_LBRACKET";

	case TOKEN_RBRACKET:
		return "TOKEN_RBRACKET";

	case TOKEN_PLUS:
		return "TOKEN_PLUS";

	case TOKEN_MINUS:
		return "TOKEN_MINUS";

	default:
		return "TOKEN_UNKNOWN";
	}
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

	char *source = read_file(argv[1]);
	if (source == NULL) return 1;

	Lexer lexer;
	lexer_init(&lexer, source);

	Token token;

	do
	{
		token = lexer_next_token(&lexer);

		printf("Type: %-18s Text: %.*s\n",
			token_type_name(token.type),
			(int)token.length,
			token.start);
	} while (token.type != TOKEN_EOF);

	free(source);

	return 0;
}