#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <stdio.h>
#include <stdlib.h>
typedef int Element;
// 定义平衡二叉树的节点结构
typedef struct AVLNode {
	Element data;
	struct AVLNode *left;
	struct AVLNode *right;
	int height;				// 每个节点的高度
}AVLNode;
// 平衡二叉树的结构
typedef struct {
	AVLNode *root;
	int count;
}AVLTree;

AVLTree *createAVLTree();				// 产生平衡二叉树
void releaseAVLTree(AVLTree *tree);		// 释放平衡二叉树
void visitAVLNode(AVLNode *node);		// 访问平衡二叉树的节点
void inOrderAVLTree(AVLTree *tree);		// 平衡二叉树的中序遍历

// 插入元素到AVL树
void insertAVLTree(AVLTree *tree, Element e);
// 从AVL树中删除元素
void deleteAVLTree(AVLTree *tree, Element e);
#endif
