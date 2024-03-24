#include "avlTree.h"
AVLTree *createAVLTree() {
	AVLTree *tree = (AVLTree *) malloc(sizeof(AVLTree));
	if (tree == NULL) {
		fprintf(stderr, "tree malloc failed!\n");
		return NULL;
	}
	tree->count = 0;
	tree->root = NULL;
	return tree;
}

static void freeNode(AVLTree *tree, AVLNode *node) {
	if (node) {
		freeNode(tree, node->left);
		freeNode(tree, node->right);
		free(node);
		tree->count--;
	}
}

void releaseAVLTree(AVLTree *tree) {
	if (tree) {
		freeNode(tree, tree->root);			// 后序递归释放节点
		printf("AVLTree have %d node!\n", tree->count);
		free(tree);
	}
}

/* 访问平衡二叉树节点，显示内容和此节点的高度 */
void visitAVLNode(AVLNode *node) {
	if (node) {
		printf("\t<%d:%d>", node->data, node->height);
	}
}
/* 递归中序遍历 */
static void inOrderAVLNode(AVLNode *node) {
	if (node) {
		inOrderAVLNode(node->left);
		visitAVLNode(node);
		inOrderAVLNode(node->right);
	}
}

void inOrderAVLTree(AVLTree *tree) {
	if (tree) {
		inOrderAVLNode(tree->root);
		printf("\n");
	}
}

static int maxNum(int a, int b) {
	return (a > b) ? a : b;
}
static int h(AVLNode *node) {
	if (node == NULL)
		return 0;
	else
		return node->height;
}
/* 左旋操作
 *     px
 *     |
 *     x
 *   /  \
 * lx    y
 *      / \
 *     ly ry
 * */
static AVLNode *leftRotate(AVLNode *x) {
	AVLNode *y = x->right;
	x->right = y->left;
	y->left = x;
	// 因为是平衡树，要更新x y的高度
	x->height = maxNum(h(x->left), h(x->right)) + 1;
	y->height = maxNum(h(y->left), h(y->right)) + 1;
	return y;
}

/* 右旋操作
 *       py
 *       |
 *       y
 *     /  \
 *    x   ry
 *   / \
 * lx  rx
 * */
AVLNode *rightRotate(AVLNode *y) {
	AVLNode *x = y->left;
	y->left = x->right;
	x->right = y;
	x->height = maxNum(h(x->left), h(x->right)) + 1;
	y->height = maxNum(h(y->left), h(y->right)) + 1;
	return x;
}

static int getBalance(AVLNode *node) {
	if (node == NULL)
		return 0;
	return h(node->left) - h(node->right);
}

static AVLNode *createAVLNode(Element e) {
	AVLNode *node = (AVLNode *) malloc(sizeof(AVLNode));
	if (node == NULL) {
		return NULL;
	}
	node->left = node->right = NULL;
	node->height = 1;
	node->data = e;
	return node;
}

static AVLNode *insertAVLNode(AVLTree *tree, AVLNode *node, Element e) {
	if (node == NULL) {		// 递归中递的边界条件
		tree->count++;
		return createAVLNode(e);
	}
	// 1. 递归找到插入 BST
	if (e < node->data) {
		node->left = insertAVLNode(tree, node->left, e);
	} else if (e > node->data) {
		node->right = insertAVLNode(tree, node->right, e);
	} else {			// 插入的元素，已经在AVL树中存在
		return node;
	}
	// 2. 归的过程中，更新归中节点的高度
	node->height = 1 + maxNum(h(node->left), h(node->right));
	// 计算这个节点的平衡因子
	int balance = getBalance(node);
	// 3. 判断平衡因子 left - right  > 1  L   < 1 R
	// 4. 调节 ，判断LL LR   RR RL
	if (balance > 1) {			// 失衡节点的左边高度比较大		L
		// 跟失衡节点的子节点判断下一步是L还是R
		if (e > node->left->data) {		// LR
			// 把LR中 把R进行左旋，转成LL状态
			node->left = leftRotate(node->left);
		}
		return rightRotate(node);		// LL
	} else if (balance < -1) {					//  右边高度大了  R
		if (e < node->right->data) {		// L
			node->right = rightRotate(node->right);
		}
		return leftRotate(node);		// RR
	}
	return node;				// 不需要调整，直接返回这个节点(归)
}

void insertAVLTree(AVLTree *tree, Element e) {
	if (tree) {
		tree->root = insertAVLNode(tree, tree->root, e);
	}
}

static AVLNode *deleteAVLNode(AVLTree *tree, AVLNode *node, Element e) {
	AVLNode *tmp;
	if (node == NULL) {			// 递到空位置，都没有进入到else
		return NULL;
	}
	// 1. 找到要删除点，按照二分搜索树的规则，删除
	if (e < node->data) {
		node->left = deleteAVLNode(tree, node->left, e);
	} else if (e > node->data) {
		node->right = deleteAVLNode(tree, node->right, e);
	} else {		// 2. 找到了这个节点
		if (node->left == NULL || node->right == NULL) {
			tmp = node->left ? node->left : node->right;
			if (tmp == NULL) {				// 度为0，直接删除node，归NULL
				free(node);
				tree->count--;
				return NULL;
			} else {						// 度为1，本身删除node，改为删除tmp，把tmp的关系拷贝到node上
				// node->data = tmp->data;
				// node->left = tmp->left;
				// node->right = tmp->right;
				// free(tmp);
				// tree->count--;
				free(node);
				return tmp;
			}
		} else {							// 找前驱节点，然后更新这个点，转为删除前驱点
			tmp = node->left;
			while (tmp->right) {
				tmp = tmp->right;
			}
			node->data = tmp->data;
			node->left = deleteAVLNode(tree, node->left, tmp->data);
		}
	}
	// 2. 更新平衡因子
	node->height = 1 + maxNum(h(node->left), h(node->right));
	int balance = getBalance(node);
	if (balance > 1) {								// L
		if (getBalance(node->left) < 0) {	// R
			node->left = leftRotate(node->left);
		}
		return rightRotate(node);
	} else if (balance < -1) {						// R
		if (getBalance(node->right) > 0) {	// L
			node->right = rightRotate(node->right);
		}
		return leftRotate(node);
	}
	return node;
}

/* 从平衡二叉树中删除元素e
 * 1. 按照二叉搜索树的规则，递归找到元素e所在节点
 * 2. 判断这个节点的度
 * 		2.1 如果是度为1，用父节点接收存在的子树
 * 		2.2 如果是度为0，直接删除，父节点接收一个NULL指针
 * 		2.3 如果是度为2，找到这个节点的前驱或者后继节点，用这个节点的值替换度为2的点
 * 			转成删除前驱或者后继这个节点
 * 3. 归的过程中，找失衡点
 * 4. 又根据LL LR  RL RR的规则，进行旋转
 * */
void deleteAVLTree(AVLTree *tree, Element e) {
	if (tree) {
		tree->root = deleteAVLNode(tree, tree->root, e);
	}
}

