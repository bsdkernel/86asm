#pragma once

/* Including libraries */
#include "lexer.h"

/* Parser struct */
typedef struct
{
	Lexer lexer;
	Token current;
} Parser;

/* Prototypes */
void parser_init(Parser *parser, const char *source);