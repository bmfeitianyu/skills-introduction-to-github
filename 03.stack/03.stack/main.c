#include <stdio.h>
#include "arrayStack.h"
#include "linkStack.h"
/*顺序栈的测试*/
int test01() {
	ArrayStack *stack = createArrayStack();
	Element e;
	if (stack == NULL) {
		return -1;
	}
	for (int i = 0; i < 5; ++i) {
		pushArrayStack(stack, i + 100);
	}
	pushArrayStack(stack, 500);
	printf("pop:");
	for (int i = 0; i < 5; ++i) {
		popArrayStack(stack, &e);
		printf("\t%d", e);
	}
	printf("\n");
	popArrayStack(stack, &e);
	releaseArrayStack(stack);
	return 0;
}

/* 链式栈的测试 */
int test02() {
	LinkStack *stack = createLinkStack();
	Element e;
	if (stack == NULL) {
		return -1;
	}
	for (int i = 0; i < 5; ++i) {
		pushLinkStack(stack, i + 50);
	}
	printf("stack node: %d\n", stack->count);
	printf("pop:");
	for (int i = 0; i < 5; ++i) {
		popLinkStack(stack, &e);
		printf("\t%d", e);
	}
	printf("\n");
	popLinkStack(stack, &e);
	releaseLinkStack(stack);
	return 0;
}

int main() {
	test02();
	return 0;
}