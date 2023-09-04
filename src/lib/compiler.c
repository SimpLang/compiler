#include "compiler.h"
#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>

// Function to get the name of a token type
const char* getTokenName(TokenType type) {
    switch (type) {
        case TOKEN_IDENTIFIER: return "TOKEN_IDENTIFIER";
        case TOKEN_KEYWORD: return "TOKEN_KEYWORD";
        case TOKEN_CONSTANT: return "TOKEN_CONSTANT";
        case TOKEN_OPERATOR: return "TOKEN_OPERATOR";
        case TOKEN_SEPARATOR: return "TOKEN_SEPARATOR";
        case TOKEN_COMMENT: return "TOKEN_COMMENT";
        case TOKEN_UNKNOWN: return "TOKEN_UNKNOWN";
        case TOKEN_STRING: return "TOKEN_STRING";
        case TOKEN_LEFT_PAREN: return "TOKEN_LEFT_PAREN";       // Added
        case TOKEN_RIGHT_PAREN: return "TOKEN_RIGHT_PAREN";     // Added
        case TOKEN_LEFT_BRACE: return "TOKEN_LEFT_BRACE";       // Added
        case TOKEN_RIGHT_BRACE: return "TOKEN_RIGHT_BRACE";     // Added
        case TOKEN_LEFT_BRACKET: return "TOKEN_LEFT_BRACKET";   // Added
        case TOKEN_RIGHT_BRACKET: return "TOKEN_RIGHT_BRACKET"; // Added
        case TOKEN_SEMICOLON: return "TOKEN_SEMICOLON";         // Added
        case TOKEN_COMMA: return "TOKEN_COMMA";                 // Added
        case TOKEN_FUNCTION_CALL: return "TOKEN_FUNCTION_CALL"; // Added
        default: return "UNKNOWN";
    }
}

// Define your compilation function here
void compile(char* sourceCode) {
    // printf("Source Code:\n%s\n", sourceCode);

    // Tokenize the source code
    Token* tokens = tokenize(sourceCode);
    for (int i = 0; tokens[i].lexeme != NULL; i++) {
        printf("%s: %s\n", getTokenName(tokens[i].type), tokens[i].lexeme);
    }

    // Free the allocated memory for tokens
    freeTokens(tokens);
}
