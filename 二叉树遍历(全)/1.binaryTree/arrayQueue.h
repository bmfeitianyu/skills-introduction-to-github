#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H
#include "binaryTree.h"

#define MaxQueue 20
// 定义顺序队列的结构
typedef struct {
	pTreeNode data[MaxQueue];
	int front;
	int rear;
}ArrayPTreeQueue;

ArrayPTreeQueue *createArrayQueue();
void releaseArrayQueue(ArrayPTreeQueue *queue);

int enArrayQueue(ArrayPTreeQueue *queue, pTreeNode e);
int deArrayQueue(ArrayPTreeQueue *queue, pTreeNode *e);
#endif
