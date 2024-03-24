#ifndef KRUSKAL_H
#define KRUSKAL_H
#include "../base.h"
#include "../01.MatrixGraph/matrixGraph.h"
/* Kruskal算法
 * 从边的角度求图的最小生成树，更适合求边稀疏的图
 * 算法思路：
 * a. 将所有的边按照权值的大小进行升序排序，然后从小到大一一判断，判断条件：
 * 	1. 如果这个边不会与之前选择的所有边组成回路，就可以作为最小生成树的一部分；
 * 	2. 放置，舍去
 * b. 循环a，直到具有n个顶点的连通图筛选出n-1条边为止
 * 引入一个数据结构，边集数组，保存边和节点的关系
 * 简化版：从边集数组里，找最小的边，判断2个顶点会不会构成一个环，如果不够，加入结果
 * */

// 使用邻接矩阵表示了无向图，从邻接矩阵中初始化边集数组
int initEdgeSet(const MGraph *graph, EdgeSet *edges);
// 排序边集数组
void sortEdgeSet(EdgeSet *edges, int num);
// Kruskal算法
int KruskalMGraph(const MGraph *graph, const EdgeSet *edges, int num, EdgeSet *result);
#endif
