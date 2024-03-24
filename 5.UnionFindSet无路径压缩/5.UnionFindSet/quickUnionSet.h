#ifndef QUICK_UNION_SET_H
#define QUICK_UNION_SET_H
/* QuickUnion方法
 * 每个元素只保存他的父元素的编号，通过不断找父元素，最终找到根编号
 * find : 两个元素的根一样
 * union : a元素的根 和 b元素的根 进行合并
 * */
#include "base.h"

typedef struct {
	Element *data;
	int n;
	int *parent;			// 每个元素只知道他的父节点，通过父节点不断去找根节点
	int *size;				// 根节点位置存放这个集合的个数
}QuickUnionSet;

QuickUnionSet *createQuickUnionSet(int n);
void releaseQuickUnionSet(QuickUnionSet *setQU);
void initQuickUnionSet(QuickUnionSet *setQU, const Element *data, int n);

int isSameQU(QuickUnionSet *setQU, Element a, Element b);
void unionQU(QuickUnionSet *setQU, Element a, Element b);
#endif
