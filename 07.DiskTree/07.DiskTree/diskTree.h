#ifndef DISK_TREE_H
#define DISK_TREE_H
/* B树的阶3，说明最大有3棵子树，那么节点最大键值2
 * 在插入节点时，当键值为3时，才会触发分离，申请的时候多申请一个
 * | k0 | k1 | k2 | k3 |		k0是无效的  k3为了防止越界
 * | p0 | p1 | p2 | p3 |		p0 < k1   k1 < p1 < k2  p2 > k2  p3是不访问
 * */
#define MaxOrder 	3		// B树的阶
typedef int KeyType;		// B树节点键值类型
// B树的节点结构
typedef struct BTNode {
	KeyType key[MaxOrder + 1];			// [1 ... MaxOrder-1]
	struct BTNode *ptr[MaxOrder + 1];	// 0开始存入关系索引
	struct BTNode *parent;				// 指向父节点
	int keyNum;							// 该节点的键值数
}BTNode;
// B树的结构
typedef struct {
	BTNode *root;
	int count;
}DiskBTree;

/* B树查找的结果集，包含查找成功和失败的信息
 * ptr : 查找成功，标记当前键值所在的节点地址
 * 		 查找失败，标记待插入节点（NULL）的父节点
 * pos : 查找成功，标记键值所在节点的位序索引号
 * 		 查找失败，标记待插入节点（NULL）的父节点位序索引号
 * tag : 1表示查找成功，0表示查找失败
 * */
typedef struct {
	BTNode *ptr;
	int pos;
	int tag;
}Result;

DiskBTree *createDiskBTree();				// 初始化B树
void releaseDiskBTree(DiskBTree *tree);		// 释放B树
// 将key值插入到B树
void insertKey(DiskBTree *tree, KeyType key);
// 查找B树中key的位置，分查找成功和失败，更新res
void searchBTree(DiskBTree *tree, KeyType key, Result *res);
// B树的打印
void printBTree(const BTNode *node, int tab);
// B树的删除key
void deleteKey(DiskBTree *tree, KeyType key);
#endif
