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
    void (*concatenation)(List* list_1, List* list_2);
    void (*sort)(List* list, unsigned int param);
    void (*map)(List* list, void* (*func)(void*));
    List* (*where)(List* list, void* (*func)(void*));
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
void sortString(List* list, unsigned int param);
void mapString(List* list, char* (*func)(char*));
List* whereString(List* list, char* (*func)(char*));

FI createStringFieldInfo() {
    FI string_fi = {
    .initList = initStringList,
    .resize = resizeStringList,
    .printList = printStringList,
    .addElement = addStringElement,
    .setElement = setStringElement,
    .getElement = getStringElement,
    .concatenation = concatenation,
    .sort = sortString,
    .map = mapString,
    .where = whereString
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

int compareString_1(char* arg1, char* arg2) {
    return strcmp(arg1, arg2);
}

int compareString_2(char* arg1, char* arg2) {
    return -strcmp(arg1, arg2);
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
        s = func(s);
        list->FieldInfo.setElement(list, i, s);
    }
}

List* whereString(List* list, char* (*func)(char*)) {
    List* new_list = createList(1, 8);
    int isFirst = 1;
    for (int i = 0; i < list->size; i++) {
        if (func(list->FieldInfo.getElement(list, i)) == 1) {
            if (isFirst) {
                new_list->FieldInfo.setElement(new_list, 1, list->FieldInfo.getElement(list, i));
                isFirst = 0;
            }
            else {
                new_list->FieldInfo.addElement(new_list, list->FieldInfo.getElement(list, i));
            }
        }
    }
    return new_list;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

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
    .concatenation = concatenation,
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
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void concatenation(List* list_1, List* list_2) {
    int size_1 = list_1->size;
    list_1->FieldInfo.resize(list_1, list_2->size);
    for (int i = size_1; i < list_1->size; i++) {
        float* q = list_2->FieldInfo.getElement(list_2, i - size_1);
        list_1->FieldInfo.setElement(list_1, i, q);
    }

}