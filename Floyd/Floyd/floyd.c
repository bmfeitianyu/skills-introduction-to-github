#include <stdio.h>
#include "matrixGraph.h"

#define MAX_SIZE 20

static int dist[MAX_SIZE][MAX_SIZE];
static int path[MAX_SIZE][MAX_SIZE];

static void setupMGraph(MGraph *graph) {
	char *nodeNames[] = {"V0", "V1", "V2", "V3"};

	initMGraph(graph, sizeof(nodeNames) / sizeof(nodeNames[0]),
			   nodeNames, 1, INF);
	for (int i = 0; i < graph->nodeNum; ++i) {
		graph->edges[i][i] = 0;
	}
	addMGraphEdge(graph, 0, 1, 1);
	addMGraphEdge(graph, 0, 3, 4);
	addMGraphEdge(graph, 1, 2, 9);
	addMGraphEdge(graph, 1, 3, 2);
	addMGraphEdge(graph, 2, 0, 3);
	addMGraphEdge(graph, 2, 1, 5);
	addMGraphEdge(graph, 2, 3, 8);
	addMGraphEdge(graph, 3, 2, 6);
}

void shortPathFloyd(MGraph *graph) {
	// 初始化
	for (int i = 0; i < graph->nodeNum; ++i) {
		for (int j = 0; j < graph->nodeNum; ++j) {
			dist[i][j] = graph->edges[i][j];
			if (dist[i][j] < INF && i != j) {
				path[i][j] = i;
			} else {
				path[i][j] = -1;
			}
		}
	}
	// floyd
	for (int k = 0; k < graph->nodeNum; ++k) {      // k表示 从[0...n)之间节点分别激活
		for (int i = 0; i < graph->nodeNum; ++i) {  // k状态下第i行
			for (int j = 0; j < graph->nodeNum; ++j) {  // k状态下第i行中第j列
				if (dist[i][k] < INF && dist[k][j] < INF &&
				dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[k][j];
				}
			}
		}
	}
}

void printfPath(int i, int j) {
	if (i == j) {
		printf("%d ", i);
		return;
	}
	int k = path[i][j];
	printfPath(i, k);
	printf("%d ", j);
}

int main() {
	MGraph graph;

	setupMGraph(&graph);
	shortPathFloyd(&graph);
	for (int i = 0; i < graph.nodeNum; ++i) {
		for (int j = 0; j < graph.nodeNum; ++j) {
			printf("%d\t", dist[i][j]);
		}
		printf("\n");
	}
	printf("====================\n");
	for (int i = 0; i < graph.nodeNum; ++i) {
		for (int j = 0; j < graph.nodeNum; ++j) {
			printf("%d\t", path[i][j]);
		}
		printf("\n");
	}
	printf("====================\n");
	printfPath(1, 0);
	return 0;
}