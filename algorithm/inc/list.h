#ifndef __ALG_LIST_H__
#define __ALG_LIST_H__

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
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


	struct LinkListNode* createLinkList();
	struct LinkListNode* linkListFind(struct LinkListNode* head, ListElemType key);
	struct LinkListNode* linkListAddTail(struct LinkListNode* head, ListElemType elem);
	struct LinkListNode* linkListAddHead(struct LinkListNode* head, ListElemType elem);
	struct LinkListNode* linkListAdd(struct LinkListNode* head, 
		                             struct LinkListNode* toAdd, 
		                             ListElemType elem);
	struct LinkListNode* linkListDel(struct LinkListNode* head, 
		                             struct LinkListNode* toDel);


#ifdef __cplusplus
}
#endif

#endif

