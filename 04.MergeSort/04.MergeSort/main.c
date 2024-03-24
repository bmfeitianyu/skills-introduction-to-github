#include "mergeSort.h"

int main() {
	int n = 100000;
	SortTable *table = generateRandomArray(n, 0, n);
	testSort("MergeSort: ", mergeSort, table);
	releaseSortTable(table);
	return 0;
}