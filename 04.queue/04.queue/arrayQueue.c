#include "arrayQueue.h"

ArrayQueue *createArrayQueue() {
	ArrayQueue *queue = (ArrayQueue *)malloc(sizeof(ArrayQueue));
	if (queue == NULL) {
		printf(".....!\n");
		return NULL;
	}
	queue->front = queue->rear = 0;
	return queue;
}

void releaseArrayQueue(ArrayQueue *queue) {
	if (queue) {
		free(queue);
	}
}

int enArrayQueue(ArrayQueue *queue, Element e) {
	// 先判断队列满不满
	if ((queue->rear + 1) % MaxQueue == queue->front) {
		printf("Queue full!\n");
		return -1;
	}
	queue->rear = (queue->rear + 1) % MaxQueue;
	queue->data[queue->rear] = e;
	return 0;
}

int deArrayQueue(ArrayQueue *queue, Element *e) {
	// 先判断队列空不空
	if (queue->rear == queue->front) {
		printf("Queue empty!\n");
		return -1;
	}
	queue->front = (queue->front + 1) % MaxQueue;
	*e = queue->data[queue->front];
	return 0;
}
