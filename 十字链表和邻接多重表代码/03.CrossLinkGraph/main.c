#include <stdio.h>
#include "crossLinkGraph.h"

static void setupGraph(CrossGraph *graph) {
	char *nodeName[] = {"V0", "V1", "V2", "V3"};
	initCrossGraph(graph, sizeof(nodeName) / sizeof(nodeName[0]), nodeName);
	addCrossArc(graph, 0, 3, 1);
	addCrossArc(graph, 1, 0, 1);
	addCrossArc(graph, 1, 2, 1);
	addCrossArc(graph, 2, 0, 1);
	addCrossArc(graph, 2, 1, 1);
}

int main() {
	int n = 4;
	CrossGraph *graph = createCrossGraph(n);
	if (graph == NULL) {
		return -1;
	}
	setupGraph(graph);
	printf("V0的入度为: %d\n", inDegreeCrossGraph(graph, 0));
	printf("V0的出度为: %d\n", outDegreeCrossGraph(graph, 0));
	releaseCrossGraph(graph);
	return 0;
}