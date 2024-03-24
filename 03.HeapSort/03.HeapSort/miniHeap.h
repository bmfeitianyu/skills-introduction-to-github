#ifndef MINI_HEAP_H
#define MINI_HEAP_H
/* 最小堆结构，使用完全二叉树来存储，使用顺序存储 */
#include "../sortHelper.h"
// 最小堆的结构
typedef struct {
	keyType *data;			// 用顺序存储动态保存堆的数据
	int len;				// 约束堆data域的长度
	int capacity;			// 最大容量
}MiniHeap;

// 产生n个元素的堆空间
MiniHeap *createMiniHeap(int n);
void releaseMiniHeap(MiniHeap *heap);
// 插入元素
void insertMiniHeap(MiniHeap *heap, keyType e);
// 提取元素
keyType extractMiniHeap(MiniHeap *heap);
#endif
