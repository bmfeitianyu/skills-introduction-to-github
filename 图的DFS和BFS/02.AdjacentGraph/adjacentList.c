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
	graph->visited = (int *) malloc(sizeof(int ) * n);
	if (graph->nodes == NULL || graph->visited == NULL) {
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
		free(graph->nodes);
		free(graph->visited);
		free(graph);
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

void visitAGraphNode(ArcNode *node) {
	printf("\t%s", node->show);
}

void DFSAGraphTravel(AGraph *graph, int v) {
	ArcEdge *p;
	// 先访问v节点，遍历v节点中的其他边的情况，找到下一个节点，再递进去
	graph->visited[v] = 1;
	visitAGraphNode(&graph->nodes[v]);
	p = graph->nodes[v].firstEdge;
	while (p) {
		if (graph->visited[p->no] == 0) {
			DFSAGraphTravel(graph, p->no);
		}
		p = p->next;
	}
}

void resetAGraphVisited(AGraph *graph) {
	if (graph && graph->visited) {
		memset(graph->visited, 0, sizeof(int ) * graph->nodeNum);
	}
}

void BFSAGraphTravel(AGraph *graph, int v) {
	int *que = (int *) malloc(sizeof(int ) * graph->nodeNum);
	int front = 0, rear = 0;
	int cur;
	ArcEdge *p;

	rear = (rear + 1) % graph->nodeNum;
	que[rear] = v;
	while (front != rear) {
		front = (front + 1) % graph->nodeNum;
		cur = que[front];
		visitAGraphNode(&graph->nodes[cur]);
		graph->visited[cur] = 1;

		p = graph->nodes[cur].firstEdge;
		while (p) {		// 把当前的任务都加入队列
			if (graph->visited[p->no] == 0) {
				rear = (rear + 1) % graph->nodeNum;
				que[rear] = p->no;
				graph->visited[p->no] = 1;
			}
			p = p->next;
		}
	}
	free(que);
}
