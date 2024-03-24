#include "linkQueue.h"

LinkQueue *createLinkQueue() {
	LinkQueue *linkQueue = (LinkQueue *) malloc(sizeof(LinkQueue));
	if (linkQueue == NULL) {
		printf(".....!\n");
		return NULL;
	}
	linkQueue->front = linkQueue->rear = NULL;
	linkQueue->cnt = 0;
	return linkQueue;
}

int enLinkQueue(LinkQueue *queue, Element e) {
	// 先申请节点
	QueNode *node = (QueNode *) malloc(sizeof(QueNode));
	if (node == NULL) {
		printf("........!\n");
		return -1;
	}
	node->data = e;
	node->next = NULL;
	if (queue->rear) {					// 队尾已经指向了有效数据
		queue->rear->next = node;
		queue->rear = node;
	} else {							// 队尾为空，说明队列里没有元素
		queue->rear = queue->front = node;
	}
	queue->cnt++;
	return 0;
}

int deLinkQueue(LinkQueue *queue, Element *e) {
	// 出队要进行判断
	if (queue->front == NULL) {
		printf("queue empty!\n");
		return -1;
	}
	*e = queue->front->data;
	QueNode *tmp = queue->front;
	queue->front = tmp->next;
	free(tmp);
	queue->cnt--;
	if (queue->front == NULL) {			// 队列已经没有元素了
		queue->rear = NULL;
	}
	return 0;
}

void releaseLinkQueue(LinkQueue *queue) {
	if (queue) {
		QueNode *node;
		// 从队头开始逐个释放元素
		while (queue->front) {
			node = queue->front;
			queue->front = node->next;
			free(node);
			queue->cnt--;
		}
		printf("queue have %d node!\n", queue->cnt);
		free(queue);
	}
}
