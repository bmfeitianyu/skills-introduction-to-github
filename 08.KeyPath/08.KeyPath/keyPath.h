#ifndef KEY_PATH_H
#define KEY_PATH_H
/* 关键路径是AOE网，边表示活动，顶点表示实践
 * 关键路径就是AOE网看做整个项目，完成整个项目至少需要多少时间？
 * 解决这个问题，关键在于从AOE网中，找到一条从起始点到结束点长度的最大值
 * */
#include "../02.AdjacentGraph/adjacentList.h"

void keyPath(AGraph *graph);
#endif
