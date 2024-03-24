#include <stdlib.h>
#include <stdio.h>
#include "Kruskal.h"

static void setupMGraph(MGraph *graph) {
	char *names[] = {"A", "B", "C", "D",
					 "E", "F", "G"};
	initMGraph(graph, sizeof(names)/ sizeof(names[0]), names, 0, 0);
	addMGraphEdge(graph, 0, 1, 12);
	addMGraphEdge(graph, 0, 5, 16);
	addMGraphEdge(graph, 0, 6, 14);
	addMGraphEdge(graph, 1, 2, 10);
	addMGraphEdge(graph, 1, 5, 7);
	addMGraphEdge(graph, 2, 3, 3);
	addMGraphEdge(graph, 2, 4, 5);
	addMGraphEdge(graph, 2, 5, 6);
	addMGraphEdge(graph, 3, 4, 4);
	addMGraphEdge(graph, 4, 5, 2);
	addMGraphEdge(graph, 4, 6, 8);
	addMGraphEdge(graph, 5, 6, 9);
}

int main() {
	MGraph graph;
	EdgeSet *edges;

	setupMGraph(&graph);
	edges = (EdgeSet *) malloc(sizeof(EdgeSet) * graph.edgeNum);

	int num = initEdgeSet(&graph, edges);
	printf("edgeSet num: %d\n", num);
	sortEdgeSet(edges, num);

	EdgeSet *result = (EdgeSet *) malloc(sizeof(EdgeSet) * (graph.nodeNum - 1));

	int sumW = KruskalMGraph(&graph, edges, num, result);
	printf("Kruskal sum of weight: %d\n", sumW);
	for (int i = 0; i < graph.nodeNum - 1; ++i) {
		printf("edge %d: [%s] --- <%d> --- [%s]\n", i + 1,
			   graph.vex[result[i].begin].show, result[i].weight, graph.vex[result[i].end].show);
	}
	free(edges);
	free(result);
	return 0;
}