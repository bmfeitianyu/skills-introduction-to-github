#include "avlTree.h"

int main() {
	Element data[] = {10, 20, 30, 40, 
					  50, 60, 67, 80};
	AVLTree *tree = createAVLTree();
	if (tree == NULL) {
		return -1;
	}
	for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
		insertAVLTree(tree, data[i]);
	}
	printf("平衡二叉树的中序遍历：");
	inOrderAVLTree(tree);
	printf("\n平衡二叉树的高度: %d\n", tree->root->height);
	deleteAVLTree(tree, 60);
	printf("平衡二叉树的中序遍历：");
	inOrderAVLTree(tree);
	printf("\n平衡二叉树的高度: %d\n", tree->root->height);
	releaseAVLTree(tree);
	return 0;
}