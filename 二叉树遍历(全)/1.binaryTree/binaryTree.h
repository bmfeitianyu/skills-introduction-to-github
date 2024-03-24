#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <stdlib.h>
#include <stdio.h>

typedef int Element;
// 树的节点结构
typedef struct treeNode {
	Element data;
	struct treeNode *left;
	struct treeNode *right;
}TreeNode;
typedef TreeNode* pTreeNode;

// 二叉树的描述信息结构
typedef struct {
	TreeNode *root;			// 二叉树的根节点
	int count;				// 二叉树的节点个数
}BinaryTree;

BinaryTree *createBinaryTree(TreeNode *root);
void releaseBinaryTree(BinaryTree *tree);

TreeNode *createTreeNode(Element e);
void insertBinaryTree(BinaryTree *tree, TreeNode *parent, TreeNode *left, TreeNode *right);
void visitTreeNode(TreeNode *node);
void preOrderBTreeRecur(BinaryTree *tree);				// 先序遍历tree，使用递归方法
void inOrderBTreeRecur(BinaryTree *tree);				// 中序遍历tree，使用递归方法
void postOrderBTreeRecur(BinaryTree *tree);				// 后序遍历tree，使用递归方法
// 层级遍历、广度遍历
void levelOrderBTree(BinaryTree *tree);

void preOrderBTreeNoRecur(BinaryTree *tree);
void inOrderBTreeNoRecur(BinaryTree *tree);
void postOrderBTreeNoRecur(BinaryTree *tree);
#endif
