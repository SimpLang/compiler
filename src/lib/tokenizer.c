#include "tokenizer.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isIdentifierChar(char c)
{
    return isalnum(c) || c == '_';
}

Token* tokenize(char* sourceCode) {
    Token* tokens = NULL;
    int numTokens = 0;
    int tokenIndex = 0;

    char* tokenStr = sourceCode;
    while (*tokenStr != '\0') {
        while (isspace(*tokenStr)) {
            tokenStr++;
        }

        if (strncmp(tokenStr, "//", 2) == 0) {
            while (*tokenStr != '\0' && *tokenStr != '\n') {
                tokenStr++;
            }
        }
        else if (strchr("(){}[];,", *tokenStr) != NULL) {
            tokens = (Token*)realloc(tokens, (numTokens + 1) * sizeof(Token));
            if (tokens == NULL) {
                perror("Error allocating memory for tokens");
                exit(1);
            }

            if (*tokenStr == '(') {
                tokens[numTokens].type = TOKEN_LEFT_PAREN;
            } else if (*tokenStr == ')') {
                tokens[numTokens].type = TOKEN_RIGHT_PAREN;
            } else if (*tokenStr == '{') {
                tokens[numTokens].type = TOKEN_LEFT_BRACE;
            } else if (*tokenStr == '}') {
                tokens[numTokens].type = TOKEN_RIGHT_BRACE;
            } else if (*tokenStr == '[') {
                tokens[numTokens].type = TOKEN_LEFT_BRACKET;
            } else if (*tokenStr == ']') {
                tokens[numTokens].type = TOKEN_RIGHT_BRACKET;
            } else if (*tokenStr == ';') {
                tokens[numTokens].type = TOKEN_SEMICOLON;
            } else if (*tokenStr == ',') {
                tokens[numTokens].type = TOKEN_COMMA;
            }

            tokens[numTokens].lexeme = strndup(tokenStr, 1);
            numTokens++;
            tokenStr++;
        }
        else if (*tokenStr == '"') {
            char* start = ++tokenStr;
            while (*tokenStr != '"' && *tokenStr != '\0') {
                tokenStr++;
            }

            if (*tokenStr == '"') {
                tokens = (Token*)realloc(tokens, (numTokens + 1) * sizeof(Token));
                if (tokens == NULL) {
                    perror("Error allocating memory for tokens");
                    exit(1);
                }

                tokens[numTokens].type = TOKEN_STRING;
                tokens[numTokens].lexeme = strndup(start, tokenStr - start);
                numTokens++;

                tokenStr++;
            } else {
                printf("Error: Unterminated string literal.\n");
                exit(1);
            }
        }
        else if (isalpha(*tokenStr) || *tokenStr == '_') {
            char* start = tokenStr;
            while (isIdentifierChar(*tokenStr)) {
                tokenStr++;
            }

            tokens = (Token*)realloc(tokens, (numTokens + 1) * sizeof(Token));
            if (tokens == NULL) {
                perror("Error allocating memory for tokens");
                exit(1);
            }

            tokens[numTokens].type = TOKEN_IDENTIFIER;
            tokens[numTokens].lexeme = strndup(start, tokenStr - start);
            numTokens++;

            if (isFunction(tokens[numTokens - 1].lexeme)) {
                executeFunction(tokens, &tokenIndex);
            }
        }
        else {
            printf("Error: Unrecognized character: %c\n", *tokenStr);
            exit(1);
        }
    }

    tokens = (Token*)realloc(tokens, (numTokens + 1) * sizeof(Token));
    if (tokens == NULL) {
        perror("Error allocating memory for tokens");
        exit(1);
    }
    tokens[numTokens].type = TOKEN_UNKNOWN;
    tokens[numTokens].lexeme = NULL;

    return tokens;
}

void freeTokens(Token *tokens)
{
    if (tokens == NULL)
    {
        return;
    }

    for (int i = 0; tokens[i].lexeme != NULL; i++)
    {
        free(tokens[i].lexeme);
    }
    free(tokens);
}

void executeFunction(Token *tokens, int *tokenIndex)
{
    char *functionName = tokens[*tokenIndex].lexeme;
    (*tokenIndex++);

    if (tokens[*tokenIndex].type == TOKEN_STRING)
    {
        if (strcmp(functionName, "println") == 0)
        {
            if (tokens[*tokenIndex].lexeme != NULL)
            {
                printf("%s\n", tokens[*tokenIndex].lexeme);
            }
            else
            {
                printf("Error: Null string argument for println\n");
                exit(1);
            }

            (*tokenIndex)++;
        }
    }
    else
    {
        printf("Error: %s expects a string argument not a '%d'\n", functionName, tokens[*tokenIndex].type);
        exit(1);
    }

    if (tokens[*tokenIndex].type == TOKEN_RIGHT_PAREN)
    {
        (*tokenIndex)++;
    }
    else
    {
        printf("Error: Missing closing parenthesis after %s\n", functionName);
        exit(1);
    }
}
