#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/compiler.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    char* sourceFile = argv[1];

    // Check if the file exists
    FILE* file = fopen(sourceFile, "r");
    if (file == NULL) {
        printf("Error: File not found.\n");
        return 1;
    }

    // Read the source code from the file
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* sourceCode = (char*)malloc(fileSize + 1);
    if (sourceCode == NULL) {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    fread(sourceCode, 1, fileSize, file);
    sourceCode[fileSize] = '\0';
    fclose(file);

    // Call your compilation function
    compile(sourceCode);

    // Clean up
    free(sourceCode);

    return 0;
}
