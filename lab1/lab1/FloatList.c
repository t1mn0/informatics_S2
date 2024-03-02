#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"



void concatenationFloat(List* list_1, List* list_2) {
    int size_1 = list_1->size;
    list_1->FieldInfo.resize(list_1, list_2->size);
    for (int i = size_1; i < list_1->size; i++) {
        float* q = list_2->FieldInfo.getElement(list_2, i - size_1);
        list_1->FieldInfo.setElement(list_1, i, q);
    }
}



FI createFloatFieldInfo();
float* initFloatList(unsigned int size);
void resizeFloatList(List* list, int delta);
void printFloatList(List* list);
void addFloatElement(List* list, float* valueP);
void setFloatElement(List* list, unsigned int index, float* valueP);
float* getFloatElement(List* list, unsigned int index);
void sortFloat(List* list, unsigned int param);
void mapFloat(List* list, float* (*func)(float*));
List* whereFloat(List* list, float* (*func)(float*));



FI createFloatFieldInfo() {
    FI float_fi = {
    .initList = initFloatList,
    .resize = resizeFloatList,
    .printList = printFloatList,
    .addElement = addFloatElement,
    .setElement = setFloatElement,
    .getElement = getFloatElement,
    .concatenation = concatenationFloat,
    .sort = sortFloat,
    .map = mapFloat,
    .where = whereFloat
    };
    return float_fi;
}



float* initFloatList(unsigned int size) {
    float* array = (float*)malloc(sizeof(float) * size);
    for (int i = 0; i < size; i++) {
        array[i] = 0.0;
    }
    return array;
}

void resizeFloatList(List* list, int delta) {
    int size = list->size;
    list->size = size + delta;
    list->array = (float*)realloc(list->array, sizeof(float) * (size + delta));
    if (delta > 0) {
        for (int i = size; i < size + delta; i++) {
            float zero = 0.0;
            list->FieldInfo.setElement(list, i, &zero);
        }
    }
}

void printFloatList(List* list) {
    for (int i = 0; i < list->size; i++) {
        printf("%f\n", ((float*)list->array)[i]);
    }
}

void addFloatElement(List* list, float* valueP) {
    list->FieldInfo.resize(list, 1);
    ((float*)(list->array))[list->size - 1] = *valueP;
}

void setFloatElement(List* list, unsigned int index, float* valueP) {
    ((float*)(list->array))[index] = *valueP;
}

float* getFloatElement(List* list, unsigned int index) {
    return &(((float*)list->array)[index]);
}

int compareFloat_1(float* arg1, float* arg2) {
    float num1 = *arg1;
    float num2 = *arg2;

    if (num1 < num2) {
        return -1;
    }
    else if (num1 > num2) {
        return 1;
    }
    else {
        return 0;
    }
}

int compareFloat_2(float* arg1, float* arg2) {
    return -compareFloat_1(arg1, arg2);
}

void sortFloat(List* list, unsigned int param) {
    if (param == 0) {
        qsort(list->array, list->size, list->element_size, compareFloat_1);
    }
    else if (param == 1) {
        qsort(list->array, list->size, list->element_size, compareFloat_2);
    }
}

void mapFloat(List* list, float* (*func)(float*)) {
    char* s;
    for (int i = 0; i < list->size; i++) {
        s = list->FieldInfo.getElement(list, i);
        s = func(s);
        list->FieldInfo.setElement(list, i, s);
    }
}

List* whereFloat(List* list, float* (*func)(float*)) {
    List* new_list = createList(1, 4);
    int isFirst = 1;
    for (int i = 0; i < list->size; i++) {
        float* v = list->FieldInfo.getElement(list, i);
        if (func(v) == 1) {
            if (isFirst == 1) {
                new_list->FieldInfo.setElement(new_list, 0, v);
                isFirst = 0;
            }
            else {
                new_list->FieldInfo.addElement(new_list, v);
            }
        }
    }
    return new_list;
}