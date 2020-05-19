#ifndef __ALG_LIST_H__
#define __ALG_LIST_H__

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
#include "common.h"
	typedef int ListElemType;
	typedef struct LinkListNode
	{
		ListElemType elem;
		struct LinkListNode* next;
	}LinkListNodeT, *pLinkListNodeT, *pListNodeT;

	typedef struct DLinkListNode 
	{
		ListElemType elem;
		struct DLinkListNode* prev;
		struct DLinkListNode* next;
	}DLinkListNodeT, *pDLinkListNodeT, *pDListNodeT;

	typedef struct polyNode {
		struct polyNode* next;
		int    coef;
		int    deg;

	}polyNodeT,*pPolyNodeT;

	struct LinkListNode* createLinkList();
	void destroyLinkList(struct LinkListNode* head);
	struct LinkListNode* linkListFind(struct LinkListNode* head, ListElemType key);
	struct LinkListNode* linkListAddTail(struct LinkListNode* head, ListElemType elem);
	struct LinkListNode* linkListAddHead(struct LinkListNode* head, ListElemType elem);
	void linkListAdd(struct LinkListNode* toAdd, ListElemType elem);
	struct LinkListNode* linkListDel(struct LinkListNode* head, struct LinkListNode* toDel);
	void visitList(struct LinkListNode* head);


	struct DLinkListNode* createDLinkList();
	void destroyDLinkList(struct DLinkListNode*);

#ifdef __cplusplus
}
#endif

#endif

