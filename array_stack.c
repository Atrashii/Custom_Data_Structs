#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXSIZE 64

// size == -1 -> then stack is empty

void push(int stack[], int data, int* size) {
	(*size)++;
	stack[*size] = data;
}

int peek(int stack[], int* size) {
	return stack[*size];
}

int pop(int stack[], int* size) {
	if(*size == -1) {
		fprintf(stderr, "Underflow\n");
		return INT_MIN;
	}
	int tmp = stack[*size];
	(*size)--;
	return tmp;
}

int main(void) {
	int stack[MAXSIZE];
	int size = -1;

	push(stack, 1, &size);
	push(stack, 5, &size);
	push(stack, 9, &size);
	push(stack, 2, &size);
	push(stack, 8, &size);

	printf("Peek %d\n", peek(stack, &size));
	printf("Pop %d\n", pop(stack, &size));
	printf("Peek %d\n", peek(stack, &size));
	printf("Pop %d\n", pop(stack, &size));
	printf("Peek %d\n", peek(stack, &size));
}
	





