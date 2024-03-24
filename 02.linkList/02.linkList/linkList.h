#ifndef LINKLIST_H
#define LINKLIST_H
/* 单向链表，带头节点的表头 */
// 节点
typedef int Element;
typedef struct node {
	Element ele;
	struct node *next;
}Node;
// 表头
typedef struct {
	Node head;
	int len;
}LinkList;

LinkList *createLinkList();
void releaseLinkList(LinkList *linkList);

// 插入节点
int insertLinkList(LinkList *linkList, int pos, Element e);
// 删除节点
int deleteLinkList(LinkList *linkList, Element e);

// 打印链表
void showLinkList(LinkList *linkList);
#endif
