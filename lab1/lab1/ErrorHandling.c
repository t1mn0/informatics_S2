#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define RESET   "\033[0m"
#define RED     "\033[1;31m"

typedef enum {
    NO_ERROR, // 0
    NULL_POINTER_ERROR,
    MEMORY_ALLOCARTION_ERROR,
    ARRAY_INDEX_OUT_OF_BOUNDS_ERROR,
    INVALID_INPUT_ERROR,
    INPUT_TYPE_ERROR,
    TRY_AGAIN,
    NO_ARRAY
} ErrorType;

void handleErrorCode(ErrorType error) {
    if (error != NO_ERROR) {
        switch (error) {
        case NULL_POINTER_ERROR:
            printf("%sError: NULL_POINTER_ERROR\n%s", RED, RESET);
            exit(EXIT_FAILURE);
            break;
        case MEMORY_ALLOCARTION_ERROR:
            printf("%sError: MEMORY_ALLOCATION_ERROR\n%s", RED, RESET);
            exit(EXIT_FAILURE);
            break;
        case ARRAY_INDEX_OUT_OF_BOUNDS_ERROR:
            printf("%sError: ARRAY_INDEX_OUT_OF_BOUNDS_ERROR\n%s", RED, RESET);
            break;
        case INVALID_INPUT_ERROR:
            printf("%sError: INVALID_INPUT_ERROR\n%s", RED, RESET);
            break;
        case INPUT_TYPE_ERROR:
            printf("%sError: INPUT_TYPE_ERROR\n%s", RED, RESET);
            break;
        case TRY_AGAIN:
            printf("%sError: INVALID_INPUT_ERROR\n%s", RED, RESET);
            printf("%sTry input again\n%s", RED, RESET);
            break;
        case NO_ARRAY:
            printf("%sError: NO_ARRAY_ERROR\n%s", RED, RESET);
            printf("%sAt least one array must be created!\n%s", RED, RESET);
            break;
        default:
            break;
        }
    }
}