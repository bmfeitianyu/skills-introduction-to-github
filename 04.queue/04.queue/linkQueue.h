#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H
#include "common.h"
// 链式节点类型
typedef struct queNode {
	Element data;
	struct queNode *next;
}QueNode;
// 队列结构
typedef struct {
	QueNode *front;
	QueNode *rear;
	int cnt;			// 队列的元素个数
}LinkQueue;

LinkQueue *createLinkQueue();
void releaseLinkQueue(LinkQueue *queue);

int enLinkQueue(LinkQueue *queue, Element e);
int deLinkQueue(LinkQueue *queue, Element *e);
#endif
