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
        if (str[i] == 'w') {
            return 1;
        }
    }
    return 0;
}


int main() {
    printf("%sCreation list_1...%s\n", PURPLE, RESET);
    dynamic_array* darr1 = LIST.init();
    printf("%sCreation list_1...%s\n", PURPLE, RESET);
    dynamic_array* darr2 = LIST.init();

    LIST.addDouble(darr1, 3.1415);
    LIST.addString(darr1, "c++");
    LIST.addDouble(darr1, 12);
    LIST.addString(darr1, "github");
    LIST.addDouble(darr1, 10);
    LIST.addString(darr1, "auto");
    LIST.addDouble(darr1, 16);
    LIST.addString(darr1, "code");
    LIST.addDouble(darr1, 25.5);
    LIST.addString(darr1, "classic");
    LIST.addDouble(darr1, 0);
    LIST.addString(darr1, "snake");
    LIST.addDouble(darr1, -144);
    LIST.addString(darr1, "iron");
    LIST.addDouble(darr1, -1000);
    LIST.addString(darr1, "gitlab");
    LIST.addDouble(darr1, -0.001);
    LIST.addString(darr1, "long float");

    LIST.addDouble(darr2, 35981);
    LIST.addString(darr2, "world");
    LIST.addDouble(darr2, -43.43);
    LIST.addString(darr2, "start");
    LIST.addDouble(darr2, 0);
    LIST.addString(darr2, "qwerty");
    LIST.addString(darr2, "wasd");
    LIST.addString(darr2, "super");

    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("%slist_1:%s\n", PURPLE, RESET);
    LIST.printList(darr1);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("%slist_2:%s\n", PURPLE, RESET);
    LIST.printList(darr2);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");

    printf("%sSorting list_1... TypeSort: 0 / 0%s\n", PURPLE, RESET);
    darr1 = LIST.sort(darr1, 0, 0);
    printf("%sSorting list_2... TypeSort: 1 / 1%s\n", PURPLE, RESET);
    darr2 = LIST.sort(darr2, 1, 1);

    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("%slist_1:%s\n", PURPLE, RESET);
    LIST.printList(darr1);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("%slist_2:%s\n", PURPLE, RESET);
    LIST.printList(darr2);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");

    printf("%sMap of double of list_1...%s\n", PURPLE, RESET);
    LIST.mapDouble(testMapDoubleFunc, darr1);
    printf("%sMap of string of list_2...%s\n", PURPLE, RESET);
    LIST.mapString(testMapStringFunc, darr2);

    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("%slist_1:%s\n", PURPLE, RESET);
    LIST.printList(darr1);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("%slist_2:%s\n", PURPLE, RESET);
    LIST.printList(darr2);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");

    printf("%sWhere ('w' in the string) of list_2%s\n", PURPLE, RESET);
    darr2 = LIST.where(testWhereFunc, darr2);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("%slist_2:%s\n", PURPLE, RESET);
    LIST.printList(darr2);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");

    printf("%sConcatenation of list_1 and list_2%s\n", PURPLE, RESET);
    LIST.concatenation(darr1, darr2);

    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("%slist:%s\n", PURPLE, RESET);
    LIST.printList(darr1);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");

    printf("%sSorting list... TypeSort: 3 / 1%s\n", PURPLE, RESET);
    LIST.sort(darr1, 3, 1);

    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("%slist:%s\n", PURPLE, RESET);
    LIST.printList(darr1);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - \n");

    LIST.freeList(darr1, 0);
    LIST.freeList(darr2, 0);

    return 0;
}