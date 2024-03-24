#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crossLinkGraph.h"

CrossGraph *createCrossGraph(int n) {
	CrossGraph *graph = (CrossGraph *) malloc(sizeof(CrossGraph));
	graph->nodes = (CrossVertex *) malloc(sizeof(CrossVertex) * n);
	graph->numVertex = n;
	graph->numEdge = 0;
	return graph;
}

void releaseCrossGraph(CrossGraph *graph) {
	int numEdges = 0;
	if (graph) {
		if (graph->nodes) {
			for (int i = 0; i < graph->numVertex; ++i) {	// 遍历所有节点，释放出度
				ArcBox *box = graph->nodes[i].firstOut;
				ArcBox *tmp;
				while (box) {
					tmp = box;
					box = box->tailNext;
					free(tmp);
					numEdges++;
				}
			}
			printf("release %d edge!\n", numEdges);
			free(graph->nodes);
		}
		free(graph);
	}
}

void initCrossGraph(CrossGraph *graph, int num, char **names) {
	for (int i = 0; i < num; ++i) {
		graph->nodes[i].no = i;
		graph->nodes[i].show = names[i];
		graph->nodes[i].firstOut = graph->nodes[i].firstIn = NULL;
	}
}

void addCrossArc(CrossGraph *graph, int tail, int head, int w) {
	ArcBox *box = (ArcBox *) malloc(sizeof(ArcBox));
	box->weight = w;
	// 使用头插法，出度
	box->tailVertex = tail;
	box->tailNext = graph->nodes[tail].firstOut;
	graph->nodes[tail].firstOut = box;
	// 使用头插法，入度关系
	box->headVertex = head;
	box->headNext = graph->nodes[head].firstIn;
	graph->nodes[head].firstIn = box;
}

int inDegreeCrossGraph(CrossGraph *graph, int no) {
	int count = 0;
	ArcBox *box = graph->nodes[no].firstIn;
	while (box) {
		count++;
		box = box->headNext;
	}
	return count;
}

int outDegreeCrossGraph(CrossGraph *graph, int no) {
	int count = 0;
	ArcBox *box = graph->nodes[no].firstOut;
	while (box) {
		count++;
		box = box->tailNext;
	}
	return count;
}
