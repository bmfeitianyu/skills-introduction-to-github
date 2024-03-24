#include <stdlib.h>
#include <stdio.h>
#include "Prim.h"

int PrimMGraph(MGraph *graph, int startV, EdgeSet *result) {
	int *cost;				// 图中各顶点的权值数组，最小生成树中的最小代价
	int *mark;				// 图中的顶点激活状态
	int *visit;				// 定义从哪个顶点访问到这个顶点的，-1表示没有被访问
	int sum = 0;
	int min, k;

	cost = (int *) malloc(sizeof(int ) * graph->nodeNum);
	mark = (int *) malloc(sizeof(int ) * graph->nodeNum);
	visit = (int *) malloc(sizeof(int ) * graph->nodeNum);
	if (cost == NULL || mark == NULL || visit == NULL) {
		return 0;
	}
	// 1. 激活的第一个顶点，就是初始化，先初始化cost路径代价
	for (int i = 0; i < graph->nodeNum; ++i) {
		cost[i] = graph->edges[startV][i];
		mark[i] = 0;
		if (cost[i] < INF) {
			visit[i] = startV;
		} else {
			visit[i] = -1;
		}
	}
	mark[startV] = 1;
	// 2. 激活节点，添加到边集
	for (int i = 0; i < graph->nodeNum - 1; ++i) {		// 查找n-1个最小生成树的边
		// 从权值代价数组里，找到未激活节点的最小值和当前节点的编号
		min = INF;
		for (int j = 0; j < graph->nodeNum; ++j) {		// 从cost数组里找到未激活的顶点的最小值
			if (mark[j] == 0 && cost[j] < min) {
				min = cost[j];
				k = j;
			}
		}
		mark[k] = 1;					// 激活了最小值的节点
		result[i].begin = visit[k];		// 从哪里来
		result[i].weight = min;
		result[i].end = k;
		sum += min;
		// 3. 每激活一个顶点后，要更新cost和访问记录
		for (int j = 0; j < graph->nodeNum; ++j) {
			if (mark[j] == 0 && graph->edges[k][j] < cost[j]) {		// 激活的k节点比它原来cost还小，就更新
				cost[j] = graph->edges[k][j];
				visit[j] = k;
			}
		}
	}
	free(cost);
	free(mark);
	free(visit);
	return sum;
}
