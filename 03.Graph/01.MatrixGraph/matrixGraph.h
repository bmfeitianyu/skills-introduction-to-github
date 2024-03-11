#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H
/* 图的邻接矩阵存储方式
 * - 描述顶点集合、边的集合
 * - 顶点用一维数组描述，边用二维数组表示
 * */
#include "../base.h"
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
/* 邻接矩阵图的初始化，初始化顶点集
 * num		:  顶点的个数
 * names	:  顶点显示的字符串，以字符指针来保存，上层空间他的值有效
 * directed :  是否是有向图
 * edgeValue:  初始化边的权值
 * */
void initMGraph(MGraph *g, int num, char *names[], int directed, int edgeValue);
/* 添加边的信息
 * x		:	起始顶点编号
 * y		:	终止顶点编号
 * w		:	该边的权值
 * */
void addMGraphEdge(MGraph *g, int x, int y, int w);

#endif
