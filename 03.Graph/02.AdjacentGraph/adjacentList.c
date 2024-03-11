#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "adjacentList.h"

AGraph *createAGraph(int n) {
	AGraph *graph = (AGraph *) malloc(sizeof(AGraph));
	if (graph == NULL) {
		fprintf(stderr, "malloc failed!\n");
		return NULL;
	}
	graph->edgeNum = 0;
	graph->nodeNum = n;
	graph->nodes = (ArcNode *) malloc(sizeof(ArcNode) * n);
	if (graph->nodes == NULL) {
		fprintf(stderr, "malloc node failed!\n");
		free(graph);
		return NULL;
	}
	// 初始化链表
	memset(graph->nodes, 0, sizeof(ArcNode) * n);
	return graph;
}

void releaseAGraph(AGraph *graph) {
	ArcEdge *tmp;
	int count = 0;
	if (graph) {
		for (int i = 0; i < graph->nodeNum; ++i) {	// 遍历每一个节点
			ArcEdge *edge = graph->nodes[i].firstEdge;
			while (edge) {
				tmp = edge;
				edge = edge->next;
				free(tmp);
				count++;
			}
		}
		printf("release %d edges!\n", count);
	}
}

void initAGraph(AGraph *graph, int num, char **names, int directed) {
	graph->directed = directed;
	for (int i = 0; i < num; ++i) {			// 为数组空间的num个顶点进行初始化
		graph->nodes[i].no = i;
		graph->nodes[i].show = names[i];
		graph->nodes[i].firstEdge = NULL;
	}
}

static ArcEdge *createArcEdge(int y, int w) {
	ArcEdge *edge = (ArcEdge *) malloc(sizeof(ArcEdge));
	edge->no = y;
	edge->weight = w;
	edge->next = NULL;
	return edge;
}

void addAGraphEdge(AGraph *graph, int x, int y, int w) {
	if (x < 0 || x >= graph->nodeNum || y < 0 || y >= graph->nodeNum)
		return;
	// 边节点采用头插法
	if (x == y)
		return;

	ArcEdge *edge = createArcEdge(y, w);
	edge->next = graph->nodes[x].firstEdge;
	graph->nodes[x].firstEdge = edge;
	graph->edgeNum++;
	if (graph->directed == 0) {		// 不是自环边，并且是无向图
		edge = createArcEdge(x, w);
		edge->next = graph->nodes[y].firstEdge;
		graph->nodes[y].firstEdge = edge;
		graph->edgeNum++;
	}
}
