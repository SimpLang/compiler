#ifndef TOKENIZER_H
#define TOKENIZER_H

// Define token types
typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_CONSTANT,
    TOKEN_OPERATOR,
    TOKEN_SEPARATOR,
    TOKEN_COMMENT,
    TOKEN_UNKNOWN,
    TOKEN_STRING,
    TOKEN_LEFT_PAREN,    // Added
    TOKEN_RIGHT_PAREN,   // Added
    TOKEN_LEFT_BRACE,    // Added
    TOKEN_RIGHT_BRACE,   // Added
    TOKEN_LEFT_BRACKET,  // Added
    TOKEN_RIGHT_BRACKET, // Added
    TOKEN_SEMICOLON,     // Added
    TOKEN_COMMA,         // Added
    TOKEN_FUNCTION_CALL, // Added
} TokenType;

// Structure to represent a token
typedef struct {
    TokenType type;
    char* lexeme;
} Token;

// Function to tokenize source code
Token* tokenize(char* sourceCode);

// Function to free memory allocated for tokens
void freeTokens(Token* tokens);

#endif // TOKENIZER_H
