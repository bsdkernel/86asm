#pragma once

/* Including libraries */
#include <stddef.h>

/* Token type */
typedef enum {
	TOKEN_IDENTIFIER,
	TOKEN_NUMBER,

	TOKEN_COMMA,
	TOKEN_COLON,
	TOKEN_LBRACKET,
	TOKEN_RBRACKET,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_STAR,

	TOKEN_NEWLINE,
	TOKEN_EOF,
	TOKEN_INVALID
} TokenType;

/* Struct of Token */
typedef struct {
	TokenType type;

	const char *start;
	size_t length;
} Token;

/* Lexer */
typedef struct {
	const char *source;
	size_t position;

	size_t line;
	size_t column;
} Lexer;

/* Prototypes */
void lexer_init(Lexer *lexer, const char *source);
Token lexer_next_token(Lexer *lexer);