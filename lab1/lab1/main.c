#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define RESET   "\033[0m"
#define PURPLE  "\033[0;35m"

double testMapDoubleFunc(double n) {
    return n * n;
}

char* testMapStringFunc(char* str) {
    return strcat(str, " by @autor");
}

int testWhereFunc(char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == 't') {
            return 1;
        }
    }
    return 0;
}


int main() {
    printf("%sCreation list_1...%s\n", PURPLE, RESET);
    dynamic_array* darr1 = newList();
    printf("%sCreation list_1...%s\n", PURPLE, RESET);
    dynamic_array* darr2 = newList();

    addDouble(darr1, 3.1415);
    addString(darr1, "code");
    addDouble(darr1, 12);
    addString(darr1, "github");
    addDouble(darr1, 10);
    addString(darr1, "auto");

    addDouble(darr2, 35981);
    addString(darr2, "world");
    addDouble(darr2, -43.43);
    addString(darr2, "start");
    addDouble(darr2, 0);
    addString(darr2, "task");


    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("%slist_1:%s\n", PURPLE, RESET);
    printList(darr1);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("%slist_2:%s\n", PURPLE, RESET);
    printList(darr2);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");

    printf("%sSorting list_1... TypeSort: 0 / 0%s\n", PURPLE, RESET);
    darr1 = sort(darr1, 0, 0);
    printf("%sSorting list_2... TypeSort: 1 / 1%s\n", PURPLE, RESET);
    darr2 = sort(darr2, 1, 1);

    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("%slist_1:%s\n", PURPLE, RESET);
    printList(darr1);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("%slist_2:%s\n", PURPLE, RESET);
    printList(darr2);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");

    printf("%sMap of double of list_1...%s\n", PURPLE, RESET);
    mapDouble(testMapDoubleFunc, darr1);
    printf("%sMap of string of list_2...%s\n", PURPLE, RESET);
    mapString(testMapStringFunc, darr2);

    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("%slist_1:%s\n", PURPLE, RESET);
    printList(darr1);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("%slist_2:%s\n", PURPLE, RESET);
    printList(darr2);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");

    printf("%sWhere ('t' in the string) of list_2%s\n", PURPLE, RESET);
    darr2 = where(testWhereFunc, darr2);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("%slist_2:%s\n", PURPLE, RESET);
    printList(darr2);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");

    printf("%sConcatenation of list_1 and list_2\n", PURPLE, RESET);
    dynamic_array* darr = concatenation(darr1, darr2);

    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("%slist:%s\n", PURPLE, RESET);
    printList(darr);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");

    printf("%sSorting list... TypeSort: 3 / 1%s\n", PURPLE, RESET);
    darr = sort(darr, 3, 1);

    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("%slist:%s\n", PURPLE, RESET);
    printList(darr);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");

    freeList(darr1, 0);
    freeList(darr2, 0);
    freeList(darr, 0);

    return 0;
}