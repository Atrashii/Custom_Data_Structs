#include <stdio.h>
#include <stdlib.h>


typedef struct CLLNode {
	int data;
	struct CLLNode *next;
} CLLNode;

CLLNode* create_node(int data) {
	CLLNode *new_node = (CLLNode*)malloc(sizeof(CLLNode));

	if(new_node == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		free(new_node);
		return NULL;
	}

	new_node->next = NULL;
	new_node->data = data;
	return new_node;
}

	 
void insert_empty_list(CLLNode **tail, int data) {
	CLLNode *new_node = create_node(data);

	new_node->next = new_node;
	*tail = new_node;
}

void insert_beginning(CLLNode **tail, int data) {
	if(*tail == NULL) {
		fprintf(stderr, "List empty, insert node first\n");
		return;
	}
	CLLNode *new_node = create_node(data);

	new_node->next = (*tail)->next;
	(*tail)->next = new_node;
}

void insert_end(CLLNode **tail, int data) {
	if(*tail == NULL) {
		fprintf(stderr, "List empty!\n");
		return;
	}
	CLLNode *new_node = create_node(data);

	CLLNode *current = (*tail)->next;

	do {
		current = current->next;
	} while(current != (*tail)->next);

	new_node->next = current->next;
	current->next = new_node;
	*tail = new_node;
}



void print_content(CLLNode **tail) {
	if(*tail == NULL) {
		printf("List is empty!\n");
		return;
	}

	CLLNode *current = (*tail)->next;

	do {
		printf("%d ", current->data);
		current = current->next;
	} while(current != (*tail)->next);
	printf("\n");
}

void free_list(CLLNode **tail) {
	if(*tail == NULL) {
		return;
	}

	CLLNode *current = (*tail)->next;
	CLLNode *first = current;

	do {
		CLLNode *tmp = current;	
		current = current->next;
		free(tmp);
	} while(current != first);

	*tail = NULL;
}

int main(void) {
	CLLNode *tail = NULL;

	insert_empty_list(&tail, 43);

	insert_beginning(&tail, 58);
	
	print_content(&tail);

	free_list(&tail);
	return 0;
}
