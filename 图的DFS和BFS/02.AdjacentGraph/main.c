#include "adjacentList.h"
#include <stdio.h>

static void setupGraph(AGraph *graph) {
	char *nodeNames[] = {"A", "B", "C", "D", "E"};
	initAGraph(graph, sizeof(nodeNames) / sizeof(nodeNames[0]),nodeNames, 1);
	addAGraphEdge(graph, 0, 4, 1);
	addAGraphEdge(graph, 0, 3, 1);
	addAGraphEdge(graph, 0, 1, 1);
	addAGraphEdge(graph, 1, 4, 1);
	addAGraphEdge(graph, 1, 2, 1);
	addAGraphEdge(graph, 2, 0, 1);
	addAGraphEdge(graph, 3, 2, 1);
}

int main() {
	int n = 5;
	AGraph *graph = createAGraph(n);
	setupGraph(graph);
	printf("边数: %d\n", graph->edgeNum);
	printf("图的深度遍历: ");
	DFSAGraphTravel(graph, 0);
	printf("\n图的广度遍历: ");
	resetAGraphVisited(graph);
	BFSAGraphTravel(graph, 0);
	printf("\n");
	releaseAGraph(graph);
	return 0;
}