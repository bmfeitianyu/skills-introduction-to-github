#include <stdlib.h>
#include "quickFindSet.h"

QuickFindSet *createQuickFindSet(int n) {
	QuickFindSet *setQF = (QuickFindSet *)malloc(sizeof(QuickFindSet));
	setQF->n = n;
	setQF->data = (Element *) malloc(sizeof(Element) * n);
	setQF->groupID = (Element *) malloc(sizeof(int) * n);
	return setQF;
}

void releaseQuickFindSet(QuickFindSet *setQF) {
	if (setQF) {
		if (setQF->data)
			free(setQF->data);
		if (setQF->groupID)
			free(setQF->groupID);
		free(setQF);
	}
}

void initQuickFindSet(QuickFindSet *setQF, const Element *data, int n) {
	for (int i = 0; i < n; ++i) {
		setQF->data[i] = data[i];		// 元素的赋值
		setQF->groupID[i] = i;			// 第i个元素的组ID就是i，自己管理自己
	}
}

static int findIndex(QuickFindSet *setQF, Element a) {
	for (int i = 0; i < setQF->n; ++i) {
		if (setQF->data[i] == a) {
			return i;
		}
	}
	return -1;
}

int isSameQF(QuickFindSet *setQF, Element a, Element b) {
	// 把元素转换为并查集中对应的索引号
	int aIndex = findIndex(setQF, a);
	int bIndex = findIndex(setQF, b);
	if (aIndex == -1 || bIndex == -1) {		// 并查集中没有a或b，返回假
		return 0;
	}
	// 根据索引号，找到元素a和b的组ID，如果组ID相等，在一个集合
	return setQF->groupID[aIndex] == setQF->groupID[bIndex];
}
/* 将元素a和元素b合并，把所有和b元素组信息改为a的组ID，把b元素合并到a */
void unionQF(QuickFindSet *setQF, Element a, Element b) {
	// 把b的老大管的所有人，都合并到a的老大
	int aIndex = findIndex(setQF, a);
	int bIndex = findIndex(setQF, b);
	int bGrpID = setQF->groupID[bIndex];			// 备份b的老大，后面就判断所有元素是不是老大是b
	for (int i = 0; i < setQF->n; ++i) {
		if (setQF->groupID[i] == bGrpID) {
			setQF->groupID[i] = setQF->groupID[aIndex];		// b的组ID，替换成a的组ID
		}
	}
}

