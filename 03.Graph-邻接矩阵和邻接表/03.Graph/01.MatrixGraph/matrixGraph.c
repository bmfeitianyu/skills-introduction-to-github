#include <string.h>
#include "matrixGraph.h"

int isEdge(int weight) {
	if (weight > 0 && weight < INF)
		return 1;
	return 0;
}

void initMGraph(MGraph *g, int num, char **names, int directed, int edgeValue) {
	g->directed = directed;
	g->edgeNum = 0;
	g->nodeNum = num;
	memset(g->vex, 0, sizeof(g->vex));
	memset(g->edges, 0, sizeof(MatrixEdge) * MaxNodeNum * MaxNodeNum);
	// 初始化顶点
	for (int i = 0; i < num; ++i) {
		g->vex[i].no = i;
		g->vex[i].show = names[i];
		for (int j = 0; j < num; ++j) {
			g->edges[i][j] = edgeValue;
		}
	}
}
// 简单图 不能有自环 不能有重边
void addMGraphEdge(MGraph *g, int x, int y, int w) {
	if (x < 0 || x > g->nodeNum)
		return;
	if (y < 0 || y > g->nodeNum)
		return;
	if (!isEdge(g->edges[x][y])) {
		g->edges[x][y] = w;
		if (g->directed == 0) {
			g->edges[y][x] = w;
		}
		g->edgeNum++;
	}
}
