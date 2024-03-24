#ifndef QUICK_SORT_H
#define QUICK_SORT_H
#include "../sortHelper.h"
/* 快速排序:
 * 冒泡排序在每一轮中，只把1个元素冒泡到数组的一端
 * 1. 快速排序，在每一轮挑选一个基准元素，让其他比它大的元素移动到一边，比它小的移动到另外一边
 * 从而把表元素拆分成两个部分。
 * 2. 基准元素的选择
 * 随机选择一个元素作为基准元素，并让基准元素和第一个元素进行交换
 * 3. 元素交换
 * 分为双边循环法和单边循环法
 * */
void quickSortV1(SortTable *table);
void quickSortV2(SortTable *table);
#endif
