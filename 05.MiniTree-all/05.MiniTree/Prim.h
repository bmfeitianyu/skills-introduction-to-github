#ifndef PRIM_H
#define PRIM_H

#include "../01.MatrixGraph/matrixGraph.h"
/* Prim算法：
 * 动态维护一个所有激活顶点的边权值数组
 * 从图中任取一个顶点，激活这个顶点，发现相关的边
 * 1. 找到激活节点后，找其中最小的边，激活另外一个顶点
 * 2. 每激活一个顶点，更新这个权值数组，找里面最小的边
 * 3. 直到所有的顶点都激活
 * */
int PrimMGraph(MGraph *graph, int startV, EdgeSet *result);
#endif
