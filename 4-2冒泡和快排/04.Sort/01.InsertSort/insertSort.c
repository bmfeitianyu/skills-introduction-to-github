#include "insertSort.h"

void insertSortV1(SortTable *table) {
	for (int i = 1; i < table->length; ++i) {		// i 去遍历无序的区域
		// 每个无序区域里的值，不断的和前面元素进行交换
		Element e = table->data[i];
		int j;
		for (j = i; j > 0 && table->data[j - 1].key > e.key; --j) {
			swapElement(&table->data[j], &table->data[j - 1]);
		}
		table->data[j] = e;
	}
}
/* 1. 默认第一个元素就是有序，那么从第二个元素开始和前面有序的区域进行比较
 * 2. 待插入的元素i，和有序区域从后往前依次查找
 * 		若待插入元素 < 以有序区域的值，有序的区域的值后移一位
 * 		插入查找的位置[0...i-1]的位置
 * */
void insertSort(SortTable *table) {
	for (int i = 1; i < table->length; ++i) {
		if (table->data[i].key < table->data[i - 1].key) {
			// 用j辅助值来找到待插入元素的真正位置
			int j = i - 1;
			Element temp = table->data[i];
			// 查找索引从[0...i-1]的位置，只要待插入的值比插入位置还小，就继续查找
			while (j > -1 && temp.key < table->data[j].key) {
				table->data[j + 1]  = table->data[j];
				j--;
			}
			table->data[j + 1] = temp;
		}
		// 待插入的元素比之前有序区域值还大，那么此时的i位置就是这个元素插入的位置
	}
}

void shellSort(SortTable *table) {
	int gap;
	// gap为步长，每次减少一半
	for (gap = table->length / 2;  gap > 0; gap /= 2) {	// 对每个步长分别进行插入排序
		// 共gap个组，每一组都执行插入排序
		for (int i = gap; i < table->length; ++i) {
			Element temp = table->data[i];
			int j;
			for (j = i; j >= gap && table->data[j - gap].key > temp.key; j-=gap) {
				swapElement(&table->data[j], &table->data[j - gap]);
			}
			table->data[j] = temp;
		}
	}
}
