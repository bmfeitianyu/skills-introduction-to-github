#include <stdlib.h>
#include <stdio.h>
#include "arrayStack.h"

ArrayStack *createArrayStack() {
	ArrayStack *stack = (ArrayStack *) malloc(sizeof(ArrayStack));
	if (stack == NULL) {
		printf("malloc failed\n");
		return NULL;
	}
	stack->top = -1;
	return stack;
}

/* 数据能存放的位置 ： [0, 1, ... max-1] */
int pushArrayStack(ArrayStack *stack, pTreeNode e) {
	// 上溢出的问题排除
	if (stack->top >= MaxStackSize - 1) {
		return -1;
	}
	stack->data[++stack->top] = e;
	return 0;
}

int popArrayStack(ArrayStack *stack, pTreeNode *e) {
	if (stack->top < 0) {
		return -1;
	}
	*e = stack->data[stack->top--];
	return 0;
}

void releaseArrayStack(ArrayStack *stack) {
	if (stack) {
		free(stack);
	}
}
