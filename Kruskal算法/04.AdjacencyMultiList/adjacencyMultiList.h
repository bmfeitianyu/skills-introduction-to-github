#ifndef ADJACENCY_MULTI_LIST_H
#define ADJACENCY_MULTI_LIST_H
/* 邻接多重表，使用于无向图，边的删除操作
 * 无向图如果用邻接表存储的话，一条边处理了2次，删除较为复杂
 * */
// 邻接多重表的边结构
typedef struct amlEdge {
	int iVex;				// 边的顶点i编号
	struct amlEdge *iNext;	// 顶点i编号的下一个边
	int jVex;
	struct amlEdge *jNext;
	int weight;
}MultiListEdge;
// 邻接多重表的顶点结构
typedef struct {
	int no;
	char *show;
	MultiListEdge *firstEdge;
}MultiListVertex;
// 邻接多重表
typedef struct {
	MultiListVertex *nodes;
	int vertexNum;
	int edgeNum;
}AdjacencyMultiList;

AdjacencyMultiList *createMultiList(int n);
void releaseMultiList(AdjacencyMultiList *graph);
void initMultiList(AdjacencyMultiList *graph, int n, char *names[]);
// 插入边
int insertMultiListEdge(AdjacencyMultiList *graph, int a, int b, int w);
// 删除边
int deleteMultiListEdge(AdjacencyMultiList *graph, int a, int b);
#endif
