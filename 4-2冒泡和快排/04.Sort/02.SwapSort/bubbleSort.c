#include "bubbleSort.h"

/* 找最大值，把最大的放到了右边
 * j [0, n-1)   j > j+1  swap
 * j [0, n-2)   j > j+1  swap
 * */
void bubbleSortV1(SortTable *table) {
	for (int i = 0; i < table->length; ++i) {
		for (int j = 0; j < table->length - i - 1; ++j) {
			if (table->data[j].key > table->data[j + 1].key) {
				swapElement(&table->data[j], &table->data[j+1]);
			}
		}
	}
}
/* 引入是否有序标记，当发现某一轮冒泡时有序，就退出循环*/
void bubbleSortV2(SortTable *table) {
	for (int i = 0; i < table->length; ++i) {
		int isSorted = 1;
		for (int j = 0; j < table->length - i - 1; ++j) {
			if (table->data[j].key > table->data[j + 1].key) {
				swapElement(&table->data[j], &table->data[j+1]);
				isSorted = 0;
			}
		}
		if (isSorted) {
			break;
		}
	}
}
/* 引入newIndex，标记最后一次交换的位置，下次冒泡排序是，只需要遍历到这个newIndex位置处 */
void bubbleSortV3(SortTable *table) {
	int newIndex;
	int n = table->length;
	do {
		newIndex = 0;
		for (int i = 0; i < n - 1; ++i) {
			if (table->data[i].key > table->data[i + 1].key) {
				swapElement(&table->data[i], &table->data[i + 1]);
				newIndex = i + 1;
			}
		}
		n = newIndex;
	} while (newIndex > 0);
}