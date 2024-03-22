#pragma once

#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

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


void handleErrorCode(ErrorType error);

#endif