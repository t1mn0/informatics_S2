#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <errno.h>
#include <limits.h>

#include "List.h"
#include "ErrorHandling.h"

#define EXIT "exit\n"
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define GREEN "\033[1;32m"
#define LINE "============================================================================================================================================================\n"
#define LANE "------------------------------------------------------------------------------------------------------------------------------------------------------------\n"



typedef struct Variable {
	char* name;
	List* listPointer;
} Variable;

Variable* createVar(char* name, unsigned int size, unsigned int element_size) {
	Variable* var = (Variable*)malloc(sizeof(Variable));
	if (var == NULL) handleErrorCode(MEMORY_ALLOCARTION_ERROR);
	var->name = (char*)malloc(strlen(name) + 1);
	strcpy(var->name, name);
	List* list = createList(size, element_size);
	var->listPointer = list;
	return var;
}

Variable vars[5];
int lastIndex = 0;


void menu();
void run();
void create_list();
void print_state();
void print_list();
void get_element();
void set_element();
void add_element();
void cut_list();
void sort_list();
void concatenate();
void map();
void where();



void menu() {
	printf("%s", LINE);
	printf("%80s", "MENU\n");
	printf("%s", LINE);
	printf("%75s%s%s", GREEN, "Available Commands:\n", RESET);
	printf("> %smenu%s\n", GREEN, RESET);
	printf("> %screate_list%s\n", GREEN, RESET);
	printf("> %sprint_state%s\n", GREEN, RESET);
	printf("> %sprint_list%s\n", GREEN, RESET);
	printf("> %sget_element%s\n", GREEN, RESET);
	printf("> %sset_element%s\n", GREEN, RESET);
	printf("> %sadd_element%s\n", GREEN, RESET);
	printf("> %scut_list%s\n", GREEN, RESET);
	printf("> %ssort_list%s\n", GREEN, RESET);
	printf("> %sconcatenate%s\n", GREEN, RESET);
	printf("> %smap%s\n", GREEN, RESET);
	printf("> %swhere%s\n\n", GREEN, RESET);
	printf("%s", LINE);
}


void run() {
	menu();
	char command[64];
	while (1) {
		printf(">>> ");
		fgets(command, sizeof(command), stdin);
		if (strcmp(command, EXIT) == 0) {
			exit(0);
		}
		else if (strcmp(command, "create_list\n") == 0) {
			create_list();
		}
		else if (strcmp(command, "print_state\n") == 0) {
			print_state();
		}
		else if (strcmp(command, "print_list\n") == 0) {
			print_list();
		}
		else if (strcmp(command, "get_element\n") == 0) {
			get_element();
		}
		else if (strcmp(command, "set_element\n") == 0) {
			set_element();
		}
		else if (strcmp(command, "add_element\n") == 0) {
			add_element();
		}
		else if (strcmp(command, "cut_list\n") == 0) {
			cut_list();
		}
		else if (strcmp(command, "sort_list\n") == 0) {
			sort_list();
		}
		else if (strcmp(command, "concatenate\n") == 0) {
			concatenate();
		}
		else if (strcmp(command, "map\n") == 0) {
			map();
		}
		else if (strcmp(command, "where\n") == 0) {
			where();
		}
		else if (strcmp(command, "menu\n") == 0) {
			menu();
		}
		else {
			printf("%s", command);
		}
	}
}



int isValidNameOfVar(char name[37]) {
	for (int i = 0; i < 12; i++) {
		if (name[i] == '\0' || name[i] == '\n') {
			return 1;
		}
		if (isalpha(name[i]) == 0 && name[i] != '_') {
			return 0;
		}
	}
	return 1;
}

int isNewName(char name[13]){
	for (int i = 0; i < lastIndex; i++) {
		if (strcmp(vars[i].name, name) == 0) {
			return 0;
		}
	}
	return 1;
}

int isValidSize(char* size) {
	char* endptr;
	size[strcspn(size, "\n")] = 0;
	size[strcspn(size, "\0")] = 0;

	long num = strtol(size, &endptr, 10);

	if (*endptr == '\0' && num >= INT_MIN && num <= INT_MAX) {
		return 1;
	}
	else {
		return 0;
	}
}

int isValidIndex(int i, char* index) {
	char* endptr;
	index[strcspn(index, "\n")] = 0;
	index[strcspn(index, "\0")] = 0;

	long num = strtol(index, &endptr, 10);

	if (*endptr == '\0')
		if (num >= 0 && num < vars[i].listPointer->size) {
		return 1;
	}
	else {
		return 0;
	}
}

int typeOfInputElement(char element[33]) {
	char* endptr;
	element[strcspn(element, "\n")] = 0;
	element[strcspn(element, "\0")] = 0;
	strtof(element, &endptr);

	if (*endptr == '\0') {
		return 1; // Строка представима как число float
	}
	else {
		return 0; // Строка не представима как число float
	}
}

void create_list() {
	if (lastIndex > 5) {
		printf("");
	}
	while (1) {
		char name[36];
		char varName[13];
		printf("%sInput name of new list (read max 12 characters, (Aa-Zz and '_')):%s ", GREEN, RESET);
		fgets(name, sizeof(name), stdin);
		if (isValidNameOfVar(name) == 1) {
			name[strcspn(name, "\n")] = 0;
			strncpy(varName, name, 12);
			varName[12] = '\0';
			if (isNewName(varName) == 1) {
				

				printf("%sInput size of new list (integer number 0-256):%s ", GREEN, RESET);
				char size[257];
				int varSize;
				fgets(size, sizeof(size), stdin);
				size[strcspn(size, "\n")] = 0;
				if (isValidSize(size) == 1) {
					varSize = atoi(size);

					Variable* var = (Variable*)malloc(sizeof(Variable));
					int isFloat = 0;
					for (int i = 0; i < varSize; i++){
						char element[33];
						printf("\n%sInput %s%s[%d]%s:%s", GREEN, RESET, varName, i, GREEN, RESET);
						fgets(element, sizeof(element), stdin);
						if (i == 0) {
							if (typeOfInputElement(element) == 1) {
								char* endptr;
								float e = strtof(element, &endptr);
								var = createVar(varName, varSize, 4);
								var->listPointer->FieldInfo.setElement(var->listPointer, i, &e);
								isFloat = 1;
								vars[lastIndex] = *var;
								lastIndex++;
							}
							else {
								char* e = (char*)malloc(sizeof(char*));
								strcpy(e, element);
								var = createVar(varName, varSize, 8);
								var->listPointer->FieldInfo.setElement(var->listPointer, i, e);
								vars[lastIndex] = *var;
								lastIndex++;
							}
						}
						else {
							if (typeOfInputElement(element) == 1 && isFloat == 1) {
								char* endptr;
								float e = strtof(element, &endptr);
								var->listPointer->FieldInfo.setElement(var->listPointer, i, &e);
							}
							else if(typeOfInputElement(element) == 0 && isFloat == 0) {
								char* e = (char*)malloc(sizeof(char*));
								strcpy(e, element);
								var->listPointer->FieldInfo.setElement(var->listPointer, i, e);
							}
							else {
								i--;
								handleErrorCode(TRY_AGAIN);
								continue;
							}
						}
					}
					printf("\n");
				}
				else {
					printf("%sINVALID_INPUT_ERROR\n%s", RED, RESET);
					printf("%sTRY AGAIN\n%s", RED, RESET);
					continue;
				}
				break;
			}
			else {
				printf("%sTHIS NAME HAS BEEN DECLARED\n%s", RED, RESET);
				continue;
			}
		}
		else {
			printf("%sINVALID_INPUT_ERROR\n%s", RED, RESET);
			printf("%sTRY AGAIN\n%s", RED, RESET);
		}
	}
}



void print_state() {
	printf("%s%85s%s", GREEN, "Memory status:\n", RESET);
	printf("%s", LANE);
	for (int i = 0; i < 5; i++) {
		printf("|%15d%15s", i, "|");
	}
	printf("\n%s", LANE);
	for (int i = 0; i < 5; i++) {
		if (i < lastIndex) {
			printf("|name: %-12s%12s", vars[i].name, "|");
		}
		else {
			printf("|name: %-12s%12s", "NONE", "|");
		}
	}
	printf("\n%s", LANE);
	for (int i = 0; i < 5; i++) {
		if (i < lastIndex) {
			printf("|size:%5d%20s", vars[i].listPointer->size, "|");
		}
		else {
			printf("|size:%5s%20s", "NONE", "|");
		}
	}
	printf("\n%s", LANE);
	for (int i = 0; i < 5; i++) {
		if (i < lastIndex) {
			if (vars[i].listPointer->element_size == 4) {
				printf("|type: float%19s", "|");
			}
			else{
				printf("|type: string%18s", "|");
			}
		}
		else {
			printf("|type: NONE%20s", "|");
		}
	}
	printf("\n%s", LANE);
}



int select_list() {
	if (lastIndex == 0) return -1;
	print_state();
	while (1) {
		char name[36];
		printf("\n%sSelect an array (input a name) :%s ", GREEN, RESET);
		fgets(name, sizeof(name), stdin);
		name[strcspn(name, "\n")] = 0;
		name[strcspn(name, "\0")] = 0;
		for (int i = 0; i < lastIndex; i++) {
			if (strcmp(vars[i].name, name) == 0) {
				return i;
			}
		}
		handleErrorCode(NO_ARRAY);
	}
}

void print_list(){
	int i = select_list();
	if (i < 0) {
		handleErrorCode(NO_ARRAY);
	}
	else {
		printf("\n");
		vars[i].listPointer->FieldInfo.printList(vars[i].listPointer);
	}
	printf("\n%s", LINE);
}

void get_element() {
	int i = select_list();
	if (i < 0) {
		handleErrorCode(NO_ARRAY);
	}
	else {
		while (1) {
			printf("\n");
			printf("%sInput index of that list:%s ", GREEN, RESET);
			char index[33];
			int j;
			fgets(index, sizeof(index), stdin);
			index[strcspn(index, "\n")] = 0;
			index[strcspn(index, "\0")] = 0;
			if (isValidIndex(i, index) == 1) {
				j = atoi(index);
				if (vars[i].listPointer->element_size == 4) {
					float* element = vars[i].listPointer->FieldInfo.getElement(vars[i].listPointer, j);
					printf("%s[%d] = %f\n", vars[i].name, j, *element);
				}
				else{
					char* element = vars[i].listPointer->FieldInfo.getElement(vars[i].listPointer, j);
					printf("%s[%d] = %s\n", vars[i].name, j, element);
				}
				break;
			}
			else {
				handleErrorCode(ARRAY_INDEX_OUT_OF_BOUNDS_ERROR);
			}
		}
	}
	printf("\n%s", LINE);
}

void set_element() {
	int i = select_list();
	if (i < 0) {
		handleErrorCode(NO_ARRAY);
	}
	else {
		while (1) {
			printf("\n");
			printf("%sInput index of that list:%s ", GREEN, RESET);
			char index[33];
			int j;
			fgets(index, sizeof(index), stdin);
			index[strcspn(index, "\n")] = 0;
			index[strcspn(index, "\0")] = 0;
			if (isValidIndex(i, index) == 1) {
				j = atoi(index);
				if (vars[i].listPointer->element_size == 4) {
					printf("%sInput value you want to set:%s ", GREEN, RESET);
					char element[65];
					fgets(element, sizeof(element), stdin);
					if (typeOfInputElement(element) == 1) {
						char* endptr;
						float e = strtof(element, &endptr);
						vars[i].listPointer->FieldInfo.setElement(vars[i].listPointer, j, &e);
					}
					else {
						handleErrorCode(INPUT_TYPE_ERROR);
						continue;
					}
				}
				else {
					printf("%sInput value you want to set:%s ", GREEN, RESET);
					char element[65];
					fgets(element, sizeof(element), stdin);
					char* e = (char*)malloc(sizeof(char*));
					element[strcspn(element, "\n")] = 0;
					element[strcspn(element, "\0")] = 0;
					strcpy(e, element);
					if (typeOfInputElement(element) == 0) {
						vars[i].listPointer->FieldInfo.setElement(vars[i].listPointer, j, e);
					}
					else {
						handleErrorCode(INPUT_TYPE_ERROR);
						continue;
					}
				}
				break;
			}
			else {
				handleErrorCode(ARRAY_INDEX_OUT_OF_BOUNDS_ERROR);
				continue;
			}
		}
	}
	printf("\n%s", LINE);
}

void add_element() {
	int i = select_list();
	if (i < 0) {
		handleErrorCode(NO_ARRAY);
	}
	else {
		while (1) {
			printf("\n");
			if (vars[i].listPointer->element_size == 4) {
				printf("%sInput value you want to add:%s ", GREEN, RESET);
				char element[65];
				fgets(element, sizeof(element), stdin);
				if (typeOfInputElement(element) == 1) {
					char* endptr;
					float e = strtof(element, &endptr);
					vars[i].listPointer->FieldInfo.addElement(vars[i].listPointer, &e);
				}
				else {
					handleErrorCode(INPUT_TYPE_ERROR);
					continue;
				}
			}
			else {
				printf("%sInput value you want to add:%s ", GREEN, RESET);
				char element[65];
				fgets(element, sizeof(element), stdin);
				char* e = (char*)malloc(sizeof(char*));
				element[strcspn(element, "\n")] = 0;
				element[strcspn(element, "\0")] = 0;
				strcpy(e, element);
				if (typeOfInputElement(element) == 0) {
					vars[i].listPointer->FieldInfo.addElement(vars[i].listPointer, e);
				}
				else {
					handleErrorCode(INPUT_TYPE_ERROR);
					continue;
				}
			}
			break;
		}
	}
	printf("\n%s", LINE);
}

void cut_list() {
	int i = select_list();
	if (i < 0) {
		handleErrorCode(NO_ARRAY);
	}
	else {
		while (1) {
			printf("\n");
			printf("%sInput new size (will take the first elements):%s ", GREEN, RESET);
			char index[33];
			int j;
			fgets(index, sizeof(index), stdin);
			index[strcspn(index, "\n")] = 0;
			index[strcspn(index, "\0")] = 0;
			if (isValidIndex(i, index) == 1) {
				j = atoi(index);
				int delta = j - vars[i].listPointer->size;
				vars[i].listPointer->FieldInfo.resize(vars[i].listPointer, delta);
				break;
			}
			else {
				handleErrorCode(ARRAY_INDEX_OUT_OF_BOUNDS_ERROR);
				continue;
			}
		}
	}
	printf("\n%s", LINE);
}



void sort_list() {
	int i = select_list();
	if (i < 0) {
		handleErrorCode(NO_ARRAY);
	}
	else {
		while (1) {
			printf("\n");
			printf("%sInput type of sort: increasing or decreasing [i / d]%s ", GREEN, RESET);
			char c[2];
			fgets(c, sizeof(c), stdin);
			if (strcmp(c, "d") == 0) {
				vars[i].listPointer->FieldInfo.sort(vars[i].listPointer, 1);
			}
			else if (strcmp(c, "i") == 0) {
				vars[i].listPointer->FieldInfo.sort(vars[i].listPointer, 0);
			}
			else {
				handleErrorCode(INPUT_TYPE_ERROR);
				continue;
			}
			break;
		}
	}
	printf("\n%s", LINE);
}

void concatenate() {
	printf("%sNOW YOU SELECT THE ARRAY TO WHICH THE FOLLOWING ARRAY WILL BE SELECTED\n%s", YELLOW, RESET);
	int i1 = select_list();
	if (i1 < 0) {
		handleErrorCode(NO_ARRAY);
		return;
	}
	printf("%sNOW YOU ARE NOW SELECT AN ARRAY THAT YOU WILL ADD TO THE ONE YOU HAVE ALREADY SELECTED\n%s", YELLOW, RESET);
	int i2 = select_list();
	if (i2 < 0) {
		handleErrorCode(NO_ARRAY);
		return;
	}
	while (1) {
		if (vars[i1].listPointer->element_size == vars[i2].listPointer->element_size) {
			vars[i1].listPointer->FieldInfo.concatenation(vars[i1].listPointer, vars[i2].listPointer);
			break;
		}
		else {
			handleErrorCode(INPUT_TYPE_ERROR);
			continue;
		}
	}
}

float exampleMapF(float* b) {
	return *b * *b;
}

char* exampleMapS(char* b) {
	strcat(b, " by: John");
	return b;
}

void map() {
	int i = select_list();
	if (i < 0) {
		handleErrorCode(NO_ARRAY);
	}
	else {
		if (vars[i].listPointer->element_size == 4) {
			vars[i].listPointer->FieldInfo.map(vars[i].listPointer, *exampleMapF);
		}
		else {
			vars[i].listPointer->FieldInfo.map(vars[i].listPointer, *exampleMapS);
		}
	}
	printf("\n%s", LINE);
}



int exampleWhereF(float* b) {
	if ((*b) > 0) return 1;
	return 0;
}

int exampleWhereS(char* b) {
	if ((b[0] == 'E') || (b[0] == 'e') || (b[0] == 'Y') || (b[0] == 'y') || (b[0] == 'U') || 
		(b[0] == 'U') || (b[0] == 'O') || (b[0] == 'o') || (b[0] == 'A') || (b[0] == 'a')) return 1;
	return 0;
}

void where() {
	int i = select_list();
	if (i < 0) {
		handleErrorCode(NO_ARRAY);
	}
	else {
		if (vars[i].listPointer->element_size == 4) {
			vars[i].listPointer = vars[i].listPointer->FieldInfo.where(vars[i].listPointer, *exampleWhereF);
		}
		else {
			vars[i].listPointer = vars[i].listPointer->FieldInfo.where(vars[i].listPointer, *exampleWhereS);
		}
	}
	printf("\n%s", LINE);
}