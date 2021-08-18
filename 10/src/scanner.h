#ifndef SCANNER_H
#define SCANNER_H
#include <string.h>
#include <stdbool.h>
typedef enum
{
    // Single-character tokens.
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,
    TOKEN_LEFT_BRACKET,
    TOKEN_RIGHT_BRACKET,
    TOKEN_COMMA,
    TOKEN_DOT,
    TOKEN_MINUS,
    TOKEN_PLUS,
    TOKEN_SEMICOLON,
    TOKEN_SLASH,
    TOKEN_STAR,
    TOKEN_NOT,

    // One or two character tokens.
    TOKEN_AND,
    TOKEN_AND_LOGICAL,
    TOKEN_BANG,
    TOKEN_BANG_EQUAL,
    TOKEN_EQUAL,
    TOKEN_EQUAL_EQUAL,
    TOKEN_GREATER,
    TOKEN_GREATER_EQUAL,
    TOKEN_LESS,
    TOKEN_LESS_EQUAL,
    TOKEN_OR,
    TOKEN_OR_LOGICAL,

    // Literals.
    TOKEN_IDENTIFIER,
    TOKEN_STRING,
    TOKEN_NUMBER,
    // Keywords.

    TOKEN_BOOLEAN,
    TOKEN_CHAR,
    TOKEN_CLASS,
    TOKEN_CONSTRUCTOR,
    TOKEN_DO,
    TOKEN_ELSE,
    TOKEN_FALSE,
    TOKEN_FIELD,
    TOKEN_FUNCTION,
    TOKEN_IF,
    TOKEN_INT,
    TOKEN_LET,
    TOKEN_METHOD,
    TOKEN_NULL,
    TOKEN_RETURN,
    TOKEN_STATIC,
    TOKEN_THIS,
    TOKEN_TRUE,
    TOKEN_VAR,
    TOKEN_VOID,
    TOKEN_WHILE,

    TOKEN_ERROR,
    TOKEN_EOF
} TokenType;

typedef struct
{
    TokenType type;
    char const* start;
    int line;
    int length;

} Token;

void initScanner(char const* source);
Token scanToken(void);

#endif
