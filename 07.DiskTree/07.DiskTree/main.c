#include <stdio.h>
#include "diskTree.h"

int main() {
	DiskBTree *bTree = createDiskBTree();

	insertKey(bTree, 8);
	insertKey(bTree, 9);
	insertKey(bTree, 10);
	insertKey(bTree, 11);
	insertKey(bTree, 15);
	insertKey(bTree, 16);
	insertKey(bTree, 17);
	insertKey(bTree, 18);
	insertKey(bTree, 20);
	insertKey(bTree, 23);
	printBTree(bTree->root, 1);

	printf("========================\n");
	deleteKey(bTree, 15);
	printBTree(bTree->root, 1);
	releaseDiskBTree(bTree);
	return 0;
}