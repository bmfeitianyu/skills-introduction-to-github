#include "arrayQueue.h"
#include "linkQueue.h"

// 测试顺序存储的循环队列
int test01() {
	ArrayQueue *queue = createArrayQueue();
	Element e;
	for (int i = 0; i < 4; ++i) {
		enArrayQueue(queue, i + 100);
	}
	printf("===========!\n");
	enArrayQueue(queue, 500);
	printf("Queue:");
	for (int i = 0; i < 4; ++i) {
		deArrayQueue(queue, &e);
		printf("\t%d", e);
	}
	printf("\n");
	deArrayQueue(queue, &e);
	releaseArrayQueue(queue);
	return 0;
}

// 测试链式队列
int test02() {
	LinkQueue *queue = createLinkQueue();
	Element e;
	for (int i = 0; i < 6; ++i) {
		enLinkQueue(queue, i + 50);
	}
	printf("cnt: %d\n", queue->cnt);
	printf("Que:");
	for (int i = 0; i < 5; ++i) {
		deLinkQueue(queue, &e);
		printf("\t%d", e);
	}
	printf("\n");
	releaseLinkQueue(queue);
	return 0;
}

int main() {
	test02();
	return 0;
}