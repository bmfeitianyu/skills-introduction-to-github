#include <string.h>
#include <stdio.h>
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

void visitMGraphNode(MatrixVertex *node) {
	printf("\t%s,", node->show);
}

// 记录是否访问的标记
static int MGraphVisited[MaxNodeNum];
void DFSMGraphTravel(MGraph *graph, int v) {
	visitMGraphNode(&graph->vex[v]);		// 访问v号节点
	MGraphVisited[v] = 1;
	// 从v号节点开始，通过邻接矩阵描述的边，找到一个未被访问的节点再进行DFS
	for (int i = 0; i < graph->nodeNum; ++i) {
		if (isEdge(graph->edges[v][i]) && MGraphVisited[i] == 0) {
			DFSMGraphTravel(graph, i);
		}
	}
}

void clearMGraphVisit() {
	memset(MGraphVisited, 0, sizeof(MGraphVisited));
}

/* 图的广度遍历
 * 初始化 ：一个队列（循环队列），把用户要访问的第一个节点放入队列
 * 循环执行任务：
 * 		队列不空，说明还有节点没有被访问，直到队列为空
 * 		循环判断队列为空
 * 		出队一个元素A，设置该元素A已经访问，将A的m个节点（未被访问）放入队列，设置为已访问状态
 * 			避免任务队列里已经有待处理的任务，而其他节点激活后，又放入到任务队列
 * 		继续循环
 * */
void BFSMGraphTravel(MGraph *graph, int v) {
	int que[MaxNodeNum];
	int rear = 0, front = 0;
	int cur;

	rear = (rear + 1) % MaxNodeNum;
	que[rear] = v;				// v放入任务队列
	while (front != rear) {
		// 出队
		front = (front + 1) % MaxNodeNum;
		cur = que[front];
		// 设置该节点以访问
		visitMGraphNode(&graph->vex[cur]);
		MGraphVisited[cur] = 1;
		for (int i = 0; i < graph->nodeNum; ++i) {
			if (isEdge(graph->edges[cur][i]) && MGraphVisited[i] == 0) {
				rear = (rear + 1) % MaxNodeNum;
				que[rear] = i;
				MGraphVisited[i] = 1;		// 防止重复任务
			}
		}
	}
}
