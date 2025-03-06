#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;

typedef struct Queue {
	size_t size;
	Node* front;
	Node* rear;
} Queue;

void init_queue(Queue *queue) {
	queue->size = 0;
	queue->front = NULL;
	queue->rear = NULL;
}

Node* create_node(int data) {
	Node *new_node = (Node*)malloc(sizeof(Node));
	if(new_node == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return NULL;
	}
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}

int dequeue(Queue *queue) {
	if(queue->front == NULL) {
		fprintf(stderr, "Queue is empty\n");
		return INT_MIN;
	}
	Node *tmp = queue->front;
	int value = tmp->data;
	queue->front = queue->front->next;
	if(queue->front == NULL) {
		queue->rear = NULL;
	}
	free(tmp);
	queue->size--;
	return value;
}

void enqueue(Queue *queue, int data) {
	Node *new_node = create_node(data);
	if(new_node == NULL) {
		fprintf(stderr, "Enqueue failed!\n");
		return;
	}
	if(queue->rear == NULL) {
		queue->front = queue->rear = new_node;
	}
	else {
		queue->rear->next = new_node;
		queue->rear = new_node;
	}
	queue->size++;
}

int peek(Queue *queue) {
	if(queue->front != NULL) {
		return queue->front->data;
	}
	return INT_MIN;
}

int rear(Queue *queue) {
	if(queue->rear != NULL) {
		return queue->rear->data;
	}
	return INT_MIN;
}

void free_queue(Queue *queue) {
	Node *current = queue->front;
	while(current != NULL){
		Node* tmp = current;
		current = current->next;
		free(tmp);
	}
	queue->front = NULL;
	queue->rear = NULL;
	queue->size = 0;
}




int main(void) {
	Queue queue;
	init_queue(&queue);

	enqueue(&queue, 32);
	printf("Peek: %d\n", peek(&queue));
	enqueue(&queue, 91);
	enqueue(&queue, 82);
	enqueue(&queue, 52);
	printf("Rear: %d\n", rear(&queue));
	enqueue(&queue, 19);

	printf("Peek: %d\n", peek(&queue));

	printf("Dequeue: %d\n", dequeue(&queue));
	printf("Dequeue: %d\n", dequeue(&queue));
	printf("Rear: %d\n", rear(&queue));

	free_queue(&queue);
	return 0;
}
