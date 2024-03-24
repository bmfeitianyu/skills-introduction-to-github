#include "linkStack.h"

LinkStack *createLinkStack() {
	LinkStack *stack = (LinkStack *) malloc(sizeof(LinkStack));
	if (stack == NULL) {
		printf("malloc failed!\n");
		return NULL;
	}
	stack->top = NULL;
	stack->count = 0;
	return stack;
}

int pushLinkStack(LinkStack *stack, Element e) {
	StackNode *node = (StackNode *) malloc(sizeof(StackNode));
	if (node == NULL) {
		printf(".....!\n");
		return -1;
	}
	node->e = e;
	node->next = stack->top;
	stack->top = node;
	stack->count++;
	return 0;
}

int popLinkStack(LinkStack *stack, Element *e) {
	if (stack->top == NULL) {
		printf(",,,,,,,,\n");
		return -1;
	}
	*e = stack->top->e;
	StackNode *tmp = stack->top;
	stack->top = tmp->next;
	free(tmp);
	stack->count--;
	return 0;
}

void releaseLinkStack(LinkStack *stack) {
	if (stack) {
		// 以top指向的元素逐个删除
		while (stack->top) {
			StackNode *tmp = stack->top;
			stack->top = tmp->next;
			free(tmp);
			stack->count--;
		}
		printf("stack count : %d\n", stack->count);
		free(stack);
	}
}
