#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET   "\033[0m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"

typedef struct {
    void** list;
    int size;
    int capacity;
} dynamic_array;

void freeList(dynamic_array* darr, int errorCode) {
    switch (errorCode) {
    case 0:
        printf("%s - - - Work with <list.c> was completed correctly - - - %s\n", GREEN, RESET);
        break;

    case 1:
        printf("%s - - - Segmentation fault - - - %s\n", RED, RESET);
        exit(EXIT_FAILURE);
        // break;
    case 2:
        printf("%s - - - Invalid Syntax - - - %s\n", RED, RESET);
        exit(EXIT_FAILURE);
        // break;
    case 3:
        printf("%s - - - Index Out Of Bounds - - - %s\n", RED, RESET);
        exit(EXIT_FAILURE);
        // break;
    case 4:
        printf("%s - - - Addressing to NULL pointer - - - %s\n", RED, RESET);
        exit(EXIT_FAILURE);
        // break;
    default:
        break;
    }
    free(darr->list);
    free(darr);
}


dynamic_array* newList() {
    dynamic_array* darr = (dynamic_array*)malloc(sizeof(dynamic_array));
    if (darr == NULL) {
        freeList(darr, 1);
    }

    darr->size = 0;
    darr->capacity = 5;

    darr->list = (void**)malloc(darr->capacity * sizeof(void*));
    if (darr->list == NULL) {
        freeList(darr, 1);
    }

    return darr;
}

void resize(dynamic_array* darr) {
    darr->capacity += 5;
    darr->list = (void**)realloc(darr->list, darr->capacity * sizeof(void*));
    if (darr->list == NULL) {
        freeList(darr, 1);
    }
}

void addString(dynamic_array* darr, char* str) {
    if (darr->size == darr->capacity) {
        resize(darr);
    }
    darr->list[darr->size] = _strdup(str);
    if (darr->list[darr->size] == NULL) {
        freeList(darr, 1);
    }
    darr->size++;
}

void addDouble(dynamic_array* darr, double n) {
    if (darr->size == darr->capacity) {
        resize(darr);
    }
    char* n_pointer = (char*)malloc(sizeof(char*));
    
    if (n_pointer == NULL) {
        freeList(darr, 1);
    }

    snprintf(n_pointer, sizeof n_pointer, "%lf", n);
    darr->list[darr->size] = n_pointer;
    darr->size++;
}

int isString(char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if ((isdigit(str[i]) == 0) && ((str[i]) != '.') && ((str[i]) != '-')) {
            return 1;
        }
    }
    return 0;
}

int isDouble(char* str) {
    if (isString(str) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void printList(dynamic_array* darr) {
    if (darr == NULL) {
        freeList(darr, 4);
    }

    for (int i = 0; i < darr->size; i++) {
        if (darr->list[i] != NULL) {
            printf("%s\n", darr->list[i]);
        }
        else {
            freeList(darr, 4);
        }
    }
}



dynamic_array* concatenation(dynamic_array* darr1, dynamic_array* darr2) {
    dynamic_array* darr = newList();
    for (int i = 0; i < darr1->size; i++) {
        addString(darr, darr1->list[i]);
    }
    for (int i = 0; i < darr2->size; i++) {
        addString(darr, darr2->list[i]);
    }
    //freeList(darr1, -1);
    //freeList(darr2, -1);
    return darr;
}

void mapString(char* (*func)(char*), dynamic_array* darr) {
    for (int i = 0; i < darr->size; i++) {
        if (isString(darr->list[i]) == 1) {
            darr->list[i] = func(darr->list[i]);
        }
    }
}

void mapDouble(double (*func)(double), dynamic_array* darr) {
    for (int i = 0; i < darr->size; i++) {
        if (isString(darr->list[i]) == 0) {
            char* n_pointer = (char*)malloc(sizeof(char*));

            if (n_pointer == NULL) {
                freeList(darr, 1);
            }

            snprintf(n_pointer, sizeof n_pointer, "%lf", func(atof(darr->list[i])));
            darr->list[i] = n_pointer;
        }
    }
}

dynamic_array* where(int (*func)(char*), dynamic_array* darr) {
    dynamic_array* darrWhere = newList();
    for (int i = 0; i < darr->size; i++) {
        if (func(darr->list[i]) == 1) {
            addString(darrWhere, darr->list[i]);
        }
    }
    return darrWhere;
}



dynamic_array* fragmentString(dynamic_array* darr) {
    return where(*isString, darr);
}

dynamic_array* fragmentDouble(dynamic_array* darr) {
    return where(*isDouble, darr);
}

int compareDouble1(void* a, void* b) {
    double num1 = atof(*(char**)a);
    double num2 = atof(*(char**)b);

    if (num1 < num2) return -1;
    else if (num1 > num2) return 1;
    else return 0;
}

int compareDouble0(void* a, void* b) {
    double num1 = atof(*(char**)a);
    double num2 = atof(*(char**)b);

    if (num1 > num2) return -1;
    else if (num1 < num2) return 1;
    else return 0;
}

void sortDouble(dynamic_array* darr, int param) {
    if (param == 1) {
        qsort(darr->list, darr->size, sizeof(char*), compareDouble1);
    }
    else {
        qsort(darr->list, darr->size, sizeof(char*), compareDouble0);
    }
}

int compareString1(void* a, void* b) {
    return strcmp(*(char**)a, *(char**)b);
}

int compareString0(void* a, void* b) {
    return -1 * strcmp(*(char**)a, *(char**)b);
}

void sortString(dynamic_array* darr, int param) {
    if (param == 1) {
        qsort(darr->list, darr->size, sizeof(char*), compareString1);
    }
    else {
        qsort(darr->list, darr->size, sizeof(char*), compareString0);
    }
}

dynamic_array* sort(dynamic_array* darr, int param1, int param2) {
    if (param2 == 1 || param2 == 0) {
        if (param1 == 0) {
            dynamic_array* sortedDouble = fragmentDouble(darr);
            sortDouble(sortedDouble, param2);
            //free(darr);
            return concatenation(sortedDouble, fragmentString(darr));
        }
        else if (param1 == 1) {
            dynamic_array* sortedString = fragmentString(darr);
            sortString(sortedString, param2);
            //free(darr);
            return concatenation(sortedString, fragmentDouble(darr));
        }
        else if (param1 == 2) {
            dynamic_array* sortedString = fragmentString(darr);
            dynamic_array* sortedDouble = fragmentDouble(darr);
            sortString(sortedString, param2);
            sortDouble(sortedDouble, param2);
            //free(darr);
            return concatenation(sortedString, sortedDouble);
        }
        else if (param1 == 3) {
            dynamic_array* sortedString = fragmentString(darr);
            dynamic_array* sortedDouble = fragmentDouble(darr);
            sortString(sortedString, param2);
            sortDouble(sortedDouble, param2);
            //free(darr);
            return concatenation(sortedDouble, sortedString);
        }
        else {
            printf("%s - - - Invalid Syntax - - - %s\n", RED, RESET);
        }
    }
    else {
        printf("%s - - - Invalid Syntax - - - %s\n", RED, RESET);
    }
}