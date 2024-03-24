#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "keyPath.h"

/* 通过拓扑排序计算出ETV，将拓扑排序的结果倒序来计算LTV
 * stack: 更新入度记录表
 * topOut: 拓扑排序的输出结果，此结果出栈，就可以算出从汇点反向计算LTV
 * */
static int topologicalOrder(AGraph *graph, int *ETV, int *LTV) {
	int *stack, *topOut;
	int top = -1;
	int *inDegree = (int *) malloc(sizeof(int ) * graph->nodeNum);

	// 1. 初始化图中顶点的入度记录表
	for (int i = 0; i < graph->nodeNum; ++i) {
		if (graph->nodes[i].firstEdge) {
			// 当该顶点有边时，统计这个对应的节点入度信息
			ArcEdge *edge = graph->nodes[i].firstEdge;
			while (edge) {
				++inDegree[edge->no];
				edge = edge->next;
			}
		}
	}
	// 2. 将入度为0的节点入栈，出栈就判断是否更新ETV
	stack = (int *) malloc(sizeof(int ) * graph->nodeNum);
	topOut = (int *) malloc(sizeof(int ) * graph->nodeNum);
	// 2.1 将初始化的入度为0的顶点压入栈
	for (int i = 0; i < graph->nodeNum; ++i) {
		if (inDegree[i] == 0) {
			stack[++top] = i;
			break;				// 关键路径，源点只有1个
		}
	}
	// 2.2 不断弹栈，更新入度记录表
	int tmp;
	int index = 0;			// topOut的栈顶索引
	while (top != -1) {
		tmp = stack[top--];
		topOut[index++] = tmp;
		ArcEdge *edge = graph->nodes[tmp].firstEdge;
		while (edge) {
			--inDegree[edge->no];
			if (inDegree[edge->no] == 0) {			// 更新入度表
				stack[++top] = edge->no;
			}
			// 更新ETV
			if (ETV[tmp] + edge->weight > ETV[edge->no]) {
				ETV[edge->no] = ETV[tmp] + edge->weight;
			}
			edge = edge->next;
		}
	}
	// 此时tmp指向了汇点
	free(inDegree);
	free(stack);
	if (index < graph->nodeNum) {		// 说明有环
		free(topOut);
		return -1;
	}
	// 3. 更新LTV
	// 初始化LTV值
	for (int i = 0; i < graph->nodeNum; ++i) {
		LTV[i] = ETV[tmp];
	}
	int getTopNo;
	while (index) {
		getTopNo = topOut[--index];
		ArcEdge *edge = graph->nodes[getTopNo].firstEdge;
		while (edge) {
			// 后一个节点LTV减去入度边的权值，和前一个节点最晚发生事件比较
			if (LTV[edge->no] - edge->weight < LTV[getTopNo]) {
				LTV[getTopNo] = LTV[edge->no] - edge->weight;
			}
			edge = edge->next;
		}
	}
	free(topOut);
	return 0;
}

static void showTable(int *table, int n, const char *name) {
	printf("%s", name);
	for (int i = 0; i < n; ++i) {
		printf("\t%d", table[i]);
	}
	printf("\n");
}

/* 为了求出AOE网中的关键路径，需要统计4个数据：
 * 对于AOE网中顶点有两个时间：
 * ETV : 事件最早发生时间		LTV : 事件最晚发生时间
 * 对于边来说，也有两个时间：
 * ETE : 活动最早发生时间		LTE : 活动最晚发生时间
 * 方法：
 * 对于所有的边来说，它的最早发生时间等于最晚发生时间，这条边就表示为关键路径
 * */
void keyPath(AGraph *graph) {
	// 1. 计算顶点的ETV和LTV
	int *ETV = (int *) malloc(sizeof(int ) * graph->nodeNum);
	int *LTV = (int *) malloc(sizeof(int ) * graph->nodeNum);
	if (ETV == NULL || LTV == NULL) {
		return;
	}
	memset(ETV, 0, sizeof(int ) * graph->nodeNum);
	memset(LTV, 0, sizeof(int ) * graph->nodeNum);
	// 2. 填充ETV和LTV
	topologicalOrder(graph, ETV, LTV);
	showTable(ETV, graph->nodeNum, "ETV: ");
	showTable(LTV, graph->nodeNum, "LTV: ");
	// 3. 计算ETE和LTE
	for (int i = 0; i < graph->nodeNum; ++i) {
		ArcEdge *edge = graph->nodes[i].firstEdge;
		while (edge) {
			// 每个边的最早发生时间就是边的弧尾的ETV
			// 每个边的最晚发生时间就是边的弧头的LTV 减去 当前边的权值
			if (ETV[i] == LTV[edge->no] - edge->weight) {
				printf("<%s> ---%d--- <%s>\n",
					   	graph->nodes[i].show, edge->weight, graph->nodes[edge->no].show);
			}
			edge = edge->next;
		}
	}
	free(ETV);
	free(LTV);
}
