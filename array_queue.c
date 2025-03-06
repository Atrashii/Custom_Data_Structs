#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAXSIZE 64

typedef struct {
	int data[MAXSIZE];
	int front;
	int rear;
	int size;
} Queue;

void init_queue(Queue *queue) {
	queue->size = 0;
	queue->front = 0;
	queue->rear = 0;
}

bool isFull(Queue *queue) {
	return (queue->size == MAXSIZE);
}

bool isEmpty(Queue *queue) {
	return (queue->size == 0);
}

void enqueue(Queue *queue, int data) {
	if(isFull(queue)) {
		fprintf(stderr, "Queue full\n");
		return;
	}
	queue->size++;	
	queue->data[queue->rear] = data;
	queue->rear = (queue->rear + 1) % MAXSIZE;
}


int dequeue(Queue *queue) {
	if(!(isEmpty(queue))) {
		int tmp = queue->data[queue->front];
		queue->front = (queue->front + 1) % MAXSIZE;
		queue->size--;
		return tmp;
	}
	return INT_MIN;
}

int peek(Queue *queue) {
	if(!(isEmpty(queue))) {
		return queue->data[queue->front];
	}
	return INT_MIN;
}

int rear(Queue *queue) {
	if(!(isEmpty(queue))) {
		return queue->data[queue->rear];
	}
	return INT_MIN;
}

int main(void) {
	Queue queue;
	init_queue(&queue);

	enqueue(&queue, 49);
	enqueue(&queue, 43);
	enqueue(&queue, 32);
	enqueue(&queue, 9);
	enqueue(&queue, 2);

	printf("Peek: %d\n", peek(&queue));
	printf("Rear: %d\n", rear(&queue));

	printf("Dequeue: %d\n", dequeue(&queue));

	printf("Peek: %d\n", peek(&queue));
	printf("Rear: %d\n", rear(&queue));

	printf("Dequeue: %d\n", dequeue(&queue));

	printf("Peek: %d\n", peek(&queue));
	printf("Rear: %d\n", rear(&queue));
	return 0;
}
