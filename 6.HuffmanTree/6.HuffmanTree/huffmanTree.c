#include <stdlib.h>
#include <string.h>
#include "huffmanTree.h"

// 找[1...n]区间中，最小的2个节点的索引号，给上层空间
static void selectNode(HuffmanTree tree, int n, int *s1, int *s2) {
	int min = 0;		// 假设最小值的索引号
	// 找到第一个最小值，假设空间中，第一个parent==0的元素，假设他就是最小值
	for (int i = 1; i <= n; ++i) {
		if (tree[i].parent == 0) {
			min = i;
			break;
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (tree[i].parent == 0) {
			if (tree[i].weight < tree[min].weight) {
				min = i;
			}
		}
	}
	*s1 =  min;
	// 开始找第二个
	for (int i = 1; i <= n; ++i) {
		if (tree[i].parent == 0 && i != *s1) {		// 排除第一个已经找到的最小值
			min = i;
			break;
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (tree[i].parent == 0 && i != *s1) {
			if (tree[i].weight < tree[min].weight) {
				min = i;
			}
		}
	}
	*s2 = min;
}

HuffmanTree createHuffmanTree(const int *w, int n) {
	HuffmanTree tree;
	int m = 2 * n - 1;
	// 1.1 申请顺序数组，元素个数是2n-1，采用0号索引的位置不用，保证0值作为一个状态标志
	// 申请的数组个数2n，每个数组里保存的都是HuffmanNode
	tree = (HuffmanTree) malloc(sizeof(HuffmanNode) * (m + 1));
	// 1.2 初始化[1 ~ 2n-1]，用0来让每一个节点都是根节点
	for (int i = 1; i <= m; ++i) {
		tree[i].parent = tree[i].lChild = tree[i].rChild = 0;
		tree[i].weight = 0;
	}
	// 1.3 设置n个元素的权值[1 ~ n] 用户传来的元素权值
	for (int i = 1; i <= n; ++i) {
		tree[i].weight = w[i - 1];
	}
	// ----------------- 初始化结束，下面开始创建Huffman树 ------------
	// 填充从n+1下标到m下标的空间
	int s1, s2;
	for (int i = n + 1; i <= m; ++i) {
		// 从[1 ... i-1]范围内，找父节点为0(根节点)的结果中，权值最小的2个
		selectNode(tree, i - 1, &s1, &s2);
		// 将这2个权值最小的节点，填充到第i个位置的，第i个位置就是这2个节点父节点
		tree[s1].parent = tree[s2].parent = i;
		tree[i].lChild = s1;	tree[i].rChild = s2;
		tree[i].weight = tree[s1].weight + tree[s2].weight;
	}
	return tree;
}

void releaseHuffmanTree(HuffmanTree tree) {
	if (tree) {
		free(tree);
	}
}

HuffmanCode *createHuffmanCode(HuffmanTree tree, int n) {
	char *temp = (char *) malloc(sizeof(char) * n);
	// 生成了n个字符的编码表，表中每个表项里保存的是这个字符对应的编码空间首地址
	HuffmanCode *codes = (HuffmanCode *) malloc(sizeof(HuffmanCode) * n);
	memset(codes, 0, sizeof(HuffmanCode) * n);
	// 对n个字符，查看Huffman树，生成对应的堆空间，将这个空间赋值给对应codes的位置
	int start;							// 在临时空间指向编码的位置，从后往前进行编码
	int p;								// 存放当前节点的父节点信息
	int pos;							// 找父节点前的位置
	// 逐步字符求Huffman编码
	for (int i = 1; i <= n; ++i) {		// 遍历树中[1...n]的字符
		start = n - 1;
		temp[start] = '\0';
		pos = i;
		p = tree[i].parent;
		while (p) {
			--start;
			temp[start] = ((tree[p].lChild == pos) ? '0' : '1');
			pos = p;
			p = tree[p].parent;
		}
		// 第i个字符编码空间，进行分配，将临时空间里的值拷贝给刚刚分配空间
		codes[i - 1] = (HuffmanCode) malloc(sizeof(char) * (n - start));
		strcpy(codes[i - 1], &temp[start]);
	}
	free(temp);
	return codes;
}

void releaseHuffmanCode(HuffmanCode *codes, int n) {
	if (codes) {
		for (int i = 0; i < n; ++i) {
			if (codes[i]) {
				free(codes[i]);
			}
		}
		free(codes);
	}
}


