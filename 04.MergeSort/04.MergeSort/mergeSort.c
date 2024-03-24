#include "mergeSort.h"

// merge合并
static void merge(SortTable *table, int left, int mid, int right) {
	// 1. 将左右任务的区域进行拷贝，方便从拷贝的空间里，按照归并的思想，向原空间填入有序的值
	int n1 = mid - left + 1;			// 左边的空间个数
	int n2 = right - mid;				// 右边的空间个数
	// 分配aux1和aux2
	Element *aux1 = (Element *) malloc(sizeof(Element) * n1);
	Element *aux2 = (Element *) malloc(sizeof(Element) * n2);
	if (aux1 == NULL || aux2 == NULL) {
		printf("aux malloc failed!\n");
		return;
	}
	// 将左右任务的子空间进行拷贝
	for (int i = 0; i < n1; ++i) {
		aux1[i] = table->data[left + i];
	}
	for (int i = 0; i < n2; ++i) {
		aux2[i] = table->data[mid + 1 + i];
	}
	// 2. 将有序的临时aux1和aux2的空间，进行归并
	int i = 0;			// 标记aux1区域当前最小值位置
	int j = 0;			// 标记aux2区域当前最小值位置
	int k = left;		// 最终存放结果的区域索引，就是table里的data
	while (i < n1 && j < n2) {
		if (aux1[i].key <= aux2[j].key) {
			table->data[k] = aux1[i++];
		} else {
			table->data[k] = aux2[j++];
		}
		k++;
	}
	// 把还有值的区域，填入到结果区域
	while (i < n1) {
		table->data[k++] = aux1[i++];
	}
	while (j < n2) {
		table->data[k++] = aux2[j++];
	}
	// 释放临时空间
	free(aux1);
	free(aux2);
}

// 设计一个通用的任务，在某一个区间内，完成归并算法
// 归并任务的访问区域[left...right]
static void mergeLoop(SortTable *table, int left, int right) {
	if (left >= right)
		return;
	// 拆成2个小任务
	int mid = (right - left) / 2 + left;
	mergeLoop(table, left, mid);
	mergeLoop(table, mid + 1, right);
	// 再进行合并任务
	merge(table, left, mid, right);
}

void mergeSort(SortTable *table) {
	mergeLoop(table, 0, table->length - 1);
}
