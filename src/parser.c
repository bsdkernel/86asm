#include "parser.h"

#include <stdbool.h>

void
parser_init(Parser *parser, const char *source)
{
	lexer_init(&parser->lexer, source);
	parser->current = lexer_next_token(&parser->lexer);
}

static void
parser_advance(Parser *parser)
{
	parser->current = lexer_next_token(&parser->lexer);
}

static bool
parser_check(Parser *parser, TokenType tokentype)
{
	TokenType currenttokentype = parser->current.type;
	if (currenttokentype == tokentype)
		return true;
	else
		return false;
}

static bool
parser_match(Parser *parser, TokenType tokentype)
{
	if (parser_check(parser, tokentype))
	{
		parser_advance(parser);
		return true;
	}
	return false;
}

/* TODO
static bool
parser_expect(Parser *parser, TokenType tokentype)
{
	if (parser_check(parser, tokentype))
	{
		parser_advance(parser);
		return true;
	}
	return false;
}
*/