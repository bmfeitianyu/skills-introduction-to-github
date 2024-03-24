#ifndef BASE_H
#define BASE_H
#define MaxNodeNum	10
#define INF 1E4
/* 图的边集数组 */
typedef struct {
	int begin;			// 边的起点（顶点1）
	int end;			// 边的终点（顶点2）
	int weight;
}EdgeSet;
#endif
