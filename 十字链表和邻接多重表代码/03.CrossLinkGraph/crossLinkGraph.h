#ifndef CROSS_LINK_GRAPH_H
#define CROSS_LINK_GRAPH_H
/* 十字链表的图表示法，将邻接表和逆邻接表整合在一个顶点描述的结构上
 * 方便查找图中出度和入度
 * */
// 十字链表的边的结构
typedef struct arcBox {
	int tailVertex;				// 弧尾编号，出度的信息
	struct arcBox *tailNext;	// 下一个弧尾，下一个出度
	int headVertex;				// 弧头编号，入度的信息
	struct arcBox *headNext;	// 下一个弧头，下一个入度
	int weight;					// 弧的权重
}ArcBox;
// 十字链表的顶点结构
typedef struct {
	int no;
	const char *show;
	ArcBox *firstIn;			// 该节点的入度
	ArcBox *firstOut;			// 该节点的出度
}CrossVertex;
// 十字链表的图结构
typedef struct {
	CrossVertex *nodes;
	int numVertex;
	int numEdge;
}CrossGraph;

// 产生n个节点的十字链表
CrossGraph *createCrossGraph(int n);
void releaseCrossGraph(CrossGraph *graph);
// 初始化图，设置节点信息
void initCrossGraph(CrossGraph *graph, int num, char *names[]);
// 添加边，从tail走向head
void addCrossArc(CrossGraph *graph, int tail, int head, int w);
// 计算no编号节点的入度
int inDegreeCrossGraph(CrossGraph *graph, int no);
// 计算no编号节点的出度
int outDegreeCrossGraph(CrossGraph *graph, int no);
#endif
