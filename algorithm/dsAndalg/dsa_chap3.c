/***************************************************************************************
 *
 *
 *
 *Author: Jiwen CHEN <chen1984jiwen@163.com>
 *
 *
 *
 *
 *
 *
 ****************************************************************************************/

#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include "list.h"
#include <time.h>

/*
 *3.1打印链表
 *    算法：递归实现
 *
 */
void printList(pLinkListNodeT head)
{
	if (!head)
		return;

	if (head->next)
		printf("%d->", head->elem);	
	else
		printf("%d\n", head->elem);
	printList(head->next);
}

/*
 *3.2 printLots
 *O(min(len(L), last elem of list P))
 */
void printLots(pLinkListNodeT L, pLinkListNodeT P)
{
	int step = 1;

	printf("\n--printLots--\n");
	while (P && L)
	{
		while (L && step < P->elem)
		{
			L = L->next;
			++step;
		}

		if(L)
			printf("%d ", L->elem);

		P = P->next;
	}
	printf("\n--printLots done!--\n");
}

/*
 *3.3 交换相邻的两个元素
 *
 *算法描述：
 *    a1->a2->a3->a4...->an->NULL
 *    递归调用交换a3->a4->...->NULL
 *    再调整a1,a2
 */

struct LinkListNode* linkListSwapNeighbor(struct LinkListNode* head)
{
	pLinkListNodeT pListEven = NULL;
	pLinkListNodeT pListOdd = NULL;
	pLinkListNodeT phead = NULL;

	if (!head || !head->next)
		return head;

	pListOdd = head;
	pListEven = pListOdd->next;
	phead = linkListSwapNeighbor(pListEven->next);

	pListOdd->next = phead;
	pListEven->next = pListOdd;
	phead = pListEven;

	return phead;
}

/**3.3 交换相邻的两个元素
 *算法描述：
 *    先遍历原始链表的时候，把原始链表分割成奇偶两部分，然后再按照先偶后奇插入
 *
 */
struct LinkListNode* linkListSwapNeighborNode(struct LinkListNode* head)
{
	pLinkListNodeT pListEven = NULL;
	pLinkListNodeT pListOdd = NULL;
	pLinkListNodeT pNode = NULL, pEvenNode = NULL, pOddNode = NULL;
	struct LinkListNode node;
	node.next = NULL;
	int step = 1;

	if (!head || !head->next)
		return head;

	pListOdd = head;
	pListEven = pListOdd->next;

	
	pEvenNode = pListEven;
	pOddNode = pListOdd;
	pNode = pListEven->next;
	
	pListEven->next = NULL;
	pListOdd->next = NULL;
	step = 3;
	while (pNode)
	{
		if (step & 1)
		{
			pOddNode->next = pNode;
			pOddNode = pNode;
			pNode = pNode->next;
			pOddNode->next = NULL;
		}
		else
		{
			pEvenNode->next = pNode;
			pEvenNode = pNode;
			pNode = pNode->next;
			pEvenNode->next = NULL;
		}
		
		step++;
	}
	
	pNode = &node;
	while (pListEven || pListOdd)
	{
		if (pListEven)
		{
			pNode->next = pListEven;
			pNode = pNode->next;
			pListEven = pListEven->next;
		}

		if (pListOdd)
		{
			pNode->next = pListOdd;
			pNode = pNode->next;
			pListOdd = pListOdd->next;
		}
	}

	return node.next;
}


/**3.3 交换相邻的两个元素
 *算法描述：
 *    设置快慢指针，然后按照a1->a2, a2->a3两两交换
 *
 */
struct LinkListNode* linkListSwapPairs(struct LinkListNode* head) 
{
	pLinkListNodeT slow = NULL;
	pLinkListNodeT fast = NULL;
	pLinkListNodeT pNode = NULL;

	
	if (!head || !head->next)
		return head;


	slow = head->next;
	fast = slow->next;
	head = fast;

	slow->next = fast->next;
	fast->next = slow;

	slow = head->next;
	fast = slow->next;
	while (fast && fast->next)
	{
		slow->next = fast->next;
		pNode = fast->next->next;
		fast->next->next = fast;
		fast->next = pNode;

		slow = fast;
		fast = fast->next;
	}

	return head;
}

/*3.5，求排序链表的并
 *sortedListUnion()
 */
struct LinkListNode* sortedListUnion(struct LinkListNode* listA, struct LinkListNode* listB)
{
	struct LinkListNode node;
	pLinkListNodeT pNode = NULL, pTemp = NULL;
	pNode = &node;

	while (listA && listB)
	{
		if (listA->elem > listB->elem) 
		{
			pNode->next = listB;
			listB = listB->next;
		}
		else 
		{
			pNode->next = listA;
			if (listA->elem == listB->elem)
			{
				pTemp = listB;
				listB = listB->next;
				free(pTemp);
			}
			listA = listA->next;
		}

		pNode = pNode->next;
	}

	if (listA)
		pNode->next = listA;

	if (listB)
		pNode->next = listB;

	return node.next;
}

/*合并两个有序链表：
 *sortedListMerge
 */
struct LinkListNode* sortedListMerge(struct LinkListNode* listA, struct LinkListNode* listB)
{
	struct LinkListNode node;
	pLinkListNodeT pNode = NULL;
	pNode = &node;

	while (listA && listB)
	{
		if (listA->elem > listB->elem)
		{
			pNode->next = listB;
			listB = listB->next;
		}
		else
		{
			pNode->next = listA;
			listA = listA->next;
		}

		pNode = pNode->next;
	}

	if (listA)
		pNode->next = listA;

	if (listB)
		pNode->next = listB;

	return node.next;
}

/*3.4，计算排序链表的交
 *sortedListIntersection
 */
struct LinkListNode* sortedListIntersection(struct LinkListNode* listA, struct LinkListNode* listB)
{
	pLinkListNodeT head = NULL;


	while (listA && listB)
	{
		if (listA->elem == listB->elem)
		{
			head = linkListAddTail(head, listA->elem);
			listA = listA->next;
			listB = listB->next;
		}
		else if (listA->elem < listB->elem)
		{
			listA = listA->next;
		}
		else
		{
			listB = listB->next;
		}

	}
	return head;
}

/*
 *对于一个链表进行归并排序
 *listMergeSort(): 
 *    利用快慢指针对链表进行划分，然后递归的调用，最后一步是merge
 */
struct LinkListNode* listMergeSort(struct LinkListNode* list)
{
	pLinkListNodeT slow = NULL, fast = NULL;
	pLinkListNodeT left = NULL, right = NULL;

	if (!list || !list->next)
		return list;

	if (!list->next->next)
	{
		slow = list;
		fast = list->next;
	}
	else
	{
		slow = list;
		fast = list;
		while (fast && fast->next)
		{
			slow = slow->next;
			fast = fast->next->next;
		}
	}

	fast = slow->next;
	slow->next = NULL;
	left  = listMergeSort(list);
	right = listMergeSort(fast);
	return sortedListMerge(left, right);
}

/*
 *3.6，多项式相加
 *    O(M+N)
 */
void printPoly(struct polyNode* poly)
{
	int hasZero = 0;
	while (poly)
	{
		if (poly->deg)
		{
			if (!hasZero)
			{
				hasZero = 1;//dummy/hack has zero
				printf("%s", poly->coef > 0 ? "" : "-");
			}
			else
			{
				printf("%s", poly->coef > 0 ? "+" : "-");
			}
			    
			if (poly->coef != 1 && poly->coef != -1)
			{
				printf("%d", poly->coef > 0 ? poly->coef : -poly->coef);
			}

			if (poly->deg != 1)
			{
				printf("x^%d", poly->deg);
			}
			else
			{
				printf("x");
			}
		}
		else
		{
			printf("%d", poly->coef);
			hasZero = 1;
		}
			

		poly = poly->next;
	}
	printf("\n");
}
/*
 *polyAdd(struct polyNode* polyA, struct polyNode* polyB):
 *    polyA:
 *    polyB:
 *    return:struct polyNode*
 *    在计算的过程中，不重新分配资源，对原始资源进行整合，同时释放相应的资源
 *    调用者需要在适当的时机调用destroyPoly()释放本函数返回的资源/指针
 */
struct polyNode* polyAdd(struct polyNode* polyA, struct polyNode* polyB)
{
	struct polyNode poly;
	struct polyNode* pNode = NULL;
	struct polyNode* ptemp = NULL;

	pNode = &poly;
	while (polyA && polyB) 
	{
		if (polyA->deg == polyB->deg) 
		{
			if (polyA->coef + polyB->coef != 0)
			{
				polyA->coef += polyB->coef;
				pNode->next = polyA;
				pNode = pNode->next;
				ptemp = polyB;
				polyB = polyB->next;
				free(ptemp);
				polyA = polyA->next;
			}
			else
			{
				ptemp = polyB;
				polyB = polyB->next;
				free(ptemp);
				ptemp = polyA;
				polyA = polyA->next;
				free(ptemp);
			}
		}
		else if (polyA->deg < polyB->deg)
		{
			pNode->next = polyA;
			polyA = polyA->next;
			pNode = pNode->next;
		}
		else
		{
			pNode->next = polyB;
			polyB = polyB->next;
			pNode = pNode->next;
		}
	}

	if (polyA)
		pNode->next = polyA;

	if (polyB)
		pNode->next = polyB;

	return poly.next;
}

/*
 *polyMulXexp:
 *    计算f(x)*x^n
 *
 *    为结果动态的分配资源，调用者需要在适当的时机释放资源
 */
struct polyNode* polyMulXexp(struct polyNode* poly, int coef, int deg)
{
	pPolyNodeT pNode = NULL, ptemp = NULL;
	struct polyNode polyMulx;

	pNode = &polyMulx;

	if (!poly)
		return poly;

	while (poly)
	{
		ptemp = (pPolyNodeT)malloc(sizeof(polyNodeT));
		ptemp->coef = poly->coef * coef;
		ptemp->deg = poly->deg + deg;
		ptemp->next = NULL;
		pNode->next = ptemp;
		pNode = pNode->next;
		poly = poly->next;
	}

	return polyMulx.next;
}

/*3.7 多项式相乘
 *f(x) = a0 + a1*x + a2*x^2 + ... + an*x^n
 *g(x) = b0 + b1*x + b2*x^2 + ... + bm*x^m
 *
 *m(x) = f(x)*g(x) = b0*f(x) + b1*x*f(x) + ... + bm*x^m*f(x)
 * S(*) = n + n +  + n = O(mn)
 */
struct polyNode* polyMul(struct polyNode* polyA, struct polyNode* polyB)
{
	pPolyNodeT polyMult = NULL;

	while (polyB)
	{
		polyMult = polyAdd(polyMult, polyMulXexp(polyA, polyB->coef, polyB->deg));
		polyB = polyB->next;
	}

	return polyMult;
}


/*
 *struct polyNode* makePoly(int *coeff, int deg)：
 *    coeff： 多项式系数矩阵/数组，对于系数为0的需要补齐，数组的第i项对应于多项式的第i次
 *    deg:    多项式的最大次数
 *    return: 多项式的结构指针，按照幂升序
 *    
 */
struct polyNode* makePoly(int *coeff, int deg)
{
	struct polyNode poly;
	struct polyNode* pNode = NULL;
	struct polyNode* pLastNode = NULL;


	int exp = 0;
	if (deg < 0)
		return NULL;

	pLastNode = &poly;
	for (exp = 0; exp <= deg; exp++) 
	{
		if (coeff[exp])
		{
			pNode = (struct polyNode*)malloc(sizeof(struct polyNode));
			pNode->coef = coeff[exp];
			pNode->deg = exp;
			pNode->next = NULL;
			pLastNode->next = pNode;
			pLastNode = pLastNode->next;
		}
	}

	return poly.next;
}

/*
 *destroyPoly(struct polyNode* poly)：
 *    poly： 需要被销毁的多项式
 */
void destroyPoly(struct polyNode* poly)
{
	struct polyNode* pNode = NULL;

	if (!poly)
		return;

	while (poly)
	{
		pNode = poly->next;
		free(poly);
		poly = pNode;
	}
}

/*
 *3.8 多项式的幂
 *   
 */
struct polyNode* polyPow(struct polyNode* poly, int n)
{
	pPolyNodeT polyPower = NULL;
	pPolyNodeT pTpoly = NULL;
	int constant = 1;


	if (n == 1)
		return poly;

	pTpoly = polyPower = makePoly((int*)&constant, 0);
	while (n--)
	{
		pTpoly = polyPower;
		polyPower = polyMul(poly, polyPower);
		destroyPoly(pTpoly);
	}

	return polyPower;
}


struct polyNode* polyPower(int *coef, int deg, int n)
{
	struct polyNode* polyA, *polyP;

	polyA = makePoly(coef, deg);
	polyP = polyPow(polyA, n);
	printf("original poly is:\n");
	printPoly(polyA);
	printf("\nthe power %d of poly:\n", n);
	printPoly(polyP);

	return polyP;
}
/*
 *3.9  编写任意精度的整数运算包
 *
 *123 在链表中存储方式为3->2->1，低位在前，高位在后，幂升排序
 */
struct LinkListNode* num2List(int num)
{
	pLinkListNodeT pNumList = NULL;

	pNumList = linkListAddTail(pNumList, num % 10);;

	num = num / 10;
	while (num)
	{
		pNumList = linkListAddTail(pNumList, num % 10);
		num = num / 10;
	}

	return pNumList;
}

/*
 *return the list which stores the sum of a and b
 *didn't allocate new memory, just use the memory of pLa and pLb
 *the list of pLa and pLb will be changed, the caller should free 
 *pLa, pLb explictly
 */
struct LinkListNode* numsAdd(struct LinkListNode* pLa, struct LinkListNode* pLb)
{
	int carrier = 0;
	pLinkListNodeT pNodeA = NULL, pNodeB = NULL;
	LinkListNodeT listSum;
	listSum.next = NULL;


	if (pLa)
		listSum.next = pLa;
	else if (pLb)
		listSum.next = pLb;
	else
		return NULL;

	while (pLa && pLb)
	{
		pLa->elem += pLb->elem + carrier;
		carrier = pLa->elem / 10;
		pLa->elem %= 10;
		pNodeB = pLb;
		pNodeA = pLa;
		pLa = pLa->next;
		pLb = pLb->next;
	}

	if (pLb)
	{
		if (pNodeA)
		{
			pNodeA->next = pLb;
			pNodeB->next = NULL;
		}
		pLa = pLb;
	}
		

	while(pLa && carrier)
	{
		pLa->elem += carrier;
		carrier = pLa->elem / 10;
		pLa->elem %= 10;
		pNodeA = pLa;
		pLa = pLa->next;
	}

	if (carrier) 
	{
		pNodeA->next = createListNode(carrier);
	}

	return listSum.next;
}

/*
 *create a new list to store the result of num*10^n
 */
struct LinkListNode* numsMul(struct LinkListNode* pLNum, int num, int n)
{
	pLinkListNodeT pMulRes = NULL;
	pLinkListNodeT pNode = NULL;
	LinkListNodeT NumMulList;
	int carry = 0;

	pMulRes = &NumMulList;

	while (pLNum)
	{
		pNode = (pLinkListNodeT)malloc(sizeof(struct LinkListNode));
		pNode->elem = pLNum->elem * num;
		pNode->elem += carry;
		pNode->next = NULL;
		carry = pNode->elem / 10;
		pNode->elem %= 10;
		pMulRes->next = pNode;
		pMulRes = pMulRes->next;
		pLNum = pLNum->next;
	}

	if (carry)
		pMulRes->next = createListNode(carry);

	while (n--)
		NumMulList.next = linkListAddHead(NumMulList.next, 0);

	return NumMulList.next;
}
/*
 *create a list to store the result of A multipled by B
 */
struct LinkListNode* numsMultply(struct LinkListNode* pLNumA, struct LinkListNode* pLNumb)
{
	int pos = 0;
	struct LinkListNode* pNumRes = NULL;
	struct LinkListNode* pNode = NULL;

	while (pLNumb)
	{
		pNode = pNumRes;
		pNumRes = numsMul(pLNumA, pLNumb->elem, pos);
		pNumRes = numsAdd(pNumRes, pNode);
		destroyLinkList(pNode);
		pos++;
		pLNumb = pLNumb->next;
	}
	return pNumRes;
}


void printListNums(struct LinkListNode* pListNum)
{
	while (pListNum)
	{
		printf("%d", pListNum->elem);
		pListNum = pListNum->next;
	}
	printf("\n");
}

struct LinkListNode* powerList(int x, int exp) {
	struct LinkListNode* pLa, *pLb;
	struct LinkListNode* pNumList;
	unsigned long digit[10] = { 0 };
	int i = 0;

	pLa = num2List(1);
	pLb = num2List(x);
	pNumList = NULL;
	for (i = 0; i < exp; i++)
	{
		pNumList = pLa;
		pLa = numsMultply(pLa, pLb);
		destroyLinkList(pNumList);
	}
	destroyLinkList(pLb);
	pNumList = pLa;
	while (pLa)
	{
		digit[pLa->elem]++;
		pLa = pLa->next;
	}
	printf("the digit counting of %d^(%d) is following:\n", x, exp);
	for (i = 0; i < 10; i++)
	{
		printf("digit: %d -- count: %d\n", i, digit[i]);
	}
	return pNumList;
}

/*
 *Josephus game
 */
int JosephusGameOpt(int M, int N, pLinkListNodeT* pFreeList)
{
	pLinkListNodeT head = NULL;
	pLinkListNodeT prev = NULL;
	LinkListNodeT FreeList;
	pLinkListNodeT pFreeNode = &FreeList;

	int i = 0;
	int round = 0;
	int res = -1;

	if (M == 0)
		return N;

	for (i = 1; i <= N; i++) 
	{
		head = makeCircleList(head, i);
	}

	if (!head)
		return res;

	while (head->next != head)
	{
		round = M;
		while (round)
		{
			prev = head;
			head = head->next;
			round--;
		}

		prev->next = head->next;
		//printf("JosephusGame: %d removed\n", head->elem);
		pFreeNode->next = head;
		head->next = NULL;
		pFreeNode = pFreeNode->next;
		head = prev->next;	
	}

	res = head->elem;
	//destroy(head);
	//destroyLinkList(FreeList.next);
	*pFreeList = FreeList.next;

	return res;
}

int JosephusGame(int M, int N)
{
	pLinkListNodeT head = NULL;
	pLinkListNodeT prev = NULL;

	int i = 0;
	int round = 0;
	int res = -1;

	if (M == 0)
		return N;

	for (i = 1; i <= N; i++)
	{
		head = makeCircleList(head, i);
	}

	if (!head)
		return res;

	while (head->next != head)
	{
		round = M;
		while (round)
		{
			prev = head;
			head = head->next;
			round--;
		}

		prev->next = head->next;
		//printf("JosephusGame: %d removed\n", head->elem);
		free(head);
		head = prev->next;
	}

	res = head->elem;
	free(head);

	return res;
}

void JosephusTest()
{
	int M, N;
	int res = -1;
	clock_t start, end;
	pLinkListNodeT pFreeList = NULL;

	printf("JosephusTest,please enter two nums:\n");
	printf(">>:");
	scanf("%d %d", &M, &N);

	start = clock();
	res = JosephusGame(M, N);
	end = clock();
	printf("JosephusGame:%d, duration:%.4f\n", res, (double)(end - start)/CLOCKS_PER_SEC);

	start = clock();
	res = JosephusGameOpt(M, N, &pFreeList);
	end = clock();
	printf("JosephusGame:%d, duration:%.4f\n", res, (double)(end - start) / CLOCKS_PER_SEC);

	destroyLinkList(pFreeList);
}

/*
 *3.12 反转一个链表
 *算法描述：
 *    从第一个节点开始断开，然后从头部插入临时表头，最后返回node.next
 *
 */
struct LinkListNode* linkListReverse(struct LinkListNode* head)
{
	struct LinkListNode node;
	node.next = NULL;
	pLinkListNodeT pNode = NULL;

	while (head)
	{
		pNode = head->next;
		head->next = node.next;
		node.next = head;
		head = pNode;
	}

	return node.next;
}


/*3.12
 *迭代反转
 *p->q->r->....
 *NULL<-p<-q r->...
 *NULL<-...<-p<-q r->...->NULL
 *NULL<-...<-...<-...<-p q = r = NULL
 */
struct LinkListNode* linkListReverseByNeihgbor(struct LinkListNode* head) 
{
	pLinkListNodeT p = NULL, q = NULL, r = NULL;

	if (!head || !head->next)
		return head;

	p = head;
	q = p->next;
	p->next = NULL;
	while (q)
	{
		r = q->next;
		q->next = p;
		p = q;
		q = r;
	}

	return p;
}

/*3.12
 *递归反转
 */
struct LinkListNode* linkListReverseRecursively(struct LinkListNode* head)
{
	pLinkListNodeT pNode = NULL;
	pLinkListNodeT phead = NULL;

	if (!head || !head->next)
		return head;

	pNode = head->next;
	phead = linkListReverseRecursively(head->next);
	pNode->next = head;
	head->next = NULL;

	return phead;
}


#define POLY_TEST_MAX_EXPON 100
#define BUFSIZE 512
void polyTest()
{
	int coeffA[] = { 2, -1, 0, 3, 0, 0, 1 }; 
	int coeffB[] = { 3, 2, -1, 1, 0, 1, -1, 4 };
	//int deg[] = { 1000, 2000, 4000, 8000, 10000 };
	int deg[] = { POLY_TEST_MAX_EXPON << 0,
		          POLY_TEST_MAX_EXPON << 1, 
				  POLY_TEST_MAX_EXPON << 2,
				  POLY_TEST_MAX_EXPON << 3,
				  POLY_TEST_MAX_EXPON << 4};

	int degA = sizeof(coeffA) / sizeof(coeffA[0]) - 1;
	int degB = sizeof(coeffB) / sizeof(coeffB[0]) - 1;
	int i = 0, j = 0;

	pPolyNodeT polyA = NULL;
	pPolyNodeT polyB = NULL;
	pPolyNodeT polyS = NULL;
	pPolyNodeT polyM = NULL;
	pPolyNodeT polyP = NULL;

	printf("****polyTest begin****\n");
	polyA = makePoly(coeffA, degA);
	polyB = makePoly(coeffB, degB);

	printPoly(polyA);
	printPoly(polyB);

	polyS = polyAdd(polyA, polyB);
	printf("****polyAdd:\n");
	printPoly(polyS);
	destroyPoly(polyS);
	polyA = NULL;
	polyB = NULL;
	polyS = NULL;

	polyA = makePoly(coeffA, degA);
	polyB = makePoly(coeffB, degB);
	polyM = polyMul(polyA, polyB);
	printf("****polyMul:\n");
	printPoly(polyM);
	destroyPoly(polyM);
	destroyPoly(polyB);
	destroyPoly(polyA);


	int* polyCoffB;
	int* polyCoffA;

	printf("******    This part is to test the performance of poly multiply     *****\n");
	for(i = 0; i < sizeof(deg)/sizeof(deg[0]); i++)
	{
		polyCoffA = (int*)malloc(sizeof(int) * (deg[i] + 1));
		polyCoffB = (int*)malloc(sizeof(int) * (deg[i] + 1));
		for (j = 0; j <= deg[i]; j++)
		{
			polyCoffA[j] = j;
			polyCoffB[j] = j;
		}

		polyA = makePoly(polyCoffA, deg[i]);
		polyB = makePoly(polyCoffA, deg[i]);
		clock_t start, end;
		start = clock();
		polyM = polyMul(polyA, polyB);
		end = clock();
		printf("degree:%d -- time duration:%.4f seconds\n",deg[i], (double)(end - start) / CLOCKS_PER_SEC);

		destroyPoly(polyM);
		destroyPoly(polyB);
		destroyPoly(polyA);
		free(polyCoffA);
		free(polyCoffB);
	}
	printf("******    poly multiply test DONE     *****\n");

	int polyCoff[] = { 1,1 };
	polyA = makePoly(polyCoff, 1);
	polyP = polyPow(polyA, 4);
	printPoly(polyA);
	printf("****polyPow:\n");
	printPoly(polyP);
	
	destroyPoly(polyA);
	destroyPoly(polyP);
	polyA = NULL;
	polyP = NULL;

	char buf[BUFSIZE];
	int  coef[BUFSIZE];
	int exp = 0;
	int power = 0;
	
	printf("power of poly test:\n");
	printf("please enter the cofficient of the poly:\n");
	printf(">>:");
	fgets(buf, BUFSIZE, stdin);
	exp = 0;
	for (i = 0; i < BUFSIZE; i++)
	{
		if (buf[i] == '\0' || buf[i] == '\n')
			break;
		if (buf[i] == ' ' || buf[i] == '\t')
			continue;
		coef[exp++] = buf[i] - '0';
	}

	printf("please enter the power:\n");
	printf(">>:");
	scanf("%d", &power);

	polyP = polyPower(coef, exp - 1, power);
	//printPoly(polyP);

	destroyPoly(polyP);

	printf("****polyTest end****\n");
}


void numListTest()
{
	struct LinkListNode* pNumList = NULL;

	int num = 123;
	int i = 0;
	char ch = 0;
	unsigned long digit[10] = { 0 };

	pNumList = num2List(num);
	//visitList(pNumList);
	destroyLinkList(pNumList);

	struct LinkListNode* pLa, * pLb;
	int numa, numb;
	char buf[BUFSIZE] = {0};

	numa = 135;
	numb = 13;
	pLa = num2List(numa);
	pLb = num2List(numb);

	pNumList = numsMul(pLa, 3, 1);

	//printList(pNumList);
	destroyLinkList(pNumList);
	pNumList = NULL;

	pNumList = numsMultply(pLa, pLb);
	pNumList = linkListReverse(pNumList);
	//printList(pNumList);
	destroyLinkList(pNumList);
	pNumList = NULL;

	pNumList = numsAdd(pLa, pLb);
	pNumList = linkListReverse(pNumList);
	//printList(pNumList);

	destroyLinkList(pNumList);
	destroyLinkList(pLb);

	pLa = pLb = NULL;
	printf("Big number multiplier test:\n");
	printf("please enter num A:\n");

need_input_again:
	memset(buf, 0, BUFSIZE);
	fgets(buf, BUFSIZE, stdin);
	for (i = 0; i < BUFSIZE; i++)
	{
		if (i == 0 && buf[0] == '\n')
			goto need_input_again;

		if (buf[i] == '\0' || buf[i] == '\n')
			break;

		pLa = linkListAddHead(pLa, buf[i] - '0');
	}
	//visitList(pLa);
	memset(buf, 0, BUFSIZE);
	printf("please enter num B:\n");
	fgets(buf, BUFSIZE, stdin);
	for (i = 0; i < BUFSIZE; i++)
	{
		if (buf[i] == '\0' || buf[i] == '\n')
			break;

		pLb = linkListAddHead(pLb, buf[i] - '0');
	}
	//visitList(pLb);
	pNumList = numsMultply(pLa, pLb);
	pNumList = linkListReverse(pNumList);
	printf("The result is:\n");
	printListNums(pNumList);
	destroyLinkList(pNumList);
	destroyLinkList(pLa);
	destroyLinkList(pLb);

	num = 2;
	pLa = num2List(1);
	pLb = num2List(2);
	pNumList = NULL;
	for (i = 0; i < 4000; i++)
	{
		pNumList = pLa;
		pLa = numsMultply(pLa, pLb);
		destroyLinkList(pNumList);
	}
	destroyLinkList(pLb);
	pNumList = pLa;
	while (pLa)
	{
		digit[pLa->elem]++;
		pLa = pLa->next;
	}
	printf("the digit counting of 2^4000 is following:\n");
	for (i = 0; i < 10; i++)
	{
		printf("digit: %d -- count: %d\n", i, digit[i]);
	}
	destroyLinkList(pNumList);

	int base = 0, exp = 0;
	printf("power of big number test:\n");
	printf("please enter base and exponent:\n");
	scanf("%d %d", &base, &exp);
	pNumList = powerList(base, exp);
	destroyLinkList(pNumList);
}

void dsaChap3Test()
{
	int num = 20;
	int i = 0;
	pListNodeT head = NULL;
	pListNodeT P = NULL;
	int nums[] = { 1,3,15,20,31 };
	int lenA = 0;
	pLinkListNodeT listA = NULL;
	pLinkListNodeT listB = NULL;
	pLinkListNodeT listC = NULL;
	int numsA[] = {1,2,3,4,5,6};
	int numsB[] = {2,3,4,5,8};

	int numsC[] = { 4,3,2,1,5,6,3,8,7,1,4,5,2,3,9,5,7 };
	int numsD[] = { 3,2,4,8,1,8,4,7 };

	printf("\n********Welcome to DSAChap3 test unit********\n");
	for (i = 20; i > 0; i--)
	{
		head = linkListAddHead(head, i);
	}
	printList(head);

	lenA = sizeof(nums)/sizeof(nums[0]);
	for (i = 0; i < lenA; i++)
	{
		P = linkListAddHead(P, nums[lenA - i - 1]);
	}
	printList(P);

	printLots(head, P);

	printf("\n--linkListReverse--\n");
	head = linkListReverse(head);
	printList(head);
	printf("\n--linkListReverse done!--\n");

	printf("\n--linkListReverseByNeihgbor--\n");
	head = linkListReverseByNeihgbor(head);
	printList(head);
	printf("\n--linkListReverseByNeihgbor done!--\n");

	printf("\n--linkListReverseRecursively--\n");
	head = linkListReverseRecursively(head);
	printList(head);
	printf("\n--linkListReverseRecursively done!--\n");

	printf("\n--linkListSwapNeighbor--\n");
	head = linkListSwapNeighbor(head);
	printList(head);
	printf("\n--linkListSwapNeighbor done!--\n");


	printf("\n--linkListSwapNeighborNode--\n");
	head = linkListSwapNeighborNode(head);
	printList(head);
	printf("\n--linkListSwapNeighborNode done!--\n");

	destroyLinkList(head);
	destroyLinkList(P);

	for (i = 1; i < 20; i += 2)
	{
		listA = linkListAddTail(listA, i);
	}
	printList(listA);

	for (i = 0; i < 20; i += 2)
	{
		listB = linkListAddTail(listB, i);
	}
	printList(listB);

	listC = sortedListIntersection(listA, listB);
	printf("sortedListIntersection:\n");
	printList(listC);
	destroyLinkList(listC);
	listC = NULL;

	listA = sortedListUnion(listA, listB);
	printf("sortedListUnion:\n");
	printList(listA);
	destroyLinkList(listA);

	listA = NULL;
	listB = NULL;

	for (i = 0; i < sizeof(numsA)/sizeof(numsA[0]); i++)
	{
		listA = linkListAddTail(listA, numsA[i]);
	}
	printList(listA);

	for (i = 0; i < sizeof(numsB) / sizeof(numsB[0]); i++)
	{
		listB = linkListAddTail(listB, numsB[i]);
	}
	printList(listB);

	listA = sortedListUnion(listA, listB);
	printf("\nsortedListUnion:\n");
	printList(listA);
	destroyLinkList(listA);
	listA = NULL;
	listB = NULL;

	for (i = 0; i < sizeof(numsA) / sizeof(numsA[0]); i++)
	{
		listA = linkListAddTail(listA, numsA[i]);
	}
	printList(listA);

	for (i = 0; i < sizeof(numsB) / sizeof(numsB[0]); i++)
	{
		listB = linkListAddTail(listB, numsB[i]);
	}
	printList(listB);
	listC = sortedListIntersection(listA, listB);
	printf("\nsortedListIntersection:\n");
	printList(listC);
	destroyLinkList(listC);
	listC = NULL;

	listA = sortedListMerge(listA, listB);
	printf("sortedListMerge:\n");
	printList(listA);
	destroyLinkList(listA);
	listA = NULL;
	listB = NULL;

	for (i = 0; i < sizeof(numsC) / sizeof(numsC[0]); i++)
	{
		listA = linkListAddTail(listA, numsC[i]);
	}
	printList(listA);
	listA = listMergeSort(listA);
	printf("listMergeSort:\n");
	printList(listA);
	destroyLinkList(listA);

	//poly test
	polyTest();

	//num test
	numListTest();

	//JosephusTest()
	JosephusTest();
}