#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct FI FI;
typedef struct List List;
FI createFloatFieldInfo();
FI createStringFieldInfo();

typedef struct FI {
    List* (*initList)(unsigned int size); // Инициализирует array
    void (*resize)(List* list, unsigned int delta); // Изменяет size на delta
    void (*printList)(List* list); // Выводит содержимое array на экран
    void (*addElement)(List* list, void* valueP); // добавляет элемент в array
    void (*setElement)(List* list, unsigned int index, void* valueP); // устанавливает значение, на которое ссылается valueP, в array по индексу index 
    void* (*getElement)(List* list, int index); // получить указатель на элемент array по индексу index
    void (*concatenation)(List* list_1, List* list_2); // к list_1 пришивает list_2
} FI;

typedef struct List {
    void* array;
    int size;
    int element_size;
    FI FieldInfo;
} List;

FI createFieldInfo(List* list) {
    switch (list->element_size) {
    case 4: return createFloatFieldInfo();
    case 8: return createStringFieldInfo();
    default: break;
    }
}

List* createList(int size, unsigned int element_size) {
    List* list = (List*)malloc(sizeof(List));
    list->element_size = element_size;
    list->size = size;
    list->FieldInfo = createFieldInfo(list);
    list->array = list->FieldInfo.initList(size);
    return list;
}

void concatenation(List* list_1, List* list_2);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

char** initStringList(unsigned int size);
void resizeStringList(List* list, int delta);
void printStringList(List* list);
void addStringElement(List* list, char* valueP);
void setStringElement(List* list, unsigned int index, char* valueP);
char* getStringElement(List* list, unsigned int index);


FI createStringFieldInfo() {
    FI string_fi = {
    .initList = initStringList,
    .resize = resizeStringList,
    .printList = printStringList,
    .addElement = addStringElement,
    .setElement = setStringElement,
    .getElement = getStringElement,
    .concatenation = concatenation,
    };
    return string_fi;
}

char** initStringList(unsigned int size) {
    char** list = (char**)malloc(sizeof(char*) * size);
    for (int i = 0; i < size; i++) {
        list[i] = " ";
    }
    return list;
}

void setStringElement(List* list, unsigned int index, char* valueP) {
    ((char**)(list->array))[index] = valueP;
}

char* getStringElement(List* list, unsigned int index) {
    return ((char**)(list->array))[index];
}

void resizeStringList(List* list, int delta) {
    int size = list->size;
    list->size = size + delta;
    list->array = (char**)realloc(list->array, sizeof(char*) * (size + delta));
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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

float* initFloatList(unsigned int size);
void resizeFloatList(List* list, int delta);
void printFloatList(List* list);
void addFloatElement(List* list, float* valueP);
void setFloatElement(List* list, unsigned int index, float* valueP);
float* getFloatElement(List* list, unsigned int index);


FI createFloatFieldInfo() {
    FI float_fi = {
    .initList = initFloatList,
    .resize = resizeFloatList,
    .printList = printFloatList,
    .addElement = addFloatElement,
    .setElement = setFloatElement,
    .getElement = getFloatElement,
    .concatenation = concatenation,
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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void concatenation(List* list_1, List* list_2) {
    int size_1 = list_1->size;
    list_1->FieldInfo.resize(list_1, list_2->size);
    for (int i = size_1; i < list_1->size; i++) {
        float* q = list_2->FieldInfo.getElement(list_2, i - size_1);
        list_1->FieldInfo.setElement(list_1, i, q);
    }

}