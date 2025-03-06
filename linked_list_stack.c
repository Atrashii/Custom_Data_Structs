#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;

Node* create_Node(int data) {
	Node *new_node = (Node*)malloc(sizeof(Node));
	if(new_node == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return NULL;
	}
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}

void push(Node **head, int data) {
	Node *new_node = create_Node(data);
	if(new_node == NULL) {
		printf("Eingabe von Daten nicht möglich\n");
		return;
	}

	new_node->next = *head;
	*head = new_node;
}

int peek(Node **head) {
	if(*head == NULL) {
		return INT_MIN;
	}
	return (*head)->data;
}

int pop(Node **head) {
	if(*head == NULL) {
		fprintf(stderr, "Stack is empty\n");
		return INT_MIN;
	}
	Node *temp = *head;
	int data = temp->data;
	*head = temp->next;
	free(temp);
	return data;
}

void free_list(Node **head) {
	if(*head == NULL) {
		fprintf(stderr, "List already empty\n");
		return;
	}
	Node *current = *head;
	while(current != NULL) {
		Node *tmp = current;
		current = current->next;
		free(tmp);
	}
	*head = NULL;
}

int main(void) {
	Node* head = NULL;

	push(&head, 32);
	push(&head, 28);
	push(&head, 92);
	push(&head, 38);
	
	printf("Peek %d\n", peek(&head));
	printf("Pop: %d\n", pop(&head));
	printf("Pop: %d\n", pop(&head));
	printf("Peek %d\n", peek(&head));

	free_list(&head);
	return 0;
}
