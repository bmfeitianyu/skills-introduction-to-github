#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H
/* 顺序栈 满递增栈*/
#include "binaryTree.h"
#define MaxStackSize 20
typedef struct {
	pTreeNode data[MaxStackSize];
	int top;
}ArrayStack;

ArrayStack *createArrayStack();
void releaseArrayStack(ArrayStack *stack);

int pushArrayStack(ArrayStack *stack, pTreeNode e);
int popArrayStack(ArrayStack *stack, pTreeNode *e);
#endif
