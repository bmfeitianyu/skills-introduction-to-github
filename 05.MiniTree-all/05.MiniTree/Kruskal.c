#include <string.h>
#include <stdlib.h>
#include "Kruskal.h"

/* 邻接矩阵无向图，只需要上三角数据即可 */
int initEdgeSet(const MGraph *graph, EdgeSet *edges) {
	int k = 0;
	for (int i = 0; i < graph->nodeNum; ++i) {			// 遍历每个节点
		for (int j = i + 1; j < graph->nodeNum; ++j) {	// 遍历每个节点，所有的边，i+1，遍历上三角
			if (graph->edges[i][j] > 0) {
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = graph->edges[i][j];
				k++;
			}
		}
	}
	return k;
}
/* 按照边的权值从小到大进行排序
 * 冒泡方法，第i个元素和后面元素比较，如果后面的权值小，交换
 * 通过一次遍历，当前的i就是最小值
 * */
void sortEdgeSet(EdgeSet *edges, int num) {
	EdgeSet tmp;
	for (int i = 0; i < num; ++i) {
		for (int j = i + 1; j < num; ++j) {
			if (edges[j].weight < edges[i].weight) {
				memcpy(&tmp, &edges[i], sizeof(EdgeSet));
				memcpy(&edges[i], &edges[j], sizeof(EdgeSet));
				memcpy(&edges[j], &tmp, sizeof(EdgeSet));
			}
		}
	}
}

// 从并查集中，找a节点的根节点
static int getRoot(const int *uSet, int a) {
	while (a != uSet[a]) {
		a = uSet[a];
	}
	return a;
}

int KruskalMGraph(const MGraph *graph, const EdgeSet *edges, int num, EdgeSet *result) {
	int *uSet;
	int a;
	int b;
	int count = 0;
	int sum = 0;
	// 1. 初始化并查集，每一个节点的编号就是自己
	uSet = (int *) malloc(sizeof(int ) *graph->nodeNum);
	for (int i = 0; i < graph->nodeNum; ++i) {
		uSet[i] = i;
	}
	// 2. 从已经排序好的边集中，找到最小的边（顺序找），当这个边加入后，不构成闭环，就可以加入结果
	for (int i = 0; (count < (graph->nodeNum - 1)) && i < num; ++i) {
		a = getRoot(uSet, edges[i].begin);
		b = getRoot(uSet, edges[i].end);
		if (a != b) {				// 不构成闭环
			uSet[a] = b;
			result[count].begin = edges[i].begin;
			result[count].end = edges[i].end;
			result[count].weight = edges[i].weight;
			count++;
			sum += edges[i].weight;
		}
	}
	free(uSet);
	return sum;
}
