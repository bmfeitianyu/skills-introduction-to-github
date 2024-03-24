#ifndef SORT_HELPER_H
#define SORT_HELPER_H
#include <stdio.h>
#include <stdlib.h>

typedef int keyType;
typedef struct {
	keyType key;		// 查找表中每个数据元素的关键值
	void *data;			// 数据的其他区域
}Element;

typedef struct {
	Element *data;		// 存放查找表中数据元素的首地址
	int length;			// 查找表的元素个数
}SortTable;
enum sortStatus{success, failed};

void swapElement(Element *a, Element *b);					// 交换元素a和元素b
SortTable *generateRandomArray(int n, int low, int high);	// 产生随机数范围[low,high]
SortTable *generateLinearArray(int n, int swapTimes);		// 参数顺序空间，随机交换swapTimes次
SortTable *copySortTable(SortTable *old);					// 拷贝和old一样值的排序表
void releaseSortTable(SortTable *table);
// 排序算法函数的别名
typedef void (*sortHandler)(SortTable *);
// 测试sortName的排序算法
void testSort(const char *sortName, sortHandler sort, SortTable *table);
#endif
