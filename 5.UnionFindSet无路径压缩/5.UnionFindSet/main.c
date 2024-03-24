#include <stdio.h>
#include "quickFindSet.h"
#include "quickUnionSet.h"
// QuickFind的测试
int test01() {
	int n = 9;
	QuickFindSet *QFSet = createQuickFindSet(n);
	Element data[9];
	for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
		data[i] = i;
	}
	initQuickFindSet(QFSet, data, n);

	unionQF(QFSet, 3, 4);
	unionQF(QFSet, 8, 0);
	unionQF(QFSet, 2, 3);
	unionQF(QFSet, 5, 6);
	if (isSameQF(QFSet, 0, 2)) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}
	if (isSameQF(QFSet, 2, 4)) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}
	unionQF(QFSet, 5, 1);
	unionQF(QFSet, 7, 3);
	unionQF(QFSet, 1, 6);
	unionQF(QFSet, 4, 8);
	if (isSameQF(QFSet, 0, 2)) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}
	if (isSameQF(QFSet, 2, 4)) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}
	releaseQuickFindSet(QFSet);
	return 0;
}

int test02() {
	int n = 9;
	QuickUnionSet *QUSet = createQuickUnionSet(n);
	Element data[9];
	for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
		data[i] = i;
	}
	initQuickUnionSet(QUSet, data, n);

	unionQU(QUSet, 3, 4);
	unionQU(QUSet, 8, 0);
	unionQU(QUSet, 2, 3);
	unionQU(QUSet, 5, 6);
	if (isSameQU(QUSet, 0, 2)) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}
	if (isSameQU(QUSet, 2, 4)) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}
	unionQU(QUSet, 5, 1);
	unionQU(QUSet, 7, 3);
	unionQU(QUSet, 1, 6);
	unionQU(QUSet, 4, 8);
	if (isSameQU(QUSet, 0, 2)) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}
	if (isSameQU(QUSet, 2, 4)) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}
	// releaseQuickFindSet(QFSet);
	return 0;
}

int main() {
	test02();
	return 0;
}