#ifndef QUICK_FIND_SET_H
#define QUICK_FIND_SET_H
#include "base.h"
/* 并查集的QuickFind算法下的结构定义
 * 每一个元素都存有一个编号，只要编号一样，就代表一个集团的人
 * 合并时，就是把另外一个团队的人的老大改为这个团队的老大
 * */
typedef struct {
	Element *data;				// 存放的具体数据，利用索引来建立数据的关系
	int n;						// 并查集的元素个数
	int *groupID;				// 每个元素的编号
}QuickFindSet;

QuickFindSet *createQuickFindSet(int n);		// 产生n个元素的并查集
void releaseQuickFindSet(QuickFindSet *setQF);	// 释放并查集
// 初始化并查集，设置元素值和对应的编号
void initQuickFindSet(QuickFindSet *setQF, const Element *data, int n);
// 查：判断两个元素是不是同一个组ID
int isSameQF(QuickFindSet *setQF, Element a, Element b);
// 并：合并两个元素
void unionQF(QuickFindSet *setQF, Element a, Element b);
#endif
