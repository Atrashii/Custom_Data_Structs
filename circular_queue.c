#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAXSIZE 64

typedef struct CircQueue {
	int data[MAXSIZE];
	size_t elements;
	int front;
	int rear;
} Queue;

void init_queue(Queue *queue) {
	queue->elements = 0;
	queue->front = 0;
	queue->rear = 0;
}

int getFront(Queue *queue) {
	if(queue->rear != queue->front) {
		return queue->data[queue->front];
	}
	return INT_MIN;
}

int getRear(Queue *queue) {
	if(queue->rear != queue->front) {
		return queue->data[queue->rear];
	}
	return INT_MIN;
}

void enqueue(Queue *queue, int data) {
	if(queue->elements == MAXSIZE) {
		fprintf(stderr, "Queue is full\n");
		return;
	}
	queue->rear = (queue->front + queue->elements) % MAXSIZE;
	queue->data[queue->rear] = data;
	queue->elements++; 
}

int dequeue(Queue *queue) {
	if(queue->elements == 0) {
		fprintf(stderr, "Queue is empty\n");
		return INT_MIN;
	}
	int value = queue->data[queue->front];
	queue->front = (queue->front + 1) % MAXSIZE;
	queue->elements--;
	return value;
}

int main(void) {
	Queue queue;
	init_queue(&queue);

	enqueue(&queue, 29);
	enqueue(&queue, 56);
	enqueue(&queue, 10);
	enqueue(&queue, 19);
	enqueue(&queue, 98);
	enqueue(&queue, 11);

	printf("getRear: %d\n", getRear(&queue));
	printf("getFront: %d\n", getFront(&queue));

	
	printf("Dequeue: %d\n", dequeue(&queue));
	printf("Dequeue: %d\n", dequeue(&queue));
	printf("getFront: %d\n", getFront(&queue));


	return 0;
}
