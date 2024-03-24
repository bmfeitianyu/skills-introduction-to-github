#ifndef ADJACENT_LIST_H
#define ADJACENT_LIST_H
/* 图的邻接表，在节点集合中，增加指向边的指针
 * 边节点里包含了下一个和首节点连接的边
 * */
#include "../base.h"
// 边的结构
typedef struct arcEdge{
	int no;					// （从首节点）其他节点的编号
	int weight;				// 边的权重
	struct arcEdge *next;	// （从首节点）指向下一条边
}ArcEdge;
// 顶点结构
typedef struct {
	int no;					// 顶点的编号
	char *show;				// 顶点显示内容
	ArcEdge *firstEdge;		// 当前的顶点指向的边
}ArcNode;
// 使用邻接表描述的图
typedef struct {
	ArcNode *nodes;			// 图中顶点的集合
	int *visited;			// 图中顶点访问的标记
	int nodeNum;			// 图中顶点的个数
	int edgeNum;			// 图中边的个数
	int directed;			// 是否有向
}AGraph;
// 产生n个节点的邻接表的图
AGraph *createAGraph(int n);
void releaseAGraph(AGraph *graph);
/* 初始化邻接表的图
 * */
void initAGraph(AGraph *graph, int num, char *names[], int directed);
void addAGraphEdge(AGraph *graph, int x, int y, int w);
// 复位访问信息
void resetAGraphVisited(AGraph *graph);
// 访问节点
void visitAGraphNode(ArcNode *node);
// 深度搜索
void DFSAGraphTravel(AGraph *graph, int v);
// 广度搜索
void BFSAGraphTravel(AGraph *graph, int v);
#endif
