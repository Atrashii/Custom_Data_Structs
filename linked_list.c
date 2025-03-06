#include <stdio.h>
#include <stdlib.h>


// Definition for the struct of a single linked list
typedef struct single_linked_list {
	int data;
	struct single_linked_list *next;
} SLLNode;

// Definition for the struct of a double linked list
typedef struct double_linked_list {
	int data;
	struct double_linked_list *next, *prev;
} DLLNode;

// insert a struct at the beginning of a single linked list
void SLL_insert_at_beginning(SLLNode **head, int data){
	SLLNode *new_node = (SLLNode*)malloc(sizeof(SLLNode));

	if (new_node == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		free(new_node);
		return;
	}

	new_node->data = data;
	new_node->next = *head;
	*head = new_node;
}


// insert a struct at the beginning of a double linked list
void DLL_insert_at_beginning(DLLNode **head, int data){
	DLLNode *new_node = (DLLNode*)malloc(sizeof(DLLNode));

	if (new_node == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
	}
	new_node->data = data;
	new_node->next = *head;
	new_node->prev = *head;
	*head = new_node;
}

void SLL_insert_at_end(SLLNode **head, int data) {
	SLLNode *new_node = (SLLNode*)malloc(sizeof(SLLNode));

	if(new_node == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
	}
	new_node->data = data;
	
	SLLNode *current = *head;
	while(current != NULL) {
		current = current->next;
	}
	current->next = new_node;
	new_node->next = NULL;
}

void DLL_insert_at_end(DLLNode **head, int data) {
	DLLNode *new_node = (DLLNode*)malloc(sizeof(DLLNode));

	if(new_node == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
	}
	new_node->data = data;
	
	DLLNode *current = *head;
	while(current != NULL) {
		current = current->next;
	}
	new_node->next = NULL;
	new_node->prev = current;
}

void SLL_insert_at_place(SLLNode **head, int data, int place) {
	SLLNode *new_node = (SLLNode*)malloc(sizeof(SLLNode));

	if(new_node == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
	}

	new_node->data = data;

	SLLNode *current = *head;

	while(current != NULL && current->data != place) {
		current = current->next;
	}

	current->next = new_node;
}

void DLL_insert_at_place(DLLNode **head, int data, int place) {
	DLLNode *new_node = (DLLNode*)malloc(sizeof(DLLNode));

	if(new_node == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
	}

	new_node->data = data;

	DLLNode *current = *head;

	while(current != NULL && current->data != place) {
		current = current->next;
	}
	if(current == NULL) {
		fprintf(stderr, "Place not found\n");
		free(new_node);
		return;
	}


	new_node->next = current->next;
	new_node->prev = current;

	if(current->next !=NULL){
		current->next->prev = new_node;
	}

	current->next = new_node;
}

void print_SLL(SLLNode **head){
	SLLNode *current = *head;
	while(current != NULL){
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}

	
void print_forward_DLL(DLLNode **head){
	DLLNode *current = *head;
	while(current != NULL){
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}

void print_backward_DLL(DLLNode **tail){
	DLLNode *current = *tail;
	while(current != NULL){
		printf("%d ", current->data);
		current = current->prev;
	}
	printf("\n");
}

void free_SLL(SLLNode **head) {
	SLLNode *current = *head;
	while(current != NULL){
		SLLNode *tmp = current;
		current = current->next;
		free(tmp);
	}
	*head = NULL;
}

void free_DLL(DLLNode **head) {
	DLLNode *current = *head;
	while(current != NULL){
		DLLNode *tmp = current;
		current = current->next;
		free(tmp);
	}
	*head = NULL;
}

int main(void) {
	SLLNode *SLLhead = NULL; 
	DLLNode *DLLhead = NULL;


	free_SLL(&SLLhead);
	free_DLL(&DLLhead);
	return 0;
}
