#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "List.h"
#include "ErrorHandling.h"

void testAll() {
	int size_1 = 3;
	unsigned int element_size_1 = 4;
	List* list_1 = createList(size_1, element_size_1);

	assert(list_1 != NULL);
	assert(list_1->size == size_1);
	assert(list_1->element_size == element_size_1);

	float v1 = 0.001;
	float v2 = -999.999;
	float v3 = 606.06;
	float v4 = -51541353;
	float v5 = 3.1415161718;
	list_1->FieldInfo.setElement(list_1, 0, &v1);
	list_1->FieldInfo.setElement(list_1, 1, &v2);
	list_1->FieldInfo.setElement(list_1, 2, &v3);
	list_1->FieldInfo.addElement(list_1, &v4);
	list_1->FieldInfo.addElement(list_1, &v5);
	float* _v1 = list_1->FieldInfo.getElement(list_1, 0);
	float* _v2 = list_1->FieldInfo.getElement(list_1, 1);
	float* _v3 = list_1->FieldInfo.getElement(list_1, 2);
	float* _v4 = list_1->FieldInfo.getElement(list_1, 3);
	float* _v5 = list_1->FieldInfo.getElement(list_1, 4);

	assert(v1 == *_v1);
	assert(v2 == *_v2);
	assert(v3 == *_v3);
	assert(v4 == *_v4);
	assert(v5 == *_v5);

	free(list_1);
}