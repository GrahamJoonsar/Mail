// STD Library //
#include <stdio.h>
#include <stdlib.h>

// Language Library //
#include "file_operations.h" // For opening the file
#include "direction.h"       // For moving the file ptr

#define STACK_SIZE 2048

int main(int argc, char * argv[]){
    // Getting file and lines of file
    unsigned long fileSize;
    char ** lines = getLinesFromFile(argv[1], &fileSize);

    // File didnt open
    if (!lines) return 8;

    // The function ptr position
    Position fptr = {0, 0};

    // Current direction of the fptr
    const Position * currentDir = &RIGHT;

    // The current char (function) that is being executed
    char function;
    
    // The stack used in the program
    int stack[STACK_SIZE];
    unsigned int stackptr = 0;

    // For telling if the last number was numeric or not
    int wasNumeric = 0;
    // In quotes
    int isString = 0;
    // Length of current string
    int stringLen = 0;
    // loop variable
    int running = 1;
    while (running){
        function = lines[fptr.y][fptr.x];

        if (isString){
            if (function == '"'){ // End quote
                isString = 0;
                stack[++stackptr] = stringLen;
                stringLen = 0;
                addPosition(&fptr, currentDir);
                continue;
            }
            stack[++stackptr] = function;
            stringLen++;
            addPosition(&fptr, currentDir);
            continue;
        }

        switch(function){
            // Changing directional movement
            case '>': currentDir = &RIGHT; break;
            case '<': currentDir = &LEFT;  break;
            case 'v': currentDir = &DOWN;  break;
            case '^': currentDir = &UP;    break;

            // Moving the stack pointer //
            // Move right
            case '}': stackptr++; stackptr %= STACK_SIZE; break;
            // Move left
            case '{': stackptr--; break;

            // Conditional if (if the current item on the stack is not 0 skip the next instruction)
            case '?': if (stack[stackptr]) addPosition(&fptr, currentDir); break;
            // Skip the next intruction (Better for more compact programs)
            case '~': addPosition(&fptr, currentDir); break;

            // Output //
            // Print as character
            case '.': printf("%c", (char)((stack[stackptr])%256)); break;
            // Print as number
            case ',': printf("%d", stack[stackptr]); break;

            case '_': printf("\n"); break;

            // Input //
            case '$': scanf("%d", &stack[stackptr]); break;

            // Using numbers
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':

            if (!wasNumeric) stack[stackptr] = 0;
            stack[stackptr] *= 10;
            stack[stackptr] += function - '0';
            break;

            // Arithmetic //
            case '+': {
                int val = stack[--stackptr];
                val += stack[stackptr+1];
                stack[stackptr] = val;
                break;
            }
            case '-': {
                int val = stack[--stackptr];
                val -= stack[stackptr+1];
                stack[stackptr] = val;
                break;
            }
            case '*': {
                int val = stack[--stackptr];
                val *= stack[stackptr+1];
                stack[stackptr] = val;
                break;
            }
            case '/': {
                int val = stack[--stackptr];
                val /= stack[stackptr+1];
                stack[stackptr] = val;
                break;
            }

            // Strings
            case '"': if (!wasNumeric) isString = !isString; break;
            // Prints string and sets ptr to start of the string
            case '@': {
                for (int i = stackptr-stack[stackptr]; i < stackptr; i++){
                    printf("%c", stack[i]);
                }
                stackptr-=stack[stackptr];
            } break;

            // Exiting the program
            case ';': running = 0; break;
        }

        wasNumeric = !isString && ((function >= '0') && (function <= '9'));

        addPosition(&fptr, currentDir);
    }

    return 0;
}
