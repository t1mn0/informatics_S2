#pragma once

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
    void (*printList)(dynamic_array*);

    void (*concatenation)(dynamic_array*, dynamic_array*);
    void (*mapString)(char* (*func)(char*), dynamic_array*);
    void (*mapDouble)(double (*func)(double), dynamic_array*);
    dynamic_array* (*where)(int (*func)(char*), dynamic_array*);
    dynamic_array* (*sort)(dynamic_array*, int, int);
} list;

/*void freeList(dynamic_array*, int);
dynamic_array* init();
void resize(dynamic_array*);
void addString(dynamic_array*, char*);
void addDouble(dynamic_array*, double);
int isString(char*);
int isDouble(char*);
void printList(dynamic_array*);

void concatenation(dynamic_array*, dynamic_array*);
void mapString(char* (*func)(char*), dynamic_array*);
void mapDouble(double (*func)(double), dynamic_array*);
dynamic_array* where(int (*func)(char*), dynamic_array*);
dynamic_array* sort(dynamic_array*, int param1, int param2);
dynamic_array* fragmentString(dynamic_array* darr);
dynamic_array* fragmentDouble(dynamic_array* darr);
int compareDouble1(void* a, void* b);
int compareDouble0(void* a, void* b);
int compareString1(void* a, void* b);
int compareString0(void* a, void* b);
void sortString(dynamic_array* darr, int param);
void sortDouble(dynamic_array* darr, int param);
*/

list LIST;