#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H
#include "common.h"
#define MaxQueue 5
// 定义顺序队列的结构
typedef struct {
	Element data[MaxQueue];
	int front;
	int rear;
}ArrayQueue;

ArrayQueue *createArrayQueue();
void releaseArrayQueue(ArrayQueue *queue);

int enArrayQueue(ArrayQueue *queue, Element e);
int deArrayQueue(ArrayQueue *queue, Element *e);
#endif
