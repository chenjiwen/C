#include "sort.h"

/*
 *2.3-2:
 *不用哨兵，重写merge的过程，当一旦L/R的数组被复制完成后，把另外一个数组的剩余部分复制到A，程序参考sort.c
 *void merge(int sortedA[], int lenA, int sortedB[], int lenB, int sortedC[])
 *
 * MERGE(A, p, q, r):
 *
 *    let L be a new array of size q - p + 1, R be a new array of size r - q
 *    L[1,...,q - p + 1] = A[p, ..., q]
 *    R[1,...,r - q] = A[q + 1, ..., r]
 *
 *    k = p
 *    while i <= q - p + 1 and j <= r - q:
 *        if L[i] < R[j]:
 *            A[k++] = L[i++]
 *        else
 *            A[k++] = R[j++]
 *
 *    while i <= q - p + 1:
 *        A[k++] = L[i++]
 *
 *    while j <= r - q:
 *        A[k++] = R[j++]
 */

/*
 *对于插入排序写一个递归版本：
 *    把A[1,n-1]递归的排序好，再把A[n]插入到合适的位置
 *
 *复杂度分析：
 * T(n) = T(n - 1) + O(InversionNum of A[n])
 *
 *最坏情况为：
 * T(n) = T(n - 1) + n - 1
 */
void insertionSortR(int A[], int begin, int end)
{
    int i = 0;
    int key = 0;
    if (begin == end)
    {
        return;
    }

    insertionSortR(A, begin, end - 1);

    i = end - 1;
    key = A[end];
    while (i >= 0 && A[i] > key)
    {
        A[i + 1] = A[i];
    }

    A[i + 1] = key;
}

/*
 *2.3-5
 *
 *二分查找的代码，参考sort.c
 *int binarySearch(int A[], int len, int key)
 *
 *证明二分查找最坏情况下的复杂度为O(lgN)
 *
 *二分查找的最坏情况为查找的元素为第一个或者最后一个元素
 *
 *T(n)=T(n/2)+c，c=O(1)为比较的时间，画出递归树，可知T(n) = c*lgN
 */



/*
 *2.3-6
 *反向扫描子数组的时候，能否在最坏的情况下，通过二分查找把插入排序的复杂度改善到O(NlogN)?
 *ANS:
 *    不能，因为binary search可以把搜索的位置从O(j)优化到lgj，但是元素需要移动的位置还是需要O(j)
 */


/*
 *2.3-7
 *给定一个整数的集合和一个目标x，请给出一个算法确定是否存在集合中两个数的和为x
 *
 *O(N^2)
 *O(NlgN)
 *O(N)
 */

/*
 *O(N^2)
 */
int twoSumsBruce(int A[], int len, int x)
{
    int i, j;

    for (i = 0; i < len - 1; i++)
    {
        for (j = i + 1; j < len; j++)
        {
            if (A[j] == x - A[i])
            {
                return 1;
            }
        }
    }

    return 0;
}

/*
 *O(NlogN)
 */
int twoSumsBinarySearch(int A[], int len, int x)
{
    int i = 0;
    int idx = 0;

    for (i = 0; i < len; i++)
    {
        idx = binarySearch(A, len, x - A[i]);
        if (idx != i)
        {
            return 1;
        }
    }

    return 0;
}

/*
 *O(NlogN)
 *对数组先排序，然后利用双指针从左右开始夹逼
 */
int twoSumsForSortedArray(int A[], int len, int x)
{
    int left = 0, right = 0;
	while (left <= right)
	{
		if (A[left] + A[right] == x)
		{
			return 1;
		}
		else if (A[left] + A[right] < x)
		{
			left++;
		}
		else
		{
			right--;
		}
	}

	return 0;
}

int twoSumsPreSorted(int A[], int len, int x)
{
    quickSort(A, len);
    return twoSumsForSortedArray(A, len, x);
}

/*
 *可以建立x-A[i]与i之间的一个map，然后遍历对每一个A[i]，遍历一下x-A[i]的key是否存在于map中
 *O(N)
 */