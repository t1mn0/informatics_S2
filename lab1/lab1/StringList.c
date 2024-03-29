#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "ErrorHandling.h"



void concatenationString(List* list_1, List* list_2) {
    int size_1 = list_1->size;
    list_1->FieldInfo.resize(list_1, list_2->size);
    for (int i = size_1; i < list_1->size; i++) {
        float* q = list_2->FieldInfo.getElement(list_2, i - size_1);
        list_1->FieldInfo.setElement(list_1, i, q);
    }
}



char** initStringList(unsigned int size);
void resizeStringList(List* list, int delta);
void printStringList(List* list);
void addStringElement(List* list, char* valueP);
void setStringElement(List* list, unsigned int index, char* valueP);
char* getStringElement(List* list, unsigned int index);
void sortString(List* list, unsigned int param);
void mapString(List* list, char* (*func)(char*));
List* whereString(List* list, int (*func)(char*));



FI createStringFieldInfo() {
    FI string_fi = {
    .initList = initStringList,
    .resize = resizeStringList,
    .printList = printStringList,
    .addElement = addStringElement,
    .setElement = setStringElement,
    .getElement = getStringElement,
    .concatenation = concatenationString,
    .sort = sortString,
    .map = mapString,
    .where = whereString
    };
    return string_fi;
}



char** initStringList(unsigned int size) {
    char** array = (char**)malloc(sizeof(char*) * size);
    if (array == NULL) handleErrorCode(MEMORY_ALLOCARTION_ERROR);
    for (int i = 0; i < size; i++) {
        array[i] = "EMPTY!";
    }
    return array;
}

void setStringElement(List* list, unsigned int index, char* valueP) {
    if (index > list->size) handleErrorCode(ARRAY_INDEX_OUT_OF_BOUNDS_ERROR);
    ((char**)(list->array))[index] = valueP;
}

char* getStringElement(List* list, unsigned int index) {
    if (index > list->size) handleErrorCode(ARRAY_INDEX_OUT_OF_BOUNDS_ERROR);
    return ((char**)(list->array))[index];
}

void resizeStringList(List* list, int delta) {
    int size = list->size;
    list->size = size + delta;
    list->array = (char**)realloc(list->array, sizeof(char*) * (size + delta));
    if (list->array == NULL) handleErrorCode(MEMORY_ALLOCARTION_ERROR);
    if (delta > 0) {
        for (int i = size; i < size + delta; i++) {
            list->FieldInfo.setElement(list, i, " ");
        }
    }
}

void printStringList(List* list) {
    for (int i = 0; i < list->size; i++) {
        printf("%s\n", ((char**)(list->array))[i]);
    }
}

void addStringElement(List* list, char* valueP) {
    list->FieldInfo.resize(list, 1);
    list->FieldInfo.setElement(list, list->size - 1, valueP);
}

int compareString_1(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int compareString_2(const void* a, const void* b) {
    return -strcmp(*(const char**)a, *(const char**)b);
}

void sortString(List* list, unsigned int param) {
    if (param == 0) {
        qsort(list->array, list->size, list->element_size, compareString_1);
    }
    else if (param == 1) {
        qsort(list->array, list->size, list->element_size, compareString_2);
    }
}

void mapString(List* list, char* (*func)(char*)) {
    char* s;
    for (int i = 0; i < list->size; i++) {
        s = list->FieldInfo.getElement(list, i);
        list->FieldInfo.setElement(list, i, func(s));
    }
}

List* whereString(List* list, int (*func)(char*)) {
    List* new_list = createList(1, 8);
    int isFirst = 1;
    for (int i = 0; i < list->size; i++) {
        if (func(list->FieldInfo.getElement(list, i)) == 1) {
            if (isFirst) {
                new_list->FieldInfo.setElement(new_list, 0, list->FieldInfo.getElement(list, i));
                isFirst = 0;
            }
            else {
                new_list->FieldInfo.addElement(new_list, list->FieldInfo.getElement(list, i));
            }
        }
    }
    return new_list;
}
