#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H

#define MaxNodeNum	10
#define INF 1E4
// 邻接矩阵图的顶点结构
typedef struct {
	int no;			// 顶点的编号
	char *show;		// 图中顶点的显示数据，指针指向了一个常量空间，考试时可以不用写
}MatrixVertex;
// 邻接矩阵边的类型，用int来描述，即可以描述权值和是否有边
typedef int MatrixEdge;
// 邻接矩阵表示的图
typedef struct {
	MatrixVertex vex[MaxNodeNum];			// 存储顶点的信息
	int	nodeNum;							// 约束实际顶点的数量，邻接矩阵遍历时的最大值
	MatrixEdge edges[MaxNodeNum][MaxNodeNum];		// 邻接矩阵定义边的情况
	int edgeNum;							// 定义边的个数
	int directed;							// 是否是有向图
}MGraph;

void initMGraph(MGraph *g, int num, char *names[], int directed, int edgeValue);
void addMGraphEdge(MGraph *g, int x, int y, int w);

#endif
