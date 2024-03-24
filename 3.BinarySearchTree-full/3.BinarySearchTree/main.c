#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "BSearchTree.h"
// 1. 普通二叉搜索树测试
void test01() {
	Element data[] = {55, 33, 45, 100, 
					  22, 80, 8, 130, 120};
	BSTree *tree = createBSTree();
	if (tree == NULL) {
		return;
	}
	// 插入元素
	for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
		// insertBSTreeNoRecur(tree, data[i]);
		insertBSTreeRecur(tree, data[i]);
	}
	printf("二分搜索树的中序遍历：");
	inOrderBSTree(tree);
	printf("\n");
	int h = heightBSNode(tree->root);
	printf("高度: %d\n", h);
	releaseBSTree(tree);
}
// 二分搜索树的测试
void binarySearchFindTest(BSTree *tree, int cnt, Element value) {
	BSNode *node = NULL;
	for (int i = 0; i < cnt; ++i) {
		node = searchBSTree(tree, value);
		if (node) {
			printf("!!!BST Find!!!\n");
			return;
		}
	}
}
// 线性查找，测试次数cnt
void linearFindTest(Element *data, int n, int cnt, Element value) {
	for (int i = 0; i < cnt; ++i) {
		for (int j = 0; j < n; ++j) {
			if (data[j] == value) {
				printf("!!! Linear Find !!!");
				return;
			}
		}
	}
}
/* 顺序表和二分搜索树的查找效率
 * 随机生成n个数字，范围在1~m之间，然后测试查找m+1(找不到)，模拟了最坏的情况
 * 根据运行的时间，来验证线性查找和二分搜索树查找的效率
 * */
void test02() {
	int n = 10000;
	Element m = n + 5000;
	int cnt = 10000;
	clock_t start, end;			// 系统滴答数
	// 创建n个元素，取值范围在1-m
	Element *data = (Element *) malloc(sizeof(Element) * n);
	srand(time(NULL));
	for (int i = 0; i < n; ++i) {
		data[i] = rand() % m + 1;
	}
	// 测试线性查找的时间
	start = clock();
	linearFindTest(data, n, cnt, m + 10);
	end = clock();
	printf("线性查找耗时: %f.\n", (double )(end - start) / CLOCKS_PER_SEC);
	// 测试二分搜索树的查找时间消耗
	BSTree *tree = createBSTree();
	for (int i = 0; i < n; ++i) {
		insertBSTreeNoRecur(tree, data[i]);
	}
	start = clock();
	binarySearchFindTest(tree, cnt, m + 10);
	end = clock();
	printf("二分搜索树查找耗时: %f.\n", (double )(end - start) / CLOCKS_PER_SEC);
	releaseBSTree(tree);
	free(data);
}

void test03() {
	Element data[] = {55, 33, 45, 100,
					  22, 80, 8, 130, 120};
	BSTree *tree = createBSTree();
	if (tree == NULL) {
		return;
	}
	// 插入元素
	for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
		insertBSTreeNoRecur(tree, data[i]);
	}
	printf("二分搜索树的中序遍历：");
	inOrderBSTree(tree);
	printf("\n");
	printf("删除8节点\n");
	// deleteBSTreeNoRecur(tree, 55);
	deleteBSTreeRecur(tree, 55);
	printf("二分搜索树的中序遍历：");
	inOrderBSTree(tree);
	printf("\n");
	releaseBSTree(tree);
}

int main() {
	test03();
	return 0;
}