#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "diskTree.h"

static void restoreBTree(DiskBTree *tree, BTNode *node);

/* 从节点中，搜索符合条件的key的位序 */
static int searchNodePos(BTNode *node, KeyType key) {
	int i = 1;			// 从1号索引开始搜索
	while (i <= node->keyNum && key > node->key[i]) {
		i++;
	}
	return i;
}

// ******************* B树的初始化 *******************//
DiskBTree *createDiskBTree() {
	DiskBTree *bTree = (DiskBTree *) malloc(sizeof(DiskBTree));
	bTree->root = NULL;
	bTree->count = 0;
	return bTree;
}

static void destroyBTNode(DiskBTree *tree, BTNode *node) {
	if (node) {
		for (int i = 0; i <= node->keyNum; ++i) {
			destroyBTNode(tree, node->ptr[i]);
		}
		free(node);
	}
}

void releaseDiskBTree(DiskBTree *tree) {
	if (tree) {
		destroyBTNode(tree, tree->root);
		free(tree);
	}
}
// ******************* B树的插入 *******************//
/* 将node节点分裂成为两个节点，前一半保留在原节点，后一半移动到other节点
 * 1. 申请新节点，将后半部分信息拷贝到新节点上
 * 2. 新申请的节点的子节点也更新
 * */
static void split(BTNode **node, int s, BTNode **other) {
	int i = s + 1;		// 老节点搬移位置
	int j = 1;			// 新节点待放入的位置
	int n = (*node)->keyNum;
	BTNode *splitNode = (BTNode *) malloc(sizeof(BTNode));
	memset(splitNode, 0, sizeof(BTNode));
	*other = splitNode;
	splitNode->ptr[0] = (*node)->ptr[s];
	for (; i <= n; ++i, ++j) {
		splitNode->key[j] = (*node)->key[i];
		splitNode->ptr[j] = (*node)->ptr[i];
		(*node)->key[i] = 0;
		(*node)->ptr[i] = 0;
	}
	splitNode->keyNum = MaxOrder - s;
	splitNode->parent = (*node)->parent;
	for (i = 0; i <= n -s ; ++i) {
		if (splitNode->ptr[i]) {
			splitNode->ptr[i]->parent = splitNode;
		}
	}
	(*node)->keyNum = s - 1;
}

/* 从节点node的pos处，插入key
 * 若是上移，child就非空，
 * 在叶子节点插入，child就为null
 * */
static void insertNode(BTNode *node, int pos, KeyType key, BTNode *child) {
	// 从节点中，移动pos及pos后的元素，最后再更新pos位置的值
	int i;
	int n = node->keyNum;
	for (i = n; i >= pos; --i) {
		node->key[i + 1] = node->key[i];
		node->ptr[i + 1] = node->ptr[i];
	}
	node->key[pos] = key;
	node->ptr[pos] = child;
	if (child) {
		child->parent = node;
	}
	node->keyNum++;
}
/* 创建一个根节点 */
static BTNode *createRootNode(KeyType key, BTNode *p0, BTNode *p1) {
	BTNode *node =  (BTNode *) malloc(sizeof(BTNode));

	node->keyNum = 1;
	node->key[1] = key;
	node->ptr[0] = p0;
	node->ptr[1] = p1;
	if (p0) {
		p0->parent = node;
	}
	if (p1) {
		p1->parent = node;
	}
	node->parent = NULL;
	return node;
}

/* 将key插入到B树中的node节点的pos位序处，根据B树的规则来决定是否分离 */
static void insertBTree(DiskBTree *tree, KeyType key, BTNode *node, int pos) {
	int mid;
	BTNode *child = NULL;
	KeyType x = key;
	int finish = 0;
	int needNewRoot = 0;

	if (node) {		// 有父节点，要么直接插入，要么进行分离
		while (!finish && !needNewRoot) {
			insertNode(node, pos, x, child);
			if (node->keyNum < MaxOrder) {
				finish = 1;
			} else {			// 超过了最大的有效位置
				mid = (MaxOrder + 1) / 2;
				x = node->key[mid];
				split(&node, mid, &child);
				if (node->parent) {
					node = node->parent;
					pos = searchNodePos(node, x);
				} else {
					needNewRoot = 1;
				}
			}
		}
	} else {		// 无父节点，现在插入的一定是一个根节点
		tree->root = createRootNode(key, NULL, NULL);
		tree->count = 1;
	}
	if (needNewRoot) {
		tree->root = createRootNode(x, node, child);
	}
}

void insertKey(DiskBTree *tree, KeyType key) {
	Result res;
	// 1. 查找key在B树的待插入位置
	searchBTree(tree, key, &res);
	if (res.tag == 1) {
		printf("key %d have exists!\n", key);
	} else {
		insertBTree(tree, key, res.ptr, res.pos);
		tree->count++;
	}
}

// ******************* B树的辅助函数 *******************//
void searchBTree(DiskBTree *tree, KeyType key, Result *res) {
	BTNode *cur = tree->root;				// 定义当前节点索引
	BTNode *pre = NULL;						// 定义指向父节点的索引
	int pos;
	int tag =  0;							// 标记是否找到
	while (cur && !tag) {
		// 遍历当前节点的所有key值，确定是否在这个节点上，
		// 如果不在这个节点，还要标记出下一个节点的位置
		pos = searchNodePos(cur, key);
		if (pos <= cur->keyNum && cur->key[pos] == key) {
			tag = 1;
		} else {
			pre = cur;
			cur = pre->ptr[pos - 1];
		}
	}
	if (tag) {					// 查找成功
		res->tag = 1;
		res->ptr = cur;
		res->pos = pos;
	} else {					// 查找失败，把父节点信息更新
		res->tag = 0;
		res->ptr = pre;
		res->pos = pos;
	}
}

void printBTree(const BTNode *node, int tab) {
	if (node == NULL) {
		return;
	}
	int i;
	for (i = 0; i <= tab; ++i) {
		printf("    ");
	}
	for (i = 1; i <= node->keyNum; ++i) {
		printf("%d", node->key[i]);
		if (i != node->keyNum) {
			printf(", ");
		}
	}
	printf("\n");
	for (i = 0; i <= node->keyNum; ++i) {
		printBTree(node->ptr[i], tab+1);
	}
}
// -----------------------------------------------------
// 向兄弟节点借关键字
static void borrowFromBrother(BTNode *node, BTNode *leftBrother, BTNode *rightBrother, BTNode *parent, int pos) {
	if (leftBrother && leftBrother->keyNum >= ((MaxOrder + 1) / 2)) {
		for (int i = node->keyNum; i > 0; --i) {
			// 关键字和指针后移，腾出第一个位置
			if (i > 1) {
				node->key[i] = node->key[i - 1];
			}
			node->ptr[i] = node->ptr[i - 1];
		}
		node->ptr[0] = leftBrother->ptr[leftBrother->keyNum];
		if (node->ptr[0]) {
			node->ptr[0]->parent = node;
		}
		leftBrother->ptr[leftBrother->keyNum] = NULL;
		node->key[1] = parent->key[pos];
		parent->key[pos] = leftBrother->key[leftBrother->keyNum];
		leftBrother->keyNum--;
		node->keyNum++;
	} else if (rightBrother && rightBrother->keyNum >= ((MaxOrder + 1) / 2)) {
		node->key[node->keyNum + 1] = parent->key[pos + 1];
		node->ptr[node->keyNum + 1] = rightBrother->ptr[0];
		if (node->ptr[node->keyNum + 1]) {
			node->ptr[node->keyNum + 1]->parent = node;
		}
		node->keyNum++;
		parent->key[pos + 1] = rightBrother->key[1];
		for (int i = 0; i < rightBrother->keyNum; ++i) {
			if (i > 0) {
				rightBrother->key[i] = rightBrother->key[i + 1];
			}
			rightBrother->ptr[i] = rightBrother->ptr[i + 1];
		}
		rightBrother->ptr[rightBrother->keyNum] = NULL;
		rightBrother->keyNum--;
	}
}
/* 与左兄弟合并 */
static void mergerWithLeftBrother(BTNode *leftBrother, BTNode *parent, BTNode *node, DiskBTree *tree, int pos) {
	// 与左兄弟合并
	leftBrother->key[leftBrother->keyNum + 1] = parent->key[pos];   // 从父节点拿下分割本节点与左兄弟的关键字
	leftBrother->ptr[leftBrother->keyNum + 1] = node->ptr[0];
	if (leftBrother->ptr[leftBrother->keyNum + 1]) {
		// 给左兄弟的节点，当此结点存在时需要把其父亲指向左节点
		leftBrother->ptr[leftBrother->keyNum + 1]->parent = leftBrother;
	}
	leftBrother->keyNum++;      // 左兄弟关键字加1
	for (int i = 1; i <= node->keyNum; ++i) {
		// 把本节点的关键字和子树指针赋给左兄弟
		leftBrother->key[leftBrother->keyNum + i] = node->key[i];
		leftBrother->ptr[leftBrother->keyNum + i] = node->ptr[i];
		if (leftBrother->ptr[leftBrother->keyNum + i]) {
			leftBrother->ptr[leftBrother->keyNum + i]->parent = leftBrother;
		}
	}
	leftBrother->keyNum += node->keyNum;
	parent->ptr[pos] = NULL;
	free(node);
	for (int j = pos; j < parent->keyNum; ++j) {    // 左移
		parent->key[j] = parent->key[j + 1];
		parent->ptr[j] = parent->ptr[j + 1];
	}
	parent->ptr[parent->keyNum] = NULL;
	parent->keyNum--;       // 父节点关键字个数减1
	if (tree->root == parent) {
		// 如果此时父节点为根，则当父节点没有关键字时才调整
		if (parent->keyNum == 0) {
			for (int i = 0; i <= parent->keyNum + 1; ++i) {
				if (parent->ptr[i]) {
					tree->root = parent->ptr[i];
					break;
				}
				tree->root->parent = NULL;
			}
		}
	} else {
		// 如果父节点不为根，则需要判断是否需要重新调整
		if (parent->keyNum < ((MaxOrder - 1) / 2)) {
			restoreBTree(tree, parent);
		}
	}
}

/* 与右兄弟合并 */
static void mergerWithRightBrother(BTNode *rightBrother, BTNode *parent, BTNode *node, DiskBTree *tree, int pos) {
	for (int i = rightBrother->keyNum; i > 0; --i) {
		if (i > 0) {
			rightBrother->key[i + 1 + node->keyNum] = rightBrother->key[i];
		}
		rightBrother->ptr[i + 1 + node->keyNum] = rightBrother->ptr[i];
	}
	rightBrother->key[node->keyNum + 1] = parent->key[pos + 1];     // 把父节点分割两个本兄弟和右兄弟的关键字拿下来使用
	for (int i = 0; i <= node->keyNum; ++i) {
		// 把本结点的关键字及子树指针移动到右兄弟中去
		if (i > 0) {
			rightBrother->key[i] = node->key[i];
		}
		rightBrother->ptr[i] = node->ptr[i];
		if (rightBrother->ptr[i]) {
			rightBrother->ptr[i]->parent = rightBrother;        // 给右兄弟的节点需要把其父节点指向右兄弟
		}
	}
	rightBrother->keyNum += (node->keyNum + 1);
	parent->ptr[pos] = NULL;
	free(node);
	for (int i = pos; i < parent->keyNum; ++i) {
		if (i > pos) {
			parent->key[i] = parent->key[i + 1];
		}
		parent->ptr[i] = parent->ptr[i + 1];
	}
	if (parent->keyNum == 1) {
		// 如果父结点在关键字减少之前只有一个结点，那么需要把父结点的右孩子赋值给左孩子
		parent->ptr[0] = parent->ptr[1];
	}
	parent->ptr[parent->keyNum] = NULL;
	parent->keyNum--;           // 父节点关键字数减1
	if (tree->root == parent) {
		//如果此时父结点为根，则当父结点没有关键字时才调整
		if (parent->keyNum == 0) {
			for (int i = 0; i <= parent->keyNum; ++i) {
				if (parent->ptr[i]) {
					tree->root = parent->ptr[i];
					break;
				}
			}
			tree->root->parent = NULL;
		}
	} else {
		// 如果父结点不为根，则需要判断是否需要重新调整
		if (parent->keyNum < ((MaxOrder - 1) / 2)) {
			restoreBTree(tree, parent);
		}
	}
}

// 调整B树
static void restoreBTree(DiskBTree *tree, BTNode *node) {
	BTNode *parent, *leftBrother, *rightBrother;
	parent = node->parent;
	if (parent) {
		// 寻找左右兄弟
		int i;
		for (i = 0; i <= parent->keyNum; ++i) {
			if (parent->ptr[i] == node) {
				break;
			}
		}
		if (i > 0) {
			leftBrother = parent->ptr[i - 1];
		} else {
			leftBrother = NULL;
		}
		if (i < parent->keyNum) {
			rightBrother = parent->ptr[i + 1];
		} else {
			rightBrother = NULL;
		}
		// 左兄弟或右兄弟有富余的关键字
		if (((leftBrother && leftBrother->keyNum >= (MaxOrder + 1) / 2)) ||
			(rightBrother && rightBrother->keyNum >= (MaxOrder + 1) / 2)){
			borrowFromBrother(node, leftBrother, rightBrother, parent, i);
		} else {
			// 左右兄弟都没有富余的关键字，需要合并
			if (leftBrother) {
				// 与左兄弟合并
				mergerWithLeftBrother(leftBrother, parent, node, tree, i);
			} else if (rightBrother) {
				mergerWithRightBrother(rightBrother, parent, node, tree, i);
			} else {
				// 左右子树都不存在，改变根节点
				for (int j = 0; j < node->keyNum; ++j) {
					if (node->ptr[j]) {
						tree->root = node->ptr[j];
						break;
					}
				}
				tree->root->parent = NULL;
			}
		}
	} else {
		BTNode *a;
		for (int i = 0; i <= node->keyNum; ++i) {
			if (node->ptr[i]) {
				a = node;
				node = node->ptr[i];
				a->ptr[i] = NULL;
				free(a);
				break;
			}
		}
		tree->root = node;
		tree->root->parent = NULL;
	}
}

// 找到node节点的后继节点，交换key值，把这个节点通过node反馈给上层
static void successor(BTNode **node, int pos) {
	BTNode *leaf = *node;
	if (leaf == NULL) {
		return;
	}
	leaf = leaf->ptr[pos];
	while (leaf->ptr[0]) {
		leaf = leaf->ptr[0];
	}
	(*node)->key[pos] = leaf->key[1];
	(*node) = leaf;
}

// 从节点node的pos位序中移除关键字key
static void removeNode(BTNode *node, int pos) {
	for (int i = pos; i < node->keyNum; ++i) {
		node->key[i] = node->key[i + 1];
		node->ptr[i] = node->ptr[i + 1];
	}
	node->keyNum--;
}

// 从tree中删除目标关键字所在node节点的pos位序上
static void deleteBTree(DiskBTree *tree, BTNode *node, int pos) {
	if (node->ptr[pos]) {		// 内部节点
		successor(&node, pos);
		deleteBTree(tree, node, 1);
	} else {
		// 从node节点中删除pos
		removeNode(node, pos);
		if (node->keyNum <= ((MaxOrder - 1) / 2)) {
			// 调整B树
			restoreBTree(tree, node);
		}
	}
}
/* B树的删除
 * 1. 找到节点
 * 2. 判断节点是否是叶子节点，如果不是，找后继(前驱)节点，替换节点后，转为删除这个前驱或后继节点(叶子节点)
 * 3. 最终都是删除这个叶子节点
 * 3.1 删除这个节点里的元素后，该节点的m是否小于临界值（m/2），如果不小于，成功返回
 * 3.2 先找兄弟，看兄弟的节点的m值是否有多余，有多余，接（接的人变父，原父下沉）
 * 3.3 兄弟没有结余，和父节点进行合并，重新再判断新的父节点关系
 * */
void deleteKey(DiskBTree *tree, KeyType key) {
	Result res;
	searchBTree(tree, key, &res);
	if (res.tag) {
		deleteBTree(tree, res.ptr, res.pos);
		tree->count--;
	} else {
		printf("key not exist!\n");
	}
}
