#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef int Element;

/* 二分查找法
 * 数组空间有序，在闭区间搜索，就是不断的确定区间范围 [0...n-1]
 * 确定left和right的区间，定位mid值，根据mid值和待查找的值的关系来更新left或right
 * */
int binarySearch(const Element *arr, int n, Element target) {
	int left = 0;
	int right = n - 1;
	int mid;
	while (left <= right) {
		mid = left + (right - left) / 2;
		if (arr[mid] == target) {
			return mid;
		} else if (arr[mid] < target) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	return -1;
}

int normalSearch(const Element *arr, int n, Element target) {
	for (int i = 0; i < n; ++i) {
		if (arr[i] == target) {
			return i;
		}
	}
	return -1;
}

Element *generateOrderArray(int n) {
	Element *arr = (Element *) malloc(sizeof(Element) * n);
	if (arr == NULL) {
		return NULL;
	}
	for (int i = 0; i < n; ++i) {
		arr[i] = i;
	}
	return arr;
}

int main() {
	int n = 10000;
	Element *array = generateOrderArray(n);
	if (array == NULL) {
		return -1;
	}
	clock_t start = clock();
	for (int i = 0; i < n; ++i) {
		if(binarySearch(array, n, n + 10) != -1) {
			printf("binary search failed!\n");
		}
	}
	clock_t end = clock();
	printf("Time1 cost: %fs\n", (double )(end - start) / CLOCKS_PER_SEC);
	start = clock();
	for (int i = 0; i < n; ++i) {
		if(normalSearch(array, n, n + 10) != -1) {
			printf("binary search failed!\n");
		}
	}
	end = clock();
	printf("Time2 cost: %fs\n", (double )(end - start) / CLOCKS_PER_SEC);
	free(array);
	return 0;
}
