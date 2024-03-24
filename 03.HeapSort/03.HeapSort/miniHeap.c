#include <stdlib.h>
#include <string.h>
#include "miniHeap.h"
/* 满足节点的访问行为 [i/2, i, 2i, 2i+1] 根节点从1号索引进行存储 */
MiniHeap *createMiniHeap(int n) {
	MiniHeap *heap = (MiniHeap *) malloc(sizeof(MiniHeap));
	if (heap == NULL) {
		return NULL;
	}
	heap->data = (keyType *) malloc(sizeof(keyType) * (n + 1));
	if (heap->data == NULL) {
		return NULL;
	}
	memset(heap->data, 0, sizeof(keyType) * (n + 1));
	heap->capacity = n;
	heap->len = 0;				// 每次插入元素先加1，再插入
	heap->capacity = n;
	return heap;
}

void releaseMiniHeap(MiniHeap *heap) {
	if (heap) {
		if (heap->data) {
			free(heap->data);
			heap->data = NULL;
		}
		free(heap);
	}
}
// ---------------- 二叉堆的插入操作 --------------------
static void shiftUp(MiniHeap *heap, int k) {
	keyType tmp;
	while (k > 1 && heap->data[k / 2] > heap->data[k]) {
		tmp = heap->data[k];
		heap->data[k] = heap->data[k / 2];
		heap->data[k / 2] = tmp;
		k /= 2;
	}
}
/* 先在最后位置插入元素，然后通过上移操作，确定这个新元素的位置，保证每个根节点是子节点的最小值 */
void insertMiniHeap(MiniHeap *heap, keyType e) {
	if (heap->len + 1 > heap->capacity) {
		printf("MiniHeap space full!\n");
		return;
	}
	heap->data[++heap->len] = e;
	// 上移操作
	shiftUp(heap, heap->len);
}

static void shiftDown(MiniHeap *heap, int k) {
	keyType tmp;
	while (2 * k <= heap->len) {			// 保证有左孩子
		int index = 2 * k;
		if (index + 1 <= heap->len && heap->data[index + 1] < heap->data[index]) {
			index += 1;				// 如果有右孩子，右孩子和左孩子比一下，右小，那么假设要更新
		}
		if (heap->data[k] <= heap->data[index])
			break;
		// 发现当前值比左右孩子最小的值还要大
		tmp = heap->data[k];
		heap->data[k] = heap->data[index];
		heap->data[index] = tmp;
		k = index;
	}
}

/* 取出堆顶元素，把堆中的最后一个元素放到堆顶，根据原则下沉 */
keyType extractMiniHeap(MiniHeap *heap) {
	if (heap->len <= 0) {
		printf("No data!\n");
		return 0;
	}
	keyType ret = heap->data[1];
	heap->data[1] = heap->data[heap->len];
	heap->len--;
	shiftDown(heap, 1);
	return ret;
}

