#include "list.h"
#include <stdio.h>
#include <stdlib.h>

struct LinkListNode* createLinkList() {
	pLinkListNodeT pNode = NULL;

	pNode = (pLinkListNodeT)malloc(sizeof(LinkListNodeT));

	return pNode;
}

struct LinkListNode* createListNode(ListElemType elem) {
	pLinkListNodeT pNode = NULL;

	pNode = (pLinkListNodeT)malloc(sizeof(LinkListNodeT));
	if (pNode) {
		pNode->elem = elem;
		pNode->next = NULL;
	}

	return pNode;
}

struct LinkListNode* linkListFind(struct LinkListNode* head, ListElemType key) {
	pLinkListNodeT pNode = NULL;

	pNode = head;
	while (pNode && pNode->elem != key)
		pNode = pNode->next;

	return pNode;
}

struct LinkListNode* linkListAddTail(struct LinkListNode* head, ListElemType elem) {
	pLinkListNodeT pLastNode = NULL;

	pLastNode = head;

	while (pLastNode->next)
		pLastNode = pLastNode->next;

	pLastNode->next = createListNode(elem);

	return head;
}

struct LinkListNode* linkListAddHead(struct LinkListNode* head, ListElemType elem) {
	pLinkListNodeT pFirstNode = NULL;

	pFirstNode = head;

	head = createListNode(elem);
	head->next = pFirstNode;

	return head;
}


struct LinkListNode* linkListDel(struct LinkListNode* head,
	                             struct LinkListNode* toDel) {
	struct LinkListNode* pNode = NULL;

	pNode = head;
	if (toDel == head)
	{
		pNode = head->next;
		free(head);
		return pNode;
	}

	while (pNode->next != toDel)
		pNode = pNode->next;

	pNode->next = toDel->next;
	free(toDel);

	return head;
}