#ifndef LINKSTACK_H
#define LINKSTACK_H
/* 链式存储栈，关注节点结构，栈的操作结构 */
#include "common.h"
// 节点结构
typedef struct stackNode {
	Element e;
	struct stackNode *next;
}StackNode;
// 链式栈的表头结构
typedef struct {
	StackNode *top;
	int count;				// 统计栈里的元素
}LinkStack;

LinkStack *createLinkStack();
void releaseLinkStack(LinkStack *stack);

int pushLinkStack(LinkStack *stack, Element e);
int popLinkStack(LinkStack *stack, Element *e);

#endif
