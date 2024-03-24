#include "insertSort.h"

int main() {
	int n = 100000;	// 增大数字
	SortTable *table1 = generateRandomArray(n, 0, n);
	SortTable *table2 = copySortTable(table1);
	SortTable *table3 = copySortTable(table1);
	SortTable *table4 = generateLinearArray(n, 10);
	
	testSort("random insertSort: ", insertSortV1, table1);
	testSort("random insertSort: ", insertSort, table2);
	testSort("shell  insertSort: ", shellSort, table3);
	testSort("linear insertSort: ", insertSort, table4);
	releaseSortTable(table1);
	releaseSortTable(table2);
	releaseSortTable(table3);
	releaseSortTable(table4);
	return 0;
}