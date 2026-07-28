#include "lexer.h"
#include <ctype.h>

/* Lexer initialize */
void
lexer_init(Lexer *lexer, 
	const char *source)
{
	lexer->source = source;
	lexer->position = 0;
	lexer->line = 1;
	lexer->column = 1;
}

static int
is_digit_for_base(char c, int base)
{
	if (c >= '0' && c <= '9')
		return (c - '0') < base;

	if (base == 16 && c >= 'a' && c <= 'f')
		return 1;

	if (base == 16 && c >= 'A' && c <= 'F')
		return 1;

	return 0;
}

static Token
lexer_read_number(Lexer *lexer)
{
	size_t start = lexer->position;
	int base = 10;

	Token token = {0};
	token.start = lexer->source + start;

	if (lexer->source[lexer->position] == '0')
	{
		char next = lexer->source[lexer->position + 1];

		if (next == 'x' || next == 'X')
		{
			base = 16;
			lexer->position += 2;
		}
		else if (next == 'b' || next == 'B')
		{
			base = 2;
			lexer->position += 2;
		}
	}

	size_t digits_start = lexer->position;

	while (is_digit_for_base(lexer->source[lexer->position], base))
	{
		lexer->position++;
	}

	if (lexer->position == digits_start)
	{
		token.type = TOKEN_INVALID;
		token.length = lexer->position - start;
		return token;
	}

	char next = lexer->source[lexer->position];

	if (isalnum((unsigned char)next) || next == '_')
	{
		while (isalnum((unsigned char)lexer->source[lexer->position]) ||
		       lexer->source[lexer->position] == '_')
		{
			lexer->position++;
		}

		token.type = TOKEN_INVALID;
		token.length = lexer->position - start;
		return token;
	}

	token.type = TOKEN_NUMBER;
	token.length = lexer->position - start;

	return token;
}

/* Getting next token */
Token
lexer_next_token(Lexer *lexer)
{
	for (;;)
	{
		while (lexer->source[lexer->position] == ' ' ||
			lexer->source[lexer->position] == '\t' ||
			lexer->source[lexer->position] == '\r')
    {
    	lexer->position++;
    }

    if (lexer->source[lexer->position] != ';')
        break;

    while (lexer->source[lexer->position] != '\n' &&
    	lexer->source[lexer->position] != '\0')
    {
    	lexer->position++;
    }
	}

	char current = lexer->source[lexer->position];

	if (current == '\0') 
	{
		Token token = {0};
		token.type = TOKEN_EOF;
		token.start = lexer->source + lexer->position;
		token.length = 0;

		return token;
	}
	else if (current == '\n')
	{
		Token token = {0};
		token.type = TOKEN_NEWLINE;
		token.start = lexer->source + lexer->position;
		token.length = 1;

		lexer->position++;
		lexer->line++;
		lexer->column = 1;
	
		return token;
	}
	else if (current == ',')
	{
		Token token = {0};
		token.type = TOKEN_COMMA;
		token.start = lexer->source + lexer->position;
		token.length = 1;

		lexer->position++;

		return token;
	}
	else if (current == ':')
	{
		Token token = {0};
		token.type = TOKEN_COLON;
		token.start = lexer->source + lexer->position;
		token.length = 1;

		lexer->position++;

		return token;
	}
	else if (isalpha((unsigned char)current) || current == '_')
	{
		size_t start = lexer->position;

		while (isalnum((unsigned char)current) ||
			current == '_')
		{
			lexer->position++;
			current = lexer->source[lexer->position];
		}

		Token token = {0};
		token.type = TOKEN_IDENTIFIER;
		token.start = lexer->source + start;
		token.length = lexer->position - start;

		return token;
	}
	else if (isdigit((unsigned char)current))
	{
		return lexer_read_number(lexer);
	}

	Token token = {0};
	token.type = TOKEN_INVALID;
	token.start = lexer->source + lexer->position;
	token.length = 1;

	lexer->position++;

	return token;
}