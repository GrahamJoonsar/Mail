#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Getting a refereence to the file
static FILE * getFile(const char * filename){
    FILE * file = fopen(filename, "r");
    if (!file) {
        printf("File was not found.\n");
        return 0;
    } else {
        return file;
    }
}

// Getting the number of lines in a file
static unsigned long getFileSize(FILE* file) {
    unsigned long size = 0;
    for (char c = getc(file); c != EOF; c = getc(file)) if (c == '\n') size++;
    rewind(file);
    return size+1;
}

// Returns an array of strings that represent the file (Doesnt include newlines)
char ** getLinesFromFile(char * filename, unsigned long * fSize){
    // Getting file
    FILE * file = getFile(filename);
    if (!file) return 0;

    // Getting lines in the file
    unsigned long fileSize = getFileSize(file);

    // Storing all of the lines from the file
    char ** lines = malloc(sizeof(char*)*fileSize);
    memset(lines, 0, fileSize);

    // Getting all lines from the file
    for (int i = 0; i < fileSize; i++){
        lines[i] = malloc(sizeof(char)*256);
        memset(lines[i], 0, 256);
        fgets(lines[i], 256, file);
        // get rid of newline
        if (lines[i][strlen(lines[i])-1] == '\n') lines[i][strlen(lines[i])-1] = '\0';
    }

    // Closing the file
    fclose(file);

    *fSize = fileSize;
    return lines;
}