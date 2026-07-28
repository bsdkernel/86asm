#include "parser.h"

void
parser_init(Parser *parser, const char *source)
{
	lexer_init(&parser->lexer, source);
	parser->current = lexer_next_token(&parser->lexer);
}