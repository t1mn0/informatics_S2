#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FloatList.h"
#include "StringList.h"
#include "ErrorHandling.h"

typedef struct FI FI;
typedef struct List List;

typedef struct FI {
    List* (*initList)(unsigned int size); // �������������� array
    void (*resize)(List* list, unsigned int delta); // �������� size �� delta
    void (*printList)(List* list); // ������� ���������� array �� �����
    void (*addElement)(List* list, void* valueP); // ��������� ������� � array
    void (*setElement)(List* list, unsigned int index, void* valueP); // ������������� ��������, �� ������� ��������� valueP, � array �� ������� index 
    void* (*getElement)(List* list, int index); // �������� ��������� �� ������� array �� ������� index
    void (*concatenation)(List* list_1, List* list_2);
    void (*sort)(List* list, unsigned int param);
    void (*map)(List* list, void* (*func)(void*));
    List* (*where)(List* list, int (*func)(void*));
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

List* createList(unsigned int size, unsigned int element_size) {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) handleErrorCode(MEMORY_ALLOCARTION_ERROR);
    list->element_size = element_size;
    list->size = size;
    list->FieldInfo = createFieldInfo(list);
    list->array = list->FieldInfo.initList(size);
    return list;
}