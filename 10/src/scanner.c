#include "scanner.h"

typedef struct
{
    char const* start;
    char const* current;
    int line;
} Scanner;

Scanner scanner;

void initScanner(char const* source)
{
    scanner.start   = source;
    scanner.current = source;
    scanner.line    = 1;
}

static bool isAtEnd()
{
    return *scanner.current == '\0';
}
static bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}
static char advance()
{
    scanner.current++;
    return scanner.current[-1];
}
static char peek()
{
    return *scanner.current;
}
static char peekNext()
{
    if (isAtEnd())
        return '\0';
    return scanner.current[1];
}

static bool match(char expected)
{
    if (isAtEnd()) return false;
    if (*scanner.current != expected) return false;
    scanner.current++;
    return true;
}

static Token makeToken(TokenType type)
{
    Token token;
    token.type   = type;
    token.start  = scanner.start;
    token.line   = scanner.line;
    token.length = (int)(scanner.current - scanner.start);
    return token;
}
static Token errorToken(char* message)
{
    Token token;
    token.start  = message;
    token.type   = TOKEN_ERROR;
    token.length = (int)strlen(message);
    token.line   = scanner.line;
    return token;
}
static Token number()
{
    while (isDigit(peek())) advance();

    if (peek() == '.' && isDigit(peekNext()))
    {
        advance();
        while (isDigit(peek())) advance();
    }
    return makeToken(TOKEN_NUMBER);
}

static void skipWhiteSpaces()
{
    for (;;)
    {
        char c = peek();
        switch (c)
        {
            case '\r':
            case '\t':
            case ' ':
            {
                advance();
                break;
            }
            case '\n':
            {
                scanner.line++;
                advance();
                break;
            }
            case '/':
            {
                if (peekNext() == '/')
                {
                    //A comments goes till the end of the line
                    while (peek() != '\n' && !isAtEnd())
                    {
                        advance();
                    }
                }
                else
                {
                    return;
                }
                break;
            }
            default:
                return;
        }
    }
}
static TokenType checkKeyword(int start, int length, char const* rest, TokenType type)
{
    if (scanner.current - scanner.start == start + length // I should be more careful with operators precedence with this comparison
        && memcmp(scanner.start + start, rest, (unsigned long)length /* be careful of casting to unsigned long*/) == 0)
    {
        return type;
    }

    return TOKEN_IDENTIFIER;
}

static Token string()
{
    while (peek() != '"' && !isAtEnd())
    {
        if (peek() == '\n') { scanner.line++; }
        advance();
    }
    if (isAtEnd())
    {
        return errorToken("unterminated string.");
    }
    //consume the closing  qoute
    advance();

    return makeToken(TOKEN_STRING);
}

static bool isAlpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || c == '$';
}
static TokenType identifierType()
{
    switch (scanner.start[0])
    {
        //----- unbranched keywords ----------//
        case 'b': return checkKeyword(1, 6, "oolean", TOKEN_BOOLEAN);
        case 'd': return checkKeyword(1, 1, "o", TOKEN_DO);
        case 'e': return checkKeyword(1, 3, "lse", TOKEN_ELSE);
        case 'l': return checkKeyword(1, 2, "et", TOKEN_LET);
        case 'm': return checkKeyword(1, 5, "ethod", TOKEN_METHOD);
        case 'n': return checkKeyword(1, 3, "ull", TOKEN_NULL);
        case 'r': return checkKeyword(1, 5, "eturn", TOKEN_RETURN);
        case 's': return checkKeyword(1, 6, "tatic", TOKEN_STATIC);
        case 'w': return checkKeyword(1, 4, "hile", TOKEN_WHILE);

        //----- unbranched keywords ----------//
        case 'c':
        {
            if (scanner.current - scanner.start > 1)

            {

                switch (scanner.start[1])
                {
                    case 'h': return checkKeyword(2, 2, "ar", TOKEN_CHAR);
                    case 'l': return checkKeyword(2, 3, "ass", TOKEN_CLASS);
                    case 'o': return checkKeyword(2, 9, "nstructor", TOKEN_CONSTRUCTOR);
                }
            }
            break;
        }

        case 'f':
        {
            if (scanner.current - scanner.start > 1)
            {
                switch (scanner.start[1])
                {
                    case 'a': return checkKeyword(2, 3, "lse", TOKEN_FALSE);
                    case 'i': return checkKeyword(2, 4, "eld", TOKEN_FIELD);
                    case 'u': return checkKeyword(2, 5, "nction", TOKEN_FUNCTION);
                }
            }
            break;
        }

        case 'i':
        {
            if (scanner.current - scanner.start > 1)
            {
                switch (scanner.start[1])
                {
                    case 'f': return checkKeyword(2, 0, "", TOKEN_IF);
                    case 'n': return checkKeyword(2, 1, "t", TOKEN_INT);
                }
            }
            break;
        }
        case 't':
        {
            if (scanner.current - scanner.start > 1)
            {
                switch (scanner.start[1])
                {
                    case 'h': return checkKeyword(2, 2, "is", TOKEN_THIS);
                    case 'r': return checkKeyword(2, 2, "re", TOKEN_TRUE);
                }
            }
            break;
        }
        case 'v':
        {
            if (scanner.current - scanner.start > 1)
            {
                switch (scanner.start[1])
                {
                    case 'a': return checkKeyword(2, 1, "r", TOKEN_VAR);
                    case 'o': return checkKeyword(2, 2, "id", TOKEN_VOID);
                }
            }
            break;
        }
    }

    return TOKEN_IDENTIFIER;
}
static Token identifier()
{
    while (isAlpha(peek()) || isDigit(peek())) advance();
    return makeToken(identifierType());
}
Token scanToken()
{
    skipWhiteSpaces();

    scanner.start = scanner.current;

    if (isAtEnd())
    {
        return makeToken(TOKEN_EOF);
    }
    char c = advance();

    //------ Scan for identifier first
    if (isAlpha(c)) return identifier();

    //------ scan for litearl numbers
    if (isDigit(c)) return number();
    switch (c)
    {
        //------- single character tokens -------------//
        case '(': return makeToken(TOKEN_LEFT_PAREN);
        case ')': return makeToken(TOKEN_RIGHT_PAREN);
        case '{': return makeToken(TOKEN_LEFT_BRACE);
        case '}': return makeToken(TOKEN_RIGHT_BRACE);
        case '[': return makeToken(TOKEN_LEFT_BRACKET);
        case ']': return makeToken(TOKEN_RIGHT_BRACKET);

        case ',': return makeToken(TOKEN_COMMA);
        case ';': return makeToken(TOKEN_SEMICOLON);

        case '+': return makeToken(TOKEN_PLUS);
        case '-': return makeToken(TOKEN_MINUS);
        case '/': return makeToken(TOKEN_SLASH);
        case '*': return makeToken(TOKEN_STAR);
        case '.': return makeToken(TOKEN_DOT);

        //------- two characters tokens -------------//
        case '&':
            return makeToken(
                match('&') ? TOKEN_AND_LOGICAL : TOKEN_AND);
        case '|':
            return makeToken(
                match('|') ? TOKEN_OR_LOGICAL : TOKEN_OR);
        case '!':
            return makeToken(
                match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
        case '=':
            return makeToken(
                match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
        case '<':
            return makeToken(
                match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
        case '>':
            return makeToken(
                match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);

            //------- litearls ------------//
        case '"': return string();

        default:
        {
            break;
        }
    }

    return errorToken("Unexpected character.");
}
