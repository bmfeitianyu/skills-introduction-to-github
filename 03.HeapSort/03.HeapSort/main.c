#include "miniHeap.h"
#include "heapSort.h"

void test01() {
	int data[] = {9, 3, 7, 6, 5, 1, 10, 2};
	int n = 20;
	MiniHeap *miniHeap = createMiniHeap(n);
	for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
		insertMiniHeap(miniHeap, data[i]);
	}
	printf("array: ");
	for (int i = 1; i <= miniHeap->len; ++i) {
		printf("\t%d", miniHeap->data[i]);
	}
	printf("\nextra: ");
	// for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
	// 	printf("\t%d", extractMiniHeap(miniHeap));
	// }
	keyType tmp = extractMiniHeap(miniHeap);
	while (tmp) {
		printf("\t%d", tmp);
		tmp = extractMiniHeap(miniHeap);
	}
	releaseMiniHeap(miniHeap);
}
// 随机排序表的堆排序测试
void test02() {
	int n = 1000000;
	SortTable *table = generateRandomArray(n, 0, n);
	testSort("HeapSort: ", miniHeapSort, table);
	releaseSortTable(table);
}

int main() {
	test02();
	return 0;
}
