#include <stdlib.h>
#include <stdio.h>
#include "linkList.h"

LinkList *createLinkList() {
	LinkList *link = (LinkList *) malloc(sizeof(LinkList));
	if (link == NULL) {
		printf("malloc failed!\n");
		return NULL;
	}
	link->head.ele = 0x88;
	link->head.next = NULL;
	link->len = 0;
	return link;
}

void releaseLinkList(LinkList *linkList) {
	int cnt = 0;
	if (linkList) {
		// 遍历链表里的每个元素，依次释放 头删法
		Node *node = &linkList->head;
		while (node->next) {
			Node *tmp = node->next;
			node->next = tmp->next;
			free(tmp);
			cnt++;
		}
		printf("release %d node!\n", cnt);
		free(linkList);
	}
}

/* pos [1 2 3 ... link->len + 1]*/
int insertLinkList(LinkList *linkList, int pos, Element e) {
	if (pos < 1 || pos > linkList->len + 1) {
		printf("insert pos invalid!\n");
		return -1;
	}
	// 找到pos - 1的位置，进行插入操作
	int cnt = 0;
	Node *tmp = &linkList->head;
	while (tmp && cnt < (pos - 1)) {
		tmp = tmp->next;
		cnt++;
	}
	// tmp指向了待插入位置的前一个节点
	Node *new_node = (Node *)malloc(sizeof(Node));
	if (new_node == NULL) {
		printf("malloc node failed!\n");
		return -1;
	}
	new_node->ele = e;
	new_node->next = tmp->next;
	tmp->next = new_node;
	linkList->len = linkList->len + 1;
	return 0;
}

void showLinkList(LinkList *linkList) {
	Node *node = linkList->head.next;
	while (node) {
		printf("%d\t", node->ele);
		node = node->next;
	}
	printf("\n");
}

int deleteLinkList(LinkList *linkList, Element e) {
	// 找到e元素的前一个位置
	Node *node = &linkList->head;
	while (node && node->next->ele != e) {
		node = node->next;
	}
	if (node == NULL) {
		printf("not find!\n");
		return -1;
	}
	// 利用删除的备份思想
	Node *tmp = node->next;
	node->next = tmp->next;
	free(tmp);
	linkList->len--;
	return 0;
}
