#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 127

typedef struct SLL_Node {
	char letter;
	struct SLL_Node *next;
} Node;

Node *create_node(char let) {
	Node *new_node = (Node *)malloc(sizeof(Node));
	if(new_node == NULL) {
		fprintf(stderr, "Node memory allocation failed\n");
		return NULL;
	}
	new_node->letter = let;
	new_node->next = NULL;
	return new_node;
}


char peek(Node **head) {
	if(*head == NULL) {
		fprintf(stderr, "Nothing to peek, Stack is empty!\n");
		return '\0';
	}
	return (*head)->letter;
}

char pop(Node **head) {
	if(*head == NULL) {
		fprintf(stderr, "Stack is empty!\n");
		return '\0';
	}
	Node *tmp = *head;
	char data = tmp->letter;
	*head = tmp->next;
	free(tmp);
	return data;
}

void push(Node **head, char let) {
	Node *new_node = create_node(let);
	if(new_node == NULL) {
		fprintf(stderr, "Couldn't push %c onto stack!\n", let);
		return;
	}
	if(*head == NULL) {
		*head = new_node;
		return;
	}
	new_node->next = *head;
	*head = new_node;		
}

void free_list(Node **head) {
	Node *current = *head;
	if(*head == NULL) {
		fprintf(stderr, "Nothing to free, stack is empty\n");
		return;
	}
	while(current->next != NULL) {
		Node *tmp = current;
		current = current->next;
		free(tmp);
	}
	*head = NULL;
}




int main(void) {
	Node *head = NULL;
	char wort[MAXLEN];

	printf("Please enter a word to check if it is a palindrome:\n");
	scanf("%s", wort);
	int c = 0;
	while(wort[c] != '\0') {
		push(&head, wort[c]);
		c++;
	}
	
	for(int i = 0; i < strlen(wort) - 1; i++) {
		if(wort[i] != pop(&head)) {
			printf("String is not a palinedrome\n");
			break;
		}
	}
	printf("String %s is a palinedrome\n", wort);
	free_list(&head);
	return 0;
}

