#ifndef DIJKSTRA_SHORT_PATH_H
#define DIJKSTRA_SHORT_PATH_H
#include "../01.MatrixGraph/matrixGraph.h"
/* 以start为源点，上层函数分配dist的数组，记录start为源点到其他节点的最短路径权值
 * 上层函数分配path数组，记录每个节点从哪个节点来访问到的，相当于这个顶点的父节点
 * */
void DijkstraMGraph(const MGraph *graph, int start, int dist[], int path[]);
/* 从path信息里打印出 start为源点到其他节点pos的最短路径*/
void showShortPath(const int path[], int num, int pos);
#endif