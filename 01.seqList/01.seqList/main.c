#include <stdio.h>
#include "sqList.h"

int main() {
	int n = 5;
	SqList *sqList = createSqList(n);
	// 操作这个顺序表
	for (int i = 0; i < n; ++i) {
		insertSqList(sqList, i + 1, i+100);
	}
	showSqList(sqList);
	insertSqList(sqList, 3, 300);
	showSqList(sqList);
	insertSqList(sqList, 9, 900);
	showSqList(sqList);
	printf("===========================\n");
	deleteSqList(sqList, 4);
	showSqList(sqList);
	releaseSqList(sqList);
	return 0;
}
