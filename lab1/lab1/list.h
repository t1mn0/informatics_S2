#pragma once
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
} FI;

typedef struct List {
    void* array;
    int size;
    int element_size;
    FI FieldInfo;
} List;

List* createList(int size, unsigned int element_size);