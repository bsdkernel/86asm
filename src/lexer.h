#pragma once

/* Including libraries */
#include <stdio.h>
#include <stdint.h>

/* Token type */
typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,

    TOKEN_COMMA,
    TOKEM_COLON,
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

    char text[64]; // TODO: Remove fixed size
    uint64_t num;
} Token;