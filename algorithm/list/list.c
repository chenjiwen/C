#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

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

	if (!head)
		return createListNode(elem);

	while (pLastNode->next)
		pLastNode = pLastNode->next;

	pLastNode->next = createListNode(elem);

	return head;
}

struct LinkListNode* linkListRemoveHead(struct LinkListNode** head)
{
	pLinkListNodeT pFirstNode = NULL;
	pFirstNode = *head;
	*head = pFirstNode->next;

	return pFirstNode;
}

struct LinkListNode* makeCircleList(struct LinkListNode* head, ListElemType elem)
{
	pLinkListNodeT pLastNode = NULL;

	pLastNode = head;

	if (!head)
	{
		head = createListNode(elem);
		head->next = head;
		return head;
	}
		

	while (pLastNode->next != head)
		pLastNode = pLastNode->next;

	pLastNode->next = createListNode(elem);
	pLastNode = pLastNode->next;
	pLastNode->next = head;

	return head;
}

struct LinkListNode* linkListAddHead(struct LinkListNode* head, ListElemType elem) {
	pLinkListNodeT pFirstNode = NULL;

	if (head) {
		pFirstNode = head;

		head = createListNode(elem);
		head->next = pFirstNode;
	}else{
		return createListNode(elem);
	}


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

void destroyLinkList(struct LinkListNode* head)
{
	pLinkListNodeT pNode = NULL;
	if (head)
	{
		pNode = head;
		while (pNode)
		{
			head = head->next;
			free(pNode);
			pNode = head;
		}
	}
}

void linkListAdd(struct LinkListNode* toAdd, ListElemType elem) 
{
	pLinkListNodeT pNode = NULL;

	pNode = createListNode(elem);
	toAdd->next = pNode;
}

void visitList(struct LinkListNode* head)
{
	while (head)
	{
		if (head->next)
			printf("%d->", head->elem);
		else
			printf("%d\n", head->elem);

		head = head->next;
	}
}

struct DLinkListNode* createDLLNode(DListElemType elem)
{
	pDLinkListNodeT pDLNode = NULL;

	pDLNode = (pDLinkListNodeT)malloc(sizeof(DLinkListNodeT));
	pDLNode->elem = elem;
	pDLNode->next = pDLNode;
	pDLNode->prev = pDLNode;

	return pDLNode;
}

/*
 *Add a node next to pNode, return head
 *link the node pToAdd with pNode->next
 */
struct DLinkListNode* DLListAdd(struct DLinkListNode* head, 
	                            struct DLinkListNode* pNode, 
	                            struct DLinkListNode* pToAdd)
{
	if (!head)
		return pToAdd;

	if (!pNode)
		pNode = head->next;

	pNode->next->prev = pToAdd;
	pToAdd->next = pNode->next;
	pToAdd->prev = pNode;
	pNode->next = pToAdd;

	return head;
}

/*
 *add the node to the head the DLinkList
 */
struct DLinkListNode* DLListAddToHead(struct DLinkListNode* head, 
	                                  struct DLinkListNode* pToAdd)
{
	return DLListAdd(head, head->next, pToAdd);
}


/*
 *add the node to the tail of the DLinkList
 */
struct DLinkListNode* DLListAddToTail(struct DLinkListNode* head,  
	                                  struct DLinkListNode* pToAdd)
{
	return DLListAdd(head, head->prev, pToAdd);
}

/*
 *Delete pToDel from the DLinkList pointed to head
 *return the head 
 */
struct DLinkListNode* DLListDel(struct DLinkListNode* head, struct DLinkListNode* pToDel)
{
	if (!pToDel)
		return head;

	if (pToDel == head && pToDel->next == head)
	{
		free(pToDel);
		return NULL;
	}

	pToDel->prev->next = pToDel->next;
	pToDel->next->prev = pToDel->prev;

	free(pToDel);

	return head;
}

struct DLinkListNode* DLListFind(struct DLinkListNode* head, DListElemType elem)
{
	pDLinkListNodeT pDLNode = NULL;

	if (!head || (head->elem == elem))
		return head;
	
	pDLNode = head->next;
	while (pDLNode != head && pDLNode->elem != elem)
		pDLNode = pDLNode->next;

	return pDLNode == head ? NULL : pDLNode;
}

void destroyDLinkList(struct DLinkListNode* head)
{
	pDLinkListNodeT pDLNode = NULL;
	while (head)
	{
		head = DLListDel(head, head->next);
	}
}

struct LinkListNode* removeElements(struct LinkListNode* head, int val) {
	struct LinkListNode* slow = NULL;
	struct LinkListNode* fast = NULL;
	pLinkListNodeT pNode = NULL;

	struct LinkListNode node;

	if (!head)
		return head;

	slow = &node;
	slow->next = head;
	fast = head;
	while (fast)
	{
		if (fast->elem == val)
		{
			pNode = fast;
			slow->next = fast->next;
			fast = fast->next;
			free(pNode);	
		}
		else
		{
			fast = fast->next;
			slow = slow->next;
		}
	}
	return node.next;
}

struct LinkListNode** splitListToParts(struct LinkListNode* root, int k, int* returnSize) {
	int listSz = 0, rem = 0, i = 0, j = 0;
	int segSz = 0;
	struct LinkListNode* pNode = NULL, * pTemp = NULL;
	struct LinkListNode** res = NULL;

	pNode = root;
	listSz = 0;
	while (pNode) {
		pNode = pNode->next;
		listSz++;
	}

	rem = listSz % k;
	segSz = listSz / k;

	*returnSize = k;

	res = (struct LinkListNode**)malloc((*returnSize) * sizeof(struct LinkListNode*));
	memset(res, 0, (*returnSize) * sizeof(struct LinkListNode*));

	pNode = root;
	for (i = 0; i < *returnSize; i++) {
		res[i] = pNode;
		j = 0;
		while (j < segSz) {
			j++;
			pTemp = pNode;
			pNode = pNode->next;
		}

		if (rem)
		{
			rem--;
			pTemp = pNode;
			pNode = pNode->next;
		}
		if (pTemp)
			pTemp->next = NULL;
	}

	return res;
}

extern struct LinkListNode* linkListReverse(struct LinkListNode* head);

bool isPalindrome(struct LinkListNode* head) {
	struct LinkListNode* slow, * fast;
	struct LinkListNode* pNode = NULL;

	slow = head;
	fast = head;

	if (!head || !head->next)
		return true;

	while (fast && fast->next) {
		pNode = slow;
		slow = slow->next;
		fast = fast->next->next;
	}

	if (fast && !fast->next)
		pNode = slow;

	slow = linkListReverse(slow);

	if (pNode)
		pNode->next = NULL;

	while (slow && head && slow->elem == head->elem) {
		slow = slow->next;
		head = head->next;
	}

	return slow == NULL && head == NULL;
}

struct LinkListNode* rotateRight(struct LinkListNode* head, int k) {
	struct LinkListNode* tail = NULL;
	int listLen = 0;
	struct LinkListNode* pNode = NULL;

	listLen = 1;
	tail = head;
	while (tail->next)
	{
		listLen++;
		tail = tail->next;
	}

	tail->next = head;
	k %= listLen;
	k = listLen - k;
	pNode = tail;

	while (k--)
	{
		pNode = pNode->next;
	}

	head = pNode->next;
	pNode->next = NULL;

	return head;
}



void listTest()
{
	int num = 20;
	int i = 0;
	int nums[] = {1,2,6,3,4,5,6};
	pLinkListNodeT* pRes = NULL;
	pListNodeT head = NULL;
	int numsA[] = { 1,0,1 };
	int res = -1;
	printf("\n********Welcome to list test unit********\n");
	for (i = 20; i > 0; i--)
	{
		head = linkListAddHead(head, i);
	}

	visitList(head);

	destroyLinkList(head);
	head = NULL;

	//leetcode splitListToParts
	for (i = 0; i < sizeof(nums) / sizeof(nums[0]); i++) 
	{
		head = linkListAddTail(head, nums[i]);
	}
	visitList(head);

	//leetcode remove val from link list
	removeElements(head, 6);
	visitList(head);

	//leetcode splitListToParts
	pRes = splitListToParts(head, 6, &num);
	printf("splitListToParts:\n");
	for (i = 0; i < num; i++)
	{
		visitList(pRes[i]);
		destroyLinkList(pRes[i]);
	}
	free(pRes);
	head = NULL;

	//leetcode-palindrome link list
	for (i = 0; i < sizeof(numsA) / sizeof(numsA[0]); i++)
	{
		head = linkListAddTail(head, numsA[i]);
	}
	visitList(head);

	res = isPalindrome(head);
	printf("It %s palindrome link list\n", res ? "is" : "is Not");

	destroyLinkList(head);
	head = NULL;

	//leedcode rotation link list
	for (i = 5; i > 0; i--)
	{
		head = linkListAddHead(head, i);
	}
	visitList(head);

	head = rotateRight(head, 3);
	printf("\nlist after rotation:\n");
	visitList(head);
	destroyLinkList(head);

	head = NULL;
}