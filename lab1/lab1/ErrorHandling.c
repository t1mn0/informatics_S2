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
    TYPE_ERROR
} ErrorType;

void handleErrorCode(ErrorType error) {
    if (error != NO_ERROR) {
        switch (error) {
        case NULL_POINTER_ERROR:
            printf("%sNULL_POINTER_ERROR%s", RED, RESET);
            exit(EXIT_FAILURE);
            break;
        case MEMORY_ALLOCARTION_ERROR:
            printf("%sMEMORY_ALLOCARTION_ERROR%s", RED, RESET);
            exit(EXIT_FAILURE);
            break;
        case ARRAY_INDEX_OUT_OF_BOUNDS_ERROR:
            printf("%sARRAY_INDEX_OUT_OF_BOUNDS_ERROR%s", RED, RESET);
            exit(EXIT_FAILURE);
            break;
        case INVALID_INPUT_ERROR:
            printf("%sINVALID_INPUT_ERROR%s", RED, RESET);
            exit(EXIT_FAILURE);
            break;
        case TYPE_ERROR:
            printf("%sTYPE_ERROR%s", RED, RESET);
            exit(EXIT_FAILURE);
            break;
        default:
            break;
        }
    }
}