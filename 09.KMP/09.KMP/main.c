#include <stdio.h>
#include "findStr.h"

void test01(StrType *str, StrType *pattern) {
	int res = index_simple(str, pattern);
	printf("index: %d\n", res);
}

void test02(StrType *str, StrType *pattern) {
	int *next= (int *) malloc(sizeof(int ) * (pattern->length + 1));
	getNext(pattern, next);
	printf("index: %d\n", indexKMP(str, pattern, next));
	free(next);
}

int main() {
	StrType str;
	StrType subStr;

	str.str = NULL;
	subStr.str = NULL;

	strAssign(&str, "ABCDABCABCABABCABCDA");
	strAssign(&subStr, "ABCABCD");

	// test01(&str, &subStr);
	test02(&str, &subStr);

	releaseStr(&str);
	releaseStr(&subStr);
	return 0;
}