#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H
/* 顺序栈 满递增栈*/
#include "common.h"
#define MaxStackSize 5
typedef struct {
	Element data[MaxStackSize];
	int top;
}ArrayStack;

ArrayStack *createArrayStack();
void releaseArrayStack(ArrayStack *stack);

int pushArrayStack(ArrayStack *stack, Element e);
int popArrayStack(ArrayStack *stack, Element *e);
#endif
