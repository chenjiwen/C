#ifndef __ALG_LIST_H__
#define __ALG_LIST_H__

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
#include "common.h"
	typedef int ListElemType;
	typedef int DListElemType;
	typedef struct LinkListNode
	{
		ListElemType elem;
		struct LinkListNode* next;
	}LinkListNodeT, *pLinkListNodeT, *pListNodeT;

	typedef struct DLinkListNode 
	{
		DListElemType elem;
		struct DLinkListNode* prev;
		struct DLinkListNode* next;
	}DLinkListNodeT, *pDLinkListNodeT, *pDListT;

	typedef struct polyNode {
		struct polyNode* next;
		int    coef;
		int    deg;

	}polyNodeT,*pPolyNodeT;

	struct LinkListNode* createListNode(ListElemType elem);
	void destroyLinkList(struct LinkListNode* head);
	struct LinkListNode* linkListFind(struct LinkListNode* head, ListElemType key);
	struct LinkListNode* linkListAddTail(struct LinkListNode* head, ListElemType elem);
	struct LinkListNode* linkListAddHead(struct LinkListNode* head, ListElemType elem);
	void linkListAdd(struct LinkListNode* toAdd, ListElemType elem);
	struct LinkListNode* linkListDel(struct LinkListNode* head, struct LinkListNode* toDel);
	struct LinkListNode* linkListRemoveHead(struct LinkListNode** head);
	void visitList(struct LinkListNode* head);
	struct LinkListNode* makeCircleList(struct LinkListNode* head, ListElemType elem);


	struct DLinkListNode* createDLLNode(DListElemType elem);
	struct DLinkListNode* DLListAdd(struct DLinkListNode* head, 
		                            struct DLinkListNode* pNode, 
		                            struct DLinkListNode* pToAdd);
	struct DLinkListNode* DLListDel(struct DLinkListNode* head, 
		                            struct DLinkListNode* pNode);
	struct DLinkListNode* DLListAddToTail(struct DLinkListNode* head,
		                                  struct DLinkListNode* pToAdd);
	struct DLinkListNode* DLListAddToHead(struct DLinkListNode* head,
		                                  struct DLinkListNode* pToAdd);
	void destroyDLinkList(struct DLinkListNode*);

#ifdef __cplusplus
}
#endif

#endif

