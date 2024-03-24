#include "binaryTree.h"
#include "arrayQueue.h"

/* 申请二叉树的信息体，若有根节点，那么指向根节点，并更新树的节点个数 */
BinaryTree *createBinaryTree(TreeNode *root) {
	BinaryTree *tree = (BinaryTree *) malloc(sizeof(BinaryTree));
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
/* 后序递归遍历，释放节点 */
static void destroyTreeNode(BinaryTree *tree, TreeNode *node) {
	if (node) {
		destroyTreeNode(tree, node->left);
		destroyTreeNode(tree, node->right);
		free(node);
		tree->count--;
	}
}
/* 释放二叉树，通过后序遍历的方式，将节点逐个释放 */
void releaseBinaryTree(BinaryTree *tree) {
	if (tree) {
		destroyTreeNode(tree, tree->root);
		printf("tree have %d node!\n", tree->count);
		free(tree);
	}
}
/* 产生新节点，初始化左右指针为NULL */
TreeNode *createTreeNode(Element e) {
	TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
	if (node == NULL) {
		fprintf(stderr, "tree node malloc failed!\n");
		return NULL;
	}
	node->data = e;
	node->left = node->right = NULL;
	return node;
}
/* 向父节点插入左右节点 */
void insertBinaryTree(BinaryTree *tree, TreeNode *parent, TreeNode *left, TreeNode *right) {
	if (tree && parent) {
		parent->left = left;
		parent->right = right;
		if (left)
			tree->count++;
		if (right)
			tree->count++;
	}
}

static void preOrder(TreeNode *node) {
	if (node) {
		visitTreeNode(node);
		preOrder(node->left);
		preOrder(node->right);
	}
}

static void inOrder(TreeNode *node) {
	if (node) {
		inOrder(node->left);
		visitTreeNode(node);
		inOrder(node->right);
	}
}

static void postOrder(TreeNode *node) {
	if (node) {
		postOrder(node->left);
		postOrder(node->right);
		visitTreeNode(node);
	}
}

void preOrderBTreeRecur(BinaryTree *tree) {
	if (tree) {
		preOrder(tree->root);
	}
}

void visitTreeNode(TreeNode *node) {
	printf("\t%c", node->data);
}

void levelOrderBTree(BinaryTree *tree) {
	ArrayPTreeQueue *queue = createArrayQueue();
	pTreeNode node;
	enArrayQueue(queue, tree->root);			// 初始化任务队列
	while (deArrayQueue(queue, &node) != -1) {
		// 访问这个节点
		visitTreeNode(node);
		// 根据这个节点的左右情况，再次更新任务（如果左，就把左节点的地址入队，如果右...）
		if (node->left) {
			enArrayQueue(queue, node->left);
		}
		if (node->right) {
			enArrayQueue(queue, node->right);
		}
	}
	releaseArrayQueue(queue);
}

void inOrderBTreeRecur(BinaryTree *tree) {
	if (tree) {
		inOrder(tree->root);
	}
}

void postOrderBTreeRecur(BinaryTree *tree) {
	if (tree) {
		postOrder(tree->root);
	}
}
