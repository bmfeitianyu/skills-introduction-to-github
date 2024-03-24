#include <stdio.h>
#include <stdlib.h>
#include "threadedBTree.h"

ThreadedBTree *createThreadedBTree(TBTNode *root) {
	ThreadedBTree *tree = (ThreadedBTree *) malloc(sizeof(ThreadedBTree));
	if (tree == NULL) {
		fprintf(stderr, "tree malloc failed!\n");
		return NULL;
	}
	if (root) {
		tree->root = root;
		tree->count = 1;
	} else {
		tree->root = NULL;
		tree->count = 0;
	}
	return tree;
}
// 后序遍历释放节点，但在找后继节点时，需要找非线索化的节点
static void freeTBTNode(ThreadedBTree *tree, TBTNode *node) {
	if (node) {
		if (node->lTag == 0) {
			freeTBTNode(tree, node->left);
		}
		if (node->rTag == 0) {
			freeTBTNode(tree, node->right);
		}
		free(node);
		tree->count--;
	}
}
/* 释放线索树 */
void releaseThreadedBTree(ThreadedBTree *tree) {
	if (tree) {
		freeTBTNode(tree, tree->root);
		printf("tree have %d node!\n", tree->count);
	}
}
/* 产生新节点，初始化左右指针为NULL */
TBTNode *createTBTNode(Element e) {
	TBTNode *node = (TBTNode *) malloc(sizeof(TBTNode));
	if (node == NULL) {
		fprintf(stderr, "tree node malloc failed!\n");
		return NULL;
	}
	node->data = e;
	node->left = node->right = NULL;
	node->lTag = node->rTag = 0;
	return node;
}
/* 树的节点访问 */
void visitTBTNode(TBTNode *node) {
	if (node) {
		printf("\t%c", node->data & 0xff);
	}
}

void insertThreadedBTree(ThreadedBTree *tree, TBTNode *parent, TBTNode *left, TBTNode *right) {
	if (tree && parent) {
		parent->left = left;
		parent->right = right;
		if (left)
			tree->count++;
		if (right)
			tree->count++;
	}
}
static TBTNode *pre = NULL;
static void inOrderThreading(TBTNode *node) {
	if (node) {
		inOrderThreading(node->left);
		if (node->left == NULL) {		// 更新当前节点的前驱
			node->lTag = 1;
			node->left = pre;
		}
		// 当前节点会不会是前面那个节点后继节点
		if (pre && pre->right == NULL) {
			pre->rTag = 1;
			pre->right = node;
		}
		pre = node;
		inOrderThreading(node->right);
	}
}

void inOrderThreadedTree(ThreadedBTree *tree) {
	if (tree) {
		inOrderThreading(tree->root);
	}
}

void inOrderTBTree(ThreadedBTree *tree) {
	TBTNode *node = tree->root;
	while (node) {
		while (node->lTag == 0) {
			node = node->left;
		}
		visitTBTNode(node);
		// 一直向右开始遍历，只要右边是后继标记，就查看
		while (node->rTag && node->right) {
			node = node->right;
			visitTBTNode(node);
		}
		node = node->right;
	}
}
