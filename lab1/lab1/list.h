#pragma once

#ifndef List_H
#define List_H

typedef struct FI FI;
typedef struct List List;

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

List* createList(int size, unsigned int element_size);

#endif List_H