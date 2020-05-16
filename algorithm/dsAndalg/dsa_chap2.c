/*
 *2.7随机生成前N个自然数的一个排列
 */

#include <stdio.h>
#include "sort.h"
#include <time.h>
#include <memory.h>
#include <stdlib.h>
#include "common.h"
#include <math.h>
#include <direct.h>
#include <io.h>

int ramdonInt(int m)
{
    return m - rand() % ((m << 1) + 1);
}

/*
 *random(int m, int n):
 *    return a random number between m and n, include m and n
 *    the max value returned by rand() is 0x7fff, to generate
 *    a 32-bit random value, (rand() << 16) | rand()
 * 
 */
int random(int m, int n) {
    int res = (rand() << 16) | rand();

    return m + res % (n - m + 1);
}

/*
 *int* randomPermutation(int n):
 *    return a random permutation of [1,2,3,...,n]
 *    
 *algorithm description:
 *    1. generate A[0,...,i]
 *    2. generate A[i+1] which is not present in A[0,...,i]
 */
int* randomPermutation(int n) {
    int* pRes = NULL;
    int i = 0, j = 0;
    int temp = 0;

    pRes = (int*)malloc(n * sizeof(int));
    if (!pRes)
    {
        return NULL;
    }

	while (i < n)
	{
		temp = random(1, n);

		for (j = 0; j < i && (temp != *(pRes + j)); j++);

		if (j == i)
		{
			*(pRes + i) = temp;
			i++;
		}
	}
        
    return pRes;
}

/*
 *int* randomPermutationByArray(int n):
 *    return a random permutation of [1,2,3,...,n]
 *
 *algorithm description:
 *    1. generate A[0,...,i]
 *    2. generate A[i+1] which is not present in A[0,...,i]
 *    3. use a array to indicate whether the randomValue is generated or not
 */
int* randomPermutationByArray(int n) {
	int* pRes = NULL;
	int i = 0;
	int temp = 0;
    int* usedRan = NULL;

	pRes = (int*)malloc(n * sizeof(int));
	if (!pRes)
	{
		return NULL;
	}

    /*
     *as usedRan[temp], 1 <= temp <= n, so need allocate n + 1 array
     */
    usedRan = (int*)malloc((n + 1) * sizeof(int));
    if (!usedRan)
    {
        return NULL;
    }

    //memset the array as zero first
    memset(usedRan, 0, (n + 1) * sizeof(int));

    i = 0;
	while (i < n)
	{
		temp = random(1, n);
		if (!usedRan[temp])
		{
            //if random value is not generated, update it as TRUE
			usedRan[temp] = TRUE;
			*(pRes + i) = temp;
			i++;
		}
	}

    free(usedRan);

    return pRes;
}

/*
 *int* randomPermutationBySwap(int n):
 *    return a random permutation of [1,2,3,...,n]
 *
 *algorithm description:
 *    1. generate A[0,...,i]
 *    2. generate A[i+1] which is not present in A[0,...,i]
 *    3. use a array to indicate whether the randomValue is generated or not
 */
int* randomPermutationBySwap(int n) {
	int* pRes = NULL;
	int i, j = 0;
	int temp = 0;
	int needRegenerate = 1;

	pRes = (int*)malloc(n * sizeof(int));

    //set the permutation first as [1,2,...,n]
    for (i = 0; i < n; i++)
    {
        *(pRes + i) = i + 1;
    }

    //swap the A[i] with a A[random(0,i)]
    for (i = 1; i < n; i++)
    {
        swap(pRes + i, pRes + random(0, i));
    }

    return pRes;
}

int* randomArrayBySwap(int n) {
	int* pRes = NULL;
	int i, j = 0;
	int temp = 0;
	int needRegenerate = 1;

	pRes = (int*)malloc(n * sizeof(int));

	//set the permutation first as [1,2,...,n]
	for (i = 0; i < n; i++)
	{
		*(pRes + i) = ramdonInt(100);
	}

	//swap the A[i] with a A[random(0,i)]
	for (i = 1; i < n; i++)
	{
		swap(pRes + i, pRes + random(0, i));
	}

	return pRes;
}


/*
 *2.10
 *issue description:
 *    f(x) = A[0]*x^0 + A[1]*x^1 + ... A[N]*x^N
 *
 *complexity:
 *     a)、S = 1 + 2 + ... + N = O(N^2)
 *     b)、S = O(NlogN) use the quick power:
 *         proof:
 *         S = log1 + log2 + ... log(N/2) + ... + log(N) <= Nlog(N)
 *
 *         S > log(N/2) + ... log(N) > N/2*log(N/2) 
 *         thus S = O(Nlog(N))
 *      c)、Horner rule：O(N)
 *          f(x) = A[0]+A[1]*x+A[2]*x^2+...+A[N]*x^N
 *               = A[0]+x*(A[1]+x*(A[2]+x*(A[3]+...x*(A[N-1] + x*(A[N]+x*(0)))))
 *
 */
int polyComputeBruce(int cofficient[], int x, int degree)
{
	int sum = 0;
	int i, j = 0;
	int res = 0;

	for (i = 0; i <= degree; i++)
	{
		res = cofficient[i];
		for (j = 0; j < i; j++)
		{
			res *= x;
		}
		sum += res;
	}

	return sum;
}

extern int QuickPower(int exp, int base);

int polyComputeByQP(int cofficient[], int x, int degree)
{
	int sum = 0;
	int i, j = 0;
	int res = 0;

	for (i = 0; i <= degree; i++)
	{
		res = cofficient[i];
		if (res)
		{
			res *= QuickPower(i,x);
		}
		sum += res;
	}

	return sum;
}

/*
 *Horner rule:
 *   f(x) = A[0]+A[1]*x+A[2]*x^2+...+A[N]*x^N
 *        = A[0]+x*(A[1]+x*(A[2]+x*(A[3]+...x*(A[N-1] + x*(A[N]+x*(0)))))
 */
int polyComputeByHorner(int cofficient[], int x, int degree)
{
	int poly = 0;
	int i = 0;

	poly = 0;
	for (i = degree; i >= 0; i--)
	{
		poly = x*poly + cofficient[i];
	}

	return poly;
}

/*
 *2.11 给出一个有效算法来确定严格递增整数序列A1,...,A[N]中是否存在i使得A[i]=i.
 *
 *二分搜索，mid = (low + high)/2
 *if A[mid] == mid: return mid
 *else if A[mid] < mid: for any 0 <= i <= mid， then A[i] < i
 *else if A[mid] > mid: for any mid <= i <= high, there must be A[i] > i
 *
 *proof:
 *
 *   if A[i] = i, then A[mid] > A[i] + mid - i = mid, there is a contradict.
 *
 */
int CheckIfNumPresent(int A[], int len, int i)
{
	return binarySearch(A, len, i);
}


/*
 *2.12
 *1.求最小连续子序列和
 *2.求最小连续正子序列和
 *3.求最大连续子序列乘积
 *
 */

/*
 *int minSubseqSumByBruce(int A[], int len)：
 *    对每一个i，从A[i]处求和，然后同最小的比较，复杂度为O(N^2)
 */
int minSubseqSumByBruce(int A[], int len, int *pSeqBegin, int *pSeqEnd)
{
	int minSum = INT_MAX;
	int tempSum = 0;

	int i = 0, j = 0;
	for (i = 0; i < len; i++)
	{
		tempSum = 0;
		for (j = i; j < len; j++)
		{
			tempSum += A[i];
			if (tempSum < minSum)
			{
				minSum = tempSum;
				*pSeqBegin = i;
				*pSeqEnd = j;
			}
		}
	}

	return minSum;
}


/*
 *int minSumSubseqByConcur(int A[], int len):
 *
 *
 *algorithm description:
 *    divide the array into two parts, then the minSum subsequence is one of the three:
 *    1. exist in left the part 
 *    2. exist in the right the part
 *    3. accross the left part and right part
 */
int minSumSubseqByConcur(int A[], int left, int right, int *pSeqBegin, int *pSeqEnd)
{
	int minSumL = 0, minSumR = 0, minSum = INT_MAX;
	int i = 0, thisSum = 0, mid = 0, lAccrossBegin = 0, rAccrossEnd = 0;
	int lLSeqBegin = 0, lRSeqEnd = 0, rLSeqBegin = 0, rRSeqEnd = 0;

	if (left == right)
	{
		*pSeqBegin = left;
		*pSeqEnd = right;
		return A[left];
	}

	mid = left + (right - left) / 2;
	minSumL = minSumSubseqByConcur(A, left, mid, &lLSeqBegin, &lRSeqEnd);
	minSumR = minSumSubseqByConcur(A, mid + 1, right, &rLSeqBegin, &rRSeqEnd);
	thisSum = 0;
	i = mid;
	while (i >= left)
	{
		thisSum += A[i];
		if (thisSum < minSum)
		{
			minSum = thisSum;
			lAccrossBegin = i;
		}
	}

	i = mid + 1;
	while (i <= right)
	{
		thisSum += A[i];
		if (thisSum < minSum)
		{
			minSum = thisSum;
			rAccrossEnd = i;
		}
	}

	if (minSum < minSumL)
	{
		if (minSum < minSumR)
		{
			*pSeqBegin = lAccrossBegin;
			*pSeqEnd = rAccrossEnd;
		}
		else
		{
			*pSeqBegin = rLSeqBegin;
			*pSeqEnd = rRSeqEnd;
		}
	}
	else
	{
		if (minSumL < minSumR)
		{
			*pSeqBegin = lLSeqBegin;
			*pSeqEnd = lRSeqEnd;
		}
		else
		{
			*pSeqBegin = rLSeqBegin;
			*pSeqEnd = rRSeqEnd;
		}
	}

	return minSum;
}

int minSumSubseqDP(int A[], int len)
{
	int minSum = INT_MAX;
	int tempSum = 0;
	int i = 0;

	for (i = 0; i < len; i++)
	{
		tempSum += A[i];
		if (tempSum < minSum)
		{
			minSum = tempSum;
		}
		else if (tempSum > 0)
		{
			tempSum = 0;
		}
	}

	return minSum;
}

/*
 **2.求最小连续正子序列和
 *sum[0]=a[0]
 *sum[1]=sum[0]+a[1]
 *
 *sum[i]=sum[i-1]+a[i]
 *
 *对sum[]排序，然后求排序后的sum[i]-sum[i-1]的差值的最小值
 */




/*
 *编写一个程序用来测试一个整数是否素数
 *O(sqrt(N))
 *反证法：
 *    对于一个数x，设在2到sqrt(N)之间没有因子，则必为素数，如若不然，若x为合数，
 *则存在s，2<=s<t-1使得x|s，由于s > sqrt(N)，所以t=x/s | x，由于x|t，且
 *t< sqrt(N)，矛盾。所以x必为素数
 */

int isPrimeNum(unsigned long num)
{
	unsigned long div = 0;
	unsigned long i = 0;

	if (num == 0 || num == 1)
	{
		return FALSE;
	}

	if (num == 2)
	{
		return TRUE;
	}


	div = (int)sqrt(num);
	for (i = 2; i <= div; i++)
	{
		if (num % i == 0)
		{
			return FALSE;
		}
	}

	return TRUE;
}

/*
 *Eratosthese algorithm:
 *    remove 2*i
 *    remove 3*i
 *    ...
 *    remove k*i k <= sqrt(N)
 */
unsigned long* makePrimeTable(unsigned long num)
{
	unsigned long* pPrimTable = NULL;
	unsigned long i = 0, k = 0;

	pPrimTable = (unsigned long*)malloc((num + 1) * sizeof(unsigned long));

	if (!pPrimTable)
		return pPrimTable;

	for (i = 0; i <= num; i++)
		*(pPrimTable + i) = i;

	for (i = 2; i <= (unsigned long)sqrt(num); i++)
	{
		if (*(pPrimTable + i))
		{
			for (k = 2; k <= num / i; k++)
				pPrimTable[k * i] = 0;
		}
	}

	printf("Prime number table less than:%10d\n", num);
	k = 0;
	for (i = 2; i < num; i++)
	{
		if (pPrimTable[i])
		{
			printf("%10d", pPrimTable[i]);
			k++;
			if (k % 5 == 0)
			{
				printf("\n");
			}
		}

	}
	return pPrimTable;
}

/*
 *decmical to binary 
 */
void decToBin(unsigned long x)
{
	int res[128] = { 0 };
	int i = 0;
	if (x == 0 || x == 1)
	{
		printf("%d\n", x);
		return;
	}

	while(x)
	{
		res[i++] = x & 1;
		x = x >> 1;
	}

	while (i)
	{
		printf("%d", res[--i]);
		if (i % 4 == 0 && i != 0)
			printf(",");
	}

	printf("\n");
}


/*2.15 8次计算x^62
 *x*x->x^2
 *x^2*x^2->x^4
 *x^4*x^4 ->x^8
 *x^8*x^8->x^16
 *x^4*x16->x^20
 *x^20*x^10->x^40
 *x^40*x^20->x^60
 *x^60*x^2->x^62
 */

/*
 *2.16 不用递归实现快速幂运算
 */
double quickPow(double x, int n)
{
	double res = 1.0;

	if (n < 0)
	{
		x = 1.0 / x;
		n = -n;
	}

	if (x == 0.0)
		res = 0.0;

	while (n)
	{
		if (n & 1)
			res *= x;
		
		x *= x;

		n >>= 1;
	}

	return res;
}

/*2.17
 *快速幂的乘法次数
 *2（N - 1）+ M N是二进制中1的个数，M是0的个数
 *由上述的非递归算法可知，对于位为1会做两次乘法，对于位为0只做一次乘法
 */


/*
 *2.19 判断是否存在主元，主元的次数超过N/2
 *算法：
 *
 *    从A中取A1,A2，如果相等，则放入数组B,如果不等则丢弃，继续选取A3,A4做前述比较
 *如果是奇数，则把最后一个元素添加到B，那么B的候选主元也是A的候选主元，因为B中的元素
 *是A中的元素双双比较相等才添入的。对于某一个不在B中的但在A中元素X,必定不是主元，
 *因为经过n/2次双双配对比较，x没有添入到B中,说明给元素的个数不会超过n/2。
 * 
 *   N/2+N/4...+1 = O(N)
 * 
 *
 *算法2：
 *    利用快速选择算法，选择中位数，然后对中位数计数
 *
 *算法3：
 *    利用一个map<int, int>,扫描数组，对key出现的次数进行更新，类似于桶排序/计数排序
 */
int SelectPivot(int A[], int len)
{
	int i = 0, k = 0;
	if (len == 0)
	{
		return -1;
	}

	if (len == 1)
	{
		return A[0];
	}

	while (i + 1 < len)
	{
		if (A[i] == A[i + 1])
		{
			A[k++] = A[i];
		}
		i += 2;
	}

	if (len & 1)
	{
		A[k++] = A[i];
	}

	return SelectPivot(A, k);
}

int FindPivot(int A[], int len)
{
	int candidate = -1;
	int count = 0;
	int i = 0;

	candidate = SelectPivot(A, len);
	if (candidate == -1)
	{
		return -1;
	}

	while (i < len)
	{
		if (candidate == A[i++])
			count++;
	}

	if (count >= ((len >> 1) + 1))
		return candidate;

	return -1;
}

void dsa_test_random()
{
	int count = 0, limit = 100;
	int lineCnt = 5;
	int i = 0;
    int m = 0, n = 0;
	int failCount = 0;
	int* nums = NULL;

	printf("Please enter two number to generate the random number in [-limit, limit].\n\
please enter the count of random number and max limit of random:\n");
	printf("the input format is:count,limit\n");
	srand((unsigned)time(NULL));
	scanf_s("%d,%d", &count, &limit);
	for (i = 0; i < count; i++)
	{
		if (i % lineCnt == 0)
		{
			printf("\n");
		}
		printf("%4d ", ramdonInt(limit));
	}

INPUT:
	printf("\nplease enter two numbers m and n to generate random number in [m, n],m < n:");
	scanf_s("%d,%d", &m, &n);
	if (m >= n && failCount < 5)
	{
		printf("make sure the first number is smaller than the second!\n");
		failCount++;
		goto INPUT;
	}

	if (failCount >= 5)
	{
		return;
	}

	nums = (int*)malloc(count * sizeof(int));
	for (i = 0; i < count; i++)
	{
		if (i % lineCnt == 0)
		{
			printf("\n");
		}
		printf("%4d ", nums[i] = random(m, n));
	}

	quickSort(nums, count);
	printf("\nsorted nums:");
	for (i = 0; i < count; i++)
	{
		if (i % lineCnt == 0)
		{
			printf("\n");
		}
		printf("%4d ", nums[i]);
	}

	free(nums);
}

#define PERMUTATION_TEST_CNT 8
#define MAX_PATH_LENGTH 1024
void dsa_permutation_alg_analysis() {
	int i = 0;
	int* pAns = NULL;
	clock_t start, end;
	double duration;
	int errorcode = -1;
	int permuNumByComp[PERMUTATION_TEST_CNT] = { 500, 1000, 2000, 4000, 8000, 16000, 20000, 40000 };
	int permuNumByArra[PERMUTATION_TEST_CNT] = { 50000, 100000, 200000, 400000, 800000, 1600000, 3200000, 6400000 };
	int permuNumBySwap[PERMUTATION_TEST_CNT] = { 50000, 100000, 200000, 400000, 800000, 1600000, 3200000, 6400000 };

	double durationByComp[PERMUTATION_TEST_CNT] = { 0.0 };
	double durationByArra[PERMUTATION_TEST_CNT] = { 0.0 };
	double durationBySwap[PERMUTATION_TEST_CNT] = { 0.0 };
	char currPath[MAX_PATH_LENGTH];
	FILE* fp = NULL;
	char* pFileName = ".\\data\\permutation.txt";
	char filePath[256] = {0};
	_getcwd(currPath, MAX_PATH_LENGTH); //derive current path
	strrchr(currPath, '\\');
	char* pTemp = pFileName;
	char* p = NULL;

	if(_access(pTemp, 0)){
		pTemp = strrchr(pFileName, '\\');
		p = pFileName;
		memset(filePath, 0, sizeof(filePath));
		while (p != pTemp)
		{
			filePath[i++] = *p++;
		}
		_mkdir(filePath);
	}

	fp = fopen(pFileName, "w+");
	if (!fp)
	{
		printf("Fail to open file:%s\n", pFileName);
		return;
	}

	srand((unsigned)time(NULL));

	fprintf(fp, "randomPermutationByCompare:\n");
	fprintf(fp, "	number					time\n");
	for (i = 0; i < PERMUTATION_TEST_CNT; i++)
	{
		start = clock();
		pAns = randomPermutation(permuNumByComp[i]);
		end = clock();
		if (!pAns)
		{
			printf("Fail to generate the permutation!!!\n");
			return;
		}
		if (pAns)
		{
			free(pAns);
		}
		durationByComp[i] = duration = (double)(end - start) / CLOCKS_PER_SEC;
		printf("\nnumbers:%d, randomPermutation: %.4f seconds, %.4f \n", permuNumByComp[i], duration, log(permuNumByComp[i]));
		fprintf(fp, "%10d				%10.4f\n", permuNumByComp[i], duration);
		if (i > 0)
		{
			printf("\nduration[%d]/duration[%d]=%.2f\n", i, i - 1, durationByComp[i] / durationByComp[i - 1]);
		}
	}
	

	fprintf(fp, "randomPermutationByArray:\n");
	fprintf(fp, "	number					time\n");
	for (i = 0; i < PERMUTATION_TEST_CNT; i++)
	{
		start = clock();
		pAns = randomPermutationByArray(permuNumByArra[i]);
		end = clock();
		if (pAns)
		{
			free(pAns);
		}
		
		durationByArra[i] = duration = (double)(end - start) / CLOCKS_PER_SEC;
		printf("\nnumbers:%d, randomPermutationByArray: %.4f seconds, %.4f\n", permuNumByArra[i], duration, log(permuNumByArra[i]));
		fprintf(fp, "%10d				%10.4f\n", permuNumByArra[i], duration);
		if (i > 0)
		{
			printf("\nduration[%d]/duration[%d]=%.2f\n", i, i - 1, durationByArra[i] / durationByArra[i - 1]);
		}
	}

	fprintf(fp, "randomPermutationBySwap:\n");
	fprintf(fp, "	number					time\n");
	for (i = 0; i < PERMUTATION_TEST_CNT; i++)
	{
		start = clock();
		pAns = randomPermutationBySwap(permuNumBySwap[i]);
		end = clock();
		if (pAns)
		{
			free(pAns);
		}
		durationBySwap[i] = duration = (double)(end - start) / CLOCKS_PER_SEC;
		printf("\nnumbers:%d, randomPermutationBySwap: %.4f seconds, %.4f\n", permuNumBySwap[i], duration, log(permuNumBySwap[i]));
		fprintf(fp, "%10d				%10.4f\n", permuNumBySwap[i], duration);
		if (i > 0)
		{
			printf("\nduration[%d]/duration[%d]=%.2f\n", i, i - 1, durationBySwap[i] / durationBySwap[i - 1]);
		}
	}

	fclose(fp);
}

void dsaPrimeTest()
{
	unsigned long d = 0;
	int res = 0;
	unsigned long* pPrimeTable = NULL;
	double x = 1.0;
	int n = 0;
	printf("\nPrime test, input -1 to end test:\n");

	printf("1. Dec to binary test. \n");
	while (d != -1)
	{
		printf(">>:");
		scanf("%uL", &d);
		if (d == -1)
		{
			break;
		}
		decToBin(d);
	}

	d = 0;
	printf("\n2. Prime Number test, please enter a number(-1 to quit):\n");
	while (d != -1)
	{
		printf(">>:");
		scanf("%uL", &d);
		if (d == -1)
		{
			break;
		}
		res = isPrimeNum(d);
		printf("%d is %s \n", d, res ? "a prime" : "NOT a prime");
	}

	printf("\n3. Input number to generate prime table:\n");
	printf(">>:");
	scanf("%uL", &d);
	pPrimeTable = makePrimeTable(d);
	if (pPrimeTable)
		free(pPrimeTable);

	printf("\n4. QuickPow test, enter base and exponets(0 to quit)\n");
	printf("input format: base exponent\n");
	while (x != 0.0)
	{
		printf(">>:");
		scanf("%lf %d", &x, &n);
		if (x == 0.0 && n < 0)
		{
			printf("invalid input\n"); 
			break;
		}
		printf("pow(%f,%d) = %.4f:\n", x, n, quickPow(x, n));
	}
}



void dsaPivotTest()
{
	//int arrayA[] = { 3,3,4,2,4,4,2,4 };
	//int arrayA[] = { 3,3,4,2,4,4,2,4, 4 };
	//int arrayA[] = { 3,3,4,2,4,4,2,4, 4 };
	int arrayA[64] = { 0 };
	int candidate = -1;
	int len = 64;
	int i = 0, d = 0, k = 0 ;
	char buf[128];

	printf("\n******dsaPivotTest********\n");
	//printNums(arrayA, sizeof(arrayA) / sizeof(arrayA[0]));
	printf("Please enter at most 64 numbers to test:\n");
	fgets(buf, sizeof(buf), stdin);
	for (i = 0; i < len ; i++)
	{
		d = buf[i];
		if (d == ' ' || d == '\n' || d == '\t' || d == ',')
			continue;
		
		if (d == '\0')
			break;
		arrayA[k++] = d - '0';
	}

	candidate = FindPivot(arrayA, k);
	if (candidate != -1)
	{
		printf("\nPivot is:%d\n", candidate);
	}
	else
	{
		printf("\nPivot is not present\n");
	}
}

void dsa_chap2_test()
{
	char c = 0;

	dsaPivotTest();
	dsaPrimeTest();

	printf("\n\nDo you want to test the performance of permutation/random algorithm?...Y or N\n");
	while (c != 'N' && c != 'n' && c != 'Y' && c != 'y')
	{
		scanf("%c", &c);
	}
	
	if (c == 'N' || c == 'n')
	{
		return;
	}
	else if (c == 'y' || c == 'Y')
	{
		printf("\nPlease select the algorithm to test: \n    P: Permutation \n    R: Random\n ");
		do
		{
			scanf("%c", &c);
		} while (c != 'P' && c != 'R');
		

		if (c == 'P')
		{
			dsa_permutation_alg_analysis();
		}
		else if (c == 'R')
		{
			dsa_test_random();
		}
	}
	
}

