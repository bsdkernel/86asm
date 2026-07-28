#include "lexer.h"

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
	// TODO
}