#ifndef B_SEARCH_TREE_H
#define B_SEARCH_TREE_H
/* 二叉搜索树，按照左小右大的规则进行约束 */
typedef int Element;
// 二分搜索树的节点，和普通二叉树节点没有什么区别
typedef struct bsNode {
	Element data;
	struct bsNode *left;
	struct bsNode *right;
}BSNode;
// 二分搜索树的结构
typedef struct {
	BSNode *root;			// 搜索树的根节点
	int count;				// 搜索树的元素
}BSTree;

// 创建BSTree的结构
BSTree *createBSTree();
// 释放BSTree及树中所有结点
void releaseBSTree(BSTree *tree);

// 中序遍历
void inOrderBSTree(BSTree *tree);
void visitBSNode(BSNode *node);

// 按照二分搜索树的规则插入数据（非递归方式）
void insertBSTreeNoRecur(BSTree *tree, Element e);
// 按照二分搜索树的规则插入数据（递归方式）
void insertBSTreeRecur(BSTree *tree, Element e);
// 在二分搜索树中，查找值为e的节点
BSNode *searchBSTree(BSTree *tree, Element e);
// 删除二叉搜索树的某个值的节点（非递归方式）
void deleteBSTreeNoRecur(BSTree *tree, Element e);
// 删除二叉搜索树的某个值的节点（递归方式）
void deleteBSTreeRecur(BSTree *tree, Element e);
// 计算树的高度
int heightBSNode(BSNode *node);

#endif
