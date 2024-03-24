#include <stdio.h>
#include "matrixGraph.h"

static void setupMatrixGraph(MGraph *g1) {
	char *nodeNames[] = {"V1", "V2", "V3", "V4",
						 "V5", "V6", "V7", "8"};
	initMGraph(g1, 8, nodeNames, 0, 0);
	addMGraphEdge(g1, 0, 1, 1);
	addMGraphEdge(g1, 0, 2, 1);
	addMGraphEdge(g1, 1, 3, 1);
	addMGraphEdge(g1, 1, 4, 1);
	addMGraphEdge(g1, 2, 5, 1);
	addMGraphEdge(g1, 2, 6, 1);
	addMGraphEdge(g1, 3, 7, 1);
	addMGraphEdge(g1, 4, 7, 1);
	addMGraphEdge(g1, 5, 6, 1);
}

int main() {
	MGraph g1;
	setupMatrixGraph(&g1);

	printf("have %d num!\n", g1.edgeNum);
	return 0;
}