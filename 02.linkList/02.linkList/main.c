#include <stdio.h>
#include "linkList.h"

int main() {
	LinkList *link = createLinkList();
	if (link == NULL) {
		return -1;
	}
	// 插入节点
	for (int i = 0; i < 5; ++i) {	// 链表的倒序
		insertLinkList(link, 1, i+100);
	}
	showLinkList(link);
	printf("====================\n");
	deleteLinkList(link, 102);
	showLinkList(link);
	releaseLinkList(link);
	return 0;
}
