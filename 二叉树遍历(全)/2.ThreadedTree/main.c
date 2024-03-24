#include <stdio.h>
#include "threadedBTree.h"

ThreadedBTree *initTree() {
	TBTNode *nodeA = createTBTNode('A');
	TBTNode *nodeB = createTBTNode('B');
	TBTNode *nodeC = createTBTNode('C');
	TBTNode *nodeD = createTBTNode('D');
	TBTNode *nodeE = createTBTNode('E');
	TBTNode *nodeF = createTBTNode('F');
	TBTNode *nodeG = createTBTNode('G');
	TBTNode *nodeH = createTBTNode('H');
	TBTNode *nodeK = createTBTNode('K');

	ThreadedBTree *tree = createThreadedBTree(nodeA);
	insertThreadedBTree(tree, nodeA, nodeB, nodeE);
	insertThreadedBTree(tree, nodeB, NULL, nodeC);
	insertThreadedBTree(tree, nodeE, NULL, nodeF);
	insertThreadedBTree(tree, nodeC, nodeD, NULL);
	insertThreadedBTree(tree, nodeF, nodeG, NULL);
	insertThreadedBTree(tree, nodeG, nodeH, nodeK);
	return tree;
}

int main() {
	ThreadedBTree *tree = initTree();
	// 1. 对原二叉树进行中序线索化，n + 1个空节点，按照左孩子指针指向前驱，右孩子指针指向后继
	inOrderThreadedTree(tree);
	// 2. 根据线索化后的树，进行中序遍历
	inOrderTBTree(tree);
	releaseThreadedBTree(tree);
	return 0;
}
