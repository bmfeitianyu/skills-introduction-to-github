#include <stdlib.h>
#include "quickUnionSet.h"

QuickUnionSet *createQuickUnionSet(int n) {
	QuickUnionSet *setQU = (QuickUnionSet *) malloc(sizeof(QuickUnionSet));
	setQU->data = (Element *) malloc(sizeof(Element) * n);
	setQU->parent = (int *) malloc(sizeof(int ) * n);
	setQU->size = (int *) malloc(sizeof(int ) * n);
	setQU->n = n;
	return setQU;
}

void initQuickUnionSet(QuickUnionSet *setQU, const Element *data, int n) {
	for (int i = 0; i < setQU->n; ++i) {
		setQU->data[i] = data[i];
		setQU->parent[i] = i;			// 父关系为自身的索引，每个人都是根
		setQU->size[i] = 1;
	}
}

static int findIndex(QuickUnionSet *setQF, Element a) {
	for (int i = 0; i < setQF->n; ++i) {
		if (setQF->data[i] == a) {
			return i;
		}
	}
	return -1;
}

static int findRootIndex(QuickUnionSet *setQU, Element e) {
	// 找e的父亲，再找这个父亲的父亲，直到发现父亲的父亲是自己，那就是根了
	int curIndex = findIndex(setQU, e);		// 如果为-1 补
	// 向上遍历
	while (setQU->parent[curIndex] != curIndex) {
		curIndex = setQU->parent[curIndex];			// 将父节点ID作为下一个寻找的ID号
	}
	return curIndex;
}

int isSameQU(QuickUnionSet *setQU, Element a, Element b) {
	// a和b的根节点
	int aRoot = findRootIndex(setQU, a);
	int bRoot = findRootIndex(setQU, b);
	if (aRoot == -1 || bRoot == -1) {
		return 0;
	}
	return aRoot == bRoot;
}

/* 在QuickUnion集合中，将a元素和b元素合并
 * 1. 找到a和b的根节点
 * 2. 将b的父节点指向a的索引
 * 根据size做优化，谁的元素多，就让另一根接入元素多的根
 * */
void unionQU(QuickUnionSet *setQU, Element a, Element b) {
	int aRoot = findRootIndex(setQU, a);
	int bRoot = findRootIndex(setQU, b);
	if (aRoot == -1 || bRoot == -1) {
		return ;
	}
	if (aRoot != bRoot) {			// a 和 b不在一个集合
		// 根据根节点元素个数来决定合并顺序
		int aSize = setQU->size[aRoot];
		int bSize = setQU->size[bRoot];
		if (aSize >= bSize) {		// 将b元素的根指向a元素的根
			setQU->parent[bRoot] = aRoot;
			setQU->size[aRoot] += bSize;	// a就是根，更新这个根中的元素个数
		} else {
			setQU->parent[aRoot] = bRoot;
			setQU->size[bRoot] += aSize;
		}
	}
}
