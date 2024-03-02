#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

float* MAP(float* aPointer) {
	float a = *aPointer;
	a = 0;
	return &a;
}

int WHERE(float* aPointer) {
	float a = *aPointer;
	if (a <= 2) {
		return 1;
	}
	else return -1;
}

int main() {
	float n1, n2, n3, n4, n5, n6, n7, n8, n9, n10;
	n1 = 3.1;
	n2 = 23.1;
	n3 = 0.001;
	n4 = -21.44;
	n5 = -17.9090;
	n6 = 232323.0;
	n7 = 5;
	n8 = -132.132;
	n9 = 999.999;
	n10 = 1;
	List* list1 = createList(1, 4);
	List* list2 = createList(1, 4);
	list1->FieldInfo.setElement(list1, 0, &n1);
	list1->FieldInfo.addElement(list1, &n2);
	list1->FieldInfo.addElement(list1, &n3);
	list1->FieldInfo.addElement(list1, &n4);
	list1->FieldInfo.addElement(list1, &n5);
	list2->FieldInfo.setElement(list2, 0, &n6);
	list2->FieldInfo.addElement(list2, &n7);
	list2->FieldInfo.addElement(list2, &n8);
	list2->FieldInfo.addElement(list2, &n9);
	list2->FieldInfo.addElement(list2, &n10);
	list1->FieldInfo.printList(list1);
	list2->FieldInfo.printList(list2);
	printf("- - - - -\n");
	list1->FieldInfo.concatenation(list1, list2);
	list1->FieldInfo.printList(list1);
	printf("- - - - -\n");
	list1->FieldInfo.sort(list1, 0);
	list1->FieldInfo.printList(list1);
	printf("- - - - -\n");
	List* Y = list1->FieldInfo.where(list1, WHERE);
	Y->FieldInfo.printList(Y);
	printf("- - - - -\n");
}