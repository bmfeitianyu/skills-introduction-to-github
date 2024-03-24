#include "keyPath.h"

static AGraph *setupAGraph() {
	char *names[] = {"V0", "V1", "V2", "V3",
					 "V4", "V5", "V6", "V7",
					 "V8"};
	int n = sizeof(names)/ sizeof(names[0]);
	AGraph *graph = createAGraph(n);
	initAGraph(graph, n, names, 1);
	addAGraphEdge(graph, 0, 1, 6);
	addAGraphEdge(graph, 0, 2, 4);
	addAGraphEdge(graph, 0, 3, 5);
	addAGraphEdge(graph, 1, 4, 1);
	addAGraphEdge(graph, 2, 4, 1);
	addAGraphEdge(graph, 3, 5, 2);
	addAGraphEdge(graph, 4, 6, 9);
	addAGraphEdge(graph, 4, 7, 7);
	addAGraphEdge(graph, 5, 7, 4);
	addAGraphEdge(graph, 6, 8, 2);
	addAGraphEdge(graph, 7, 8, 4);
	return graph;
}

int main() {
	AGraph *graph = setupAGraph();
	keyPath(graph);
	releaseAGraph(graph);
	return 0;
}