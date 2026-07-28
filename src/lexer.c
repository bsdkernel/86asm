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

/* Getting next token */
Token
lexer_next_token(Lexer *lexer)
{
	while (lexer->source[lexer->position] == ' ' ||
		lexer->source[lexer->position] == '\t' ||
		lexer->source[lexer->position] == '\r')
	{
		lexer->position++;
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

	if (isalpha((unsigned char)current) || current == '_')
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

	Token token = {0};
	token.type = TOKEN_INVALID;
	token.start = lexer->source + lexer->position;
	token.length = 1;

	lexer->position++;

	return token;
}