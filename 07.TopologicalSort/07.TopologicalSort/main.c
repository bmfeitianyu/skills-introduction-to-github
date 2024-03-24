#include <stdio.h>
#include "topologicalSort.h"

AGraph *setupAGraph1() {
	char *names[] = {"0", "1", "2", "3",
					 "4", "5", "6"};
	int n = sizeof(names) / sizeof(names[0]);
	AGraph *graph = createAGraph(n);
	if (graph == NULL) {
		return NULL;
	}
	initAGraph(graph, n, names, 1);
	addAGraphEdge(graph, 0, 1, 1);
	addAGraphEdge(graph, 0, 2, 1);
	addAGraphEdge(graph, 0, 3, 1);
	addAGraphEdge(graph, 1, 2, 1);
	addAGraphEdge(graph, 1, 4, 1);
	addAGraphEdge(graph, 2, 4, 1);
	addAGraphEdge(graph, 2, 5, 1);
	addAGraphEdge(graph, 3, 5, 1);
	addAGraphEdge(graph, 4, 6, 1);
	addAGraphEdge(graph, 5, 4, 1);
	addAGraphEdge(graph, 5, 6, 1);
	return graph;
}

AGraph *setupAGraph2() {
	char *names[] = {"A", "B", "C", "D", "E"};
	int n = sizeof(names) / sizeof(names[0]);
	AGraph *graph = createAGraph(n);
	if (graph == NULL) {
		return NULL;
	}
	initAGraph(graph, n, names, 1);
	addAGraphEdge(graph, 0, 1, 1);
	addAGraphEdge(graph, 0, 2, 1);
	addAGraphEdge(graph, 1, 3, 1);
	addAGraphEdge(graph, 2, 4, 1);
	addAGraphEdge(graph, 3, 4, 1);
	addAGraphEdge(graph, 4, 1, 1);
	return graph;
}

int main() {
	AGraph *graph1 = setupAGraph2();
	int result = TopologicalSort(graph1);
	printf("\nresult is %d\n", result);
	releaseAGraph(graph1);
	return 0;
}