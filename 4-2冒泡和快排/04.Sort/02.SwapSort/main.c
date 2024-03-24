#include "bubbleSort.h"
#include "quickSort.h"

int main() {
	int n = 10000;
	SortTable *table1 = generateRandomArray(n, 0, n);
	SortTable *table2 = copySortTable(table1);
	SortTable *table3 = copySortTable(table1);

	testSort("quick Sort V1", quickSortV1, table1);
	testSort("quick Sort V2", quickSortV2, table2);
	testSort("Bubble Sort V3", bubbleSortV3, table3);

	releaseSortTable(table1);
	releaseSortTable(table2);
	releaseSortTable(table3);
	return 0;
}
