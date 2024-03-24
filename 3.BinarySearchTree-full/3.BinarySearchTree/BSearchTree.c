#include <stdio.h>
#include <stdlib.h>
#include "BSearchTree.h"

BSTree *createBSTree() {
	BSTree *tree = (BSTree *) malloc(sizeof(BSTree));
	if (tree == NULL) {
		return NULL;
	}
	tree->root = NULL;
	tree->count = 0;
	return tree;
}
// 后序遍历方式释放所有结点
static void freeNode(BSTree *tree, BSNode *node) {
	if (node) {
		freeNode(tree, node->left);
		freeNode(tree, node->right);
		free(node);
		tree->count--;
	}
}
void releaseBSTree(BSTree *tree) {
	if (tree) {
		// 先释放所有树中的结点
		freeNode(tree, tree->root);
		printf("There are %d node after released!\n", tree->count);
		// 再释放树的结构
		free(tree);
	}
}

BSNode *searchBSTree(BSTree *tree, Element e) {
	// 引入辅助指针，指向遍历的节点
	BSNode *node = tree->root;
	while (node) {
		if (e < node->data) {
			node = node->left;
		} else if (e > node->data) {
			node = node->right;
		} else {			// e == node->data
			return node;
		}
	}
	return NULL;
}
static BSNode *createBSNode(Element e) {
	BSNode *node = (BSNode *) malloc(sizeof(BSNode));
	if (node == NULL) {
		return NULL;
	}
	node->data = e;
	node->left = node->right = NULL;
	return node;
}

void insertBSTreeNoRecur(BSTree *tree, Element e) {
	BSNode *cur = tree->root;
	BSNode *pre = NULL;
	// 1. 找到待插入的位置
	while (cur) {
		pre = cur;
		if (e < cur->data) {
			cur = cur->left;
		} else if (e > cur->data) {
			cur = cur->right;
		} else {				// 插入元素已经在BST树中存在，那么就直接返回
			return;
		}
	}
	// 此时，pre就是唯一知道待插入节点的前一个位置在哪里
	// 2. 分配节点
	BSNode *node = createBSNode(e);
	// 3. 将这个新的节点，放到待插入位置前面那个节点的左或右
	// 放入pre指向结点的左或右
	if (pre) {
		if (e < pre->data) {
			pre->left = node;
		} else {
			pre->right = node;
		}
	} else {						// 树中还没有根
		tree->root = node;
	}
	tree->count++;
}

static void inOrder(BSNode *node) {
	if (node) {
		inOrder(node->left);
		visitBSNode(node);
		inOrder(node->right);
	}
}
void inOrderBSTree(BSTree *tree) {
	if (tree && tree->root) {
		inOrder(tree->root);
	}
}
void visitBSNode(BSNode *node) {
	printf("\t%d", node->data);
}

static void deleteMiniNode(BSNode *node) {
	BSNode *mini = node->right;		// 找最小值
	BSNode *pre = node;
	while (mini && mini->left) {
		pre = mini;
		mini = mini->left;
	}
	node->data = mini->data;
	// 说明找到了后继节点，可能是node节点的右孩子，也可能是右孩子的最左边
	if (pre->data == node->data) {
		pre->right = mini->right;
	} else {
		pre->left = mini->right;
	}
	free(mini);
}

/* 1. 找到这个待删除的节点node，还需要一个pre节点指向上一个位置
 * 2. 判断node的度的情况
 * */
void deleteBSTreeNoRecur(BSTree *tree, Element e) {
	// 1. 找到元素
	BSNode *node = tree->root;
	BSNode *pre = NULL;
	BSNode *tmp = NULL;
	while (node) {
		if (e < node->data) {
			pre = node;
			node = node->left;
		} else if (e > node->data) {
			pre = node;
			node = node->right;
		} else {
			break;
		}
	}
	// 2. 找到node，删除的节点是非根节点，找到了实际元素
	if (pre && node) {
		// 2.1 判断node的度
		if (node->left == NULL) {
			tmp = node->right;
		} else if (node->right == NULL) {
			tmp = node->left;
		} else {		// 度为2的情况，从node节点中找后继，然后进行删除
			deleteMiniNode(node);
			tree->count--;
			return;
		}
		if (node->data < pre->data) {
			pre->left = tmp;
		} else {
			pre->right = tmp;
		}
		free(node);
		tree->count--;
		return;
	}
	if (pre == NULL) {
		deleteMiniNode(node);
		tree->count--;
	}
}

static BSNode *insertBSNodeRecur(BSTree *tree, BSNode *node, Element e) {
	if (node == NULL) {
		tree->count++;
		return createBSNode(e);
	}
	if (e < node->data) {
		node->left = insertBSNodeRecur(tree, node->left, e);
	} else if (e > node->data) {
		node->right = insertBSNodeRecur(tree, node->right, e);
	}
	return node;
}

void insertBSTreeRecur(BSTree *tree, Element e) {
	tree->root = insertBSNodeRecur(tree, tree->root, e);
}

int heightBSNode(BSNode *node) {
	if (node == NULL) {
		return 0;
	}
	int leftHeight = heightBSNode(node->left);
	int rightHeight = heightBSNode(node->right);
	if (leftHeight > rightHeight) {
		return ++leftHeight;
	} else {
		return ++rightHeight;
	}
}
// 找后继节点的方法
static BSNode *miniValueBSNode(BSNode *node) {
	while (node && node->left) {
		node = node->left;
	}
	return node;
}

static BSNode *deleteBSNode(BSTree *tree, BSNode *node, Element e) {
	if (node == NULL) {
		return NULL;
	}
	if (e < node->data) {
		node->left = deleteBSNode(tree, node->left, e);
	} else if (e > node->data) {
		node->right = deleteBSNode(tree, node->right, e);
	} else {				// 找到e
		BSNode *tmp;
		if (node->left == NULL) {
			tmp = node->right;
			free(node);
			tree->count--;
			return tmp;
		}
		if (node->right == NULL) {
			tmp = node->left;
			free(node);
			tree->count--;
			return tmp;
		}
		// 度为2，删除度为2的节点，变成找到后继节点，将后继节点的值拷贝给度为2的点
		// 把删除的任务，转换为删除后继节点
		tmp = miniValueBSNode(node->right);
		node->data = tmp->data;
		node->right = deleteBSNode(tree, node->right, tmp->data);
	}
	return node;
}

void deleteBSTreeRecur(BSTree *tree, Element e) {
	if (tree) {
		tree->root = deleteBSNode(tree, tree->root, e);
	}
}
