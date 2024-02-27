#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET   "\033[0m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"

#define add(arg1, arg2) _Generic((arg2), double : addDouble, char* : addString)(arg);


typedef struct {
    void** array;
    int size;
    int capacity;
} dynamic_array;

typedef struct {
    void (*freeList)(dynamic_array*, int);
    dynamic_array* (*init)();
    void (*resize)(dynamic_array*);
    void (*addString)(dynamic_array*, char*);
    void (*addDouble)(dynamic_array*, double);
    void* (*get)(dynamic_array*, int);
    void (*set)(dynamic_array*, void*, int);
    void (*printList)(dynamic_array*);

    void (*concatenation)(dynamic_array*, dynamic_array*);
    void (*mapString)(char* (*func)(char*), dynamic_array*);
    void (*mapDouble)(double (*func)(double), dynamic_array*);
    dynamic_array* (*where)(int (*func)(char*), dynamic_array*);
    dynamic_array* (*sort)(dynamic_array*, int, int);
} list;


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
    free(darr->array);
    free(darr);
}

dynamic_array* init() {
    dynamic_array* darr = (dynamic_array*)malloc(sizeof(dynamic_array));
    if (darr == NULL) {
        freeList(darr, 1);
    }

    darr->size = 0;
    darr->capacity = 5;

    darr->array = (void**)malloc(darr->capacity * sizeof(void*));
    if (darr->array == NULL) {
        freeList(darr, 1);
    }

    return darr;
}

void resize(dynamic_array* darr) {
    darr->capacity += 5;
    darr->array = (void**)realloc(darr->array, darr->capacity * sizeof(void*));
    if (darr->array == NULL) {
        freeList(darr, 1);
    }
}

void addString(dynamic_array* darr, char* str) {
    if (darr->size == darr->capacity) {
        resize(darr);
    }
    darr->array[darr->size] = _strdup(str);
    if (darr->array[darr->size] == NULL) {
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
    darr->array[darr->size] = n_pointer;
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
    for (int i = 0; i < strlen(str); i++) {
        if ((isdigit(str[i]) == 0) && ((str[i]) != '.') && ((str[i]) != '-')) {
            return 0;
        }
    }
    return 1;
}

double getDouble(dynamic_array* darr, int index) {
    return atof((char*)darr->array[index]);
}

char* getString(dynamic_array* darr, int index) {
    return (char*)darr->array[index];
}

void* get(dynamic_array* darr, int index) {
    if (index > darr->size) {
        freeList(darr, 3);
    }
    else {
        void* res = darr->array[index];
        if (res == NULL) {
            freeList(darr, 4);
        }
        else {
            if (isDouble(darr->array[index]) == 1) {
                double result = getDouble(darr, index);
                return &result;
            }
            else {
                return getString(darr, index);
            }
        }
    }
}

void set(dynamic_array* darr, void* element, int index) {
    if (index > darr->size) {
        freeList(darr, 3);
    }
    else {
        if (darr->array[index] == NULL) {
            freeList(darr, 4);
        }
        else {
            darr->array[index] = element;
        }
    }
}

void printList(dynamic_array* darr) {
    if (darr == NULL) {
        freeList(darr, 4);
    }

    for (int i = 0; i < darr->size; i++) {
        if (darr->array[i] != NULL) {
            printf("%s\n", darr->array[i]);
        }
        else {
            freeList(darr, 4);
        }
    }
}



void concatenation(dynamic_array* darr1, dynamic_array* darr2) {
    for (int i = 0; i < darr2->size; i++) {
        addString(darr1, darr2->array[i]);
    }
}

void mapString(char* (*func)(char*), dynamic_array* darr) {
    for (int i = 0; i < darr->size; i++) {
        if (isString(darr->array[i]) == 1) {
            darr->array[i] = func(darr->array[i]);
        }
    }
}

void mapDouble(double (*func)(double), dynamic_array* darr) {
    for (int i = 0; i < darr->size; i++) {
        if (isString(darr->array[i]) == 0) {
            char* n_pointer = (char*)malloc(sizeof(char*));

            if (n_pointer == NULL) {
                freeList(darr, 1);
            }

            snprintf(n_pointer, sizeof n_pointer, "%lf", func(atof(darr->array[i])));
            darr->array[i] = n_pointer;
        }
    }
}

dynamic_array* where(int (*func)(char*), dynamic_array* darr) {
    dynamic_array* darrWhere = init();
    for (int i = 0; i < darr->size; i++) {
        if (func(darr->array[i]) == 1) {
            addString(darrWhere, darr->array[i]);
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
        qsort(darr->array, darr->size, sizeof(char*), compareDouble1);
    }
    else {
        qsort(darr->array, darr->size, sizeof(char*), compareDouble0);
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
        qsort(darr->array, darr->size, sizeof(char*), compareString1);
    }
    else {
        qsort(darr->array, darr->size, sizeof(char*), compareString0);
    }
}

dynamic_array* sort(dynamic_array* darr, int param1, int param2) {
    if (param2 == 1 || param2 == 0) {
        if (param1 == 0) {
            dynamic_array* sortedDouble = fragmentDouble(darr);
            sortDouble(sortedDouble, param2);
            //free(darr);
            concatenation(sortedDouble, fragmentString(darr));
            return sortedDouble;
        }
        else if (param1 == 1) {
            dynamic_array* sortedString = fragmentString(darr);
            sortString(sortedString, param2);
            //free(darr);
            concatenation(sortedString, fragmentDouble(darr));
            return sortedString;
        }
        else if (param1 == 2) {
            dynamic_array* sortedString = fragmentString(darr);
            dynamic_array* sortedDouble = fragmentDouble(darr);
            sortString(sortedString, param2);
            sortDouble(sortedDouble, param2);
            //free(darr);
            concatenation(sortedString, sortedDouble);
            return sortedString;
        }
        else if (param1 == 3) {
            dynamic_array* sortedString = fragmentString(darr);
            dynamic_array* sortedDouble = fragmentDouble(darr);
            sortString(sortedString, param2);
            sortDouble(sortedDouble, param2);
            //free(darr);
            concatenation(sortedDouble, sortedString);
            return sortedDouble;
        }
        else {
            printf("%s - - - Invalid Syntax - - - %s\n", RED, RESET);
        }
    }
    else {
        printf("%s - - - Invalid Syntax - - - %s\n", RED, RESET);
    }
}


list LIST = {
    .freeList = freeList,
    .init = init,
    .resize = resize,
    .addString = addString,
    .addDouble = addDouble,
    .set = set,
    .get = get,
    .printList = printList,
    .concatenation = concatenation,
    .mapString = mapString,
    .mapDouble = mapDouble,
    .where = where,
    .sort = sort
};