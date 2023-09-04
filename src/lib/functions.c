#include "functions.h"
#include "tokenizer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to execute println with a string argument
void executePrintln(Token* tokens) {
    // Check if there are enough tokens for the function call
    if (tokens[0].type == TOKEN_STRING && tokens[1].type == TOKEN_RIGHT_PAREN) {
        printf("%s\n", tokens[0].lexeme);
    } else {
        // Handle error - incorrect argument list for println
        printf("Error: Invalid argument list for println\n");
        exit(1);
    }
}

void println(const char* args) {
    printf("%s\n", args);
}

// List of known functions
const char* functions[] = {
    "println",
    NULL
};

int isFunction(const char* token) {
    for (int i = 0; functions[i] != NULL; i++) {
        if (strcmp(token, functions[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
