#include "binaryTree.h"

BinaryTree *initTree1() {
	TreeNode *nodeA = createTreeNode('A');
	TreeNode *nodeB = createTreeNode('B');
	TreeNode *nodeC = createTreeNode('C');
	TreeNode *nodeD = createTreeNode('D');
	TreeNode *nodeE = createTreeNode('E');
	TreeNode *nodeF = createTreeNode('F');
	TreeNode *nodeG = createTreeNode('G');
	TreeNode *nodeH = createTreeNode('H');
	TreeNode *nodeK = createTreeNode('K');

	BinaryTree *tree = createBinaryTree(nodeA);
	insertBinaryTree(tree, nodeA, nodeB, nodeE);
	insertBinaryTree(tree, nodeB, NULL, nodeC);
	insertBinaryTree(tree, nodeE, NULL, nodeF);
	insertBinaryTree(tree, nodeC, nodeD, NULL);
	insertBinaryTree(tree, nodeF, nodeG, NULL);
	insertBinaryTree(tree, nodeG, nodeH, nodeK);
	return tree;
}

int main() {
	BinaryTree *tree = initTree1();
	printf("树的节点数: %d\n", tree->count);
	printf("先序遍历: ");
	preOrderBTreeRecur(tree);
	printf("\n中序遍历: ");
	inOrderBTreeRecur(tree);
	printf("\n后序遍历: ");
	postOrderBTreeRecur(tree);
	printf("\n层次遍历: ");
	levelOrderBTree(tree);
	printf("\n非递归先序遍历: ");
	preOrderBTreeNoRecur(tree);
	printf("\nInorder: ");
	inOrderBTreeNoRecur(tree);
	printf("\nPostOrder:");
	postOrderBTreeNoRecur(tree);
	printf("\n");
	releaseBinaryTree(tree);
	return 0;
}
