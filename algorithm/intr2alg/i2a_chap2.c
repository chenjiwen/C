#include "sort.h"

/*
 *2.3-2:
 *�����ڱ�����дmerge�Ĺ��̣���һ��L/R�����鱻������ɺ󣬰�����һ�������ʣ�ಿ�ָ��Ƶ�A������ο�sort.c
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
 *���ڲ�������дһ���ݹ�汾��
 *    ��A[1,n-1]�ݹ������ã��ٰ�A[n]���뵽���ʵ�λ��
 *
 *���Ӷȷ�����
 * T(n) = T(n - 1) + O(InversionNum of A[n])
 *
 *����Ϊ��
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
 *���ֲ��ҵĴ��룬�ο�sort.c
 *int binarySearch(int A[], int len, int key)
 *
 *֤�����ֲ��������µĸ��Ӷ�ΪO(lgN)
 *
 *���ֲ��ҵ�����Ϊ���ҵ�Ԫ��Ϊ��һ���������һ��Ԫ��
 *
 *T(n)=T(n/2)+c��c=O(1)Ϊ�Ƚϵ�ʱ�䣬�����ݹ�������֪T(n) = c*lgN
 */



/*
 *2.3-6
 *����ɨ���������ʱ���ܷ����������£�ͨ�����ֲ��ҰѲ�������ĸ��Ӷȸ��Ƶ�O(NlogN)?
 *ANS:
 *    ���ܣ���Ϊbinary search���԰�������λ�ô�O(j)�Ż���lgj������Ԫ����Ҫ�ƶ���λ�û�����ҪO(j)
 */


/*
 *2.3-7
 *����һ�������ļ��Ϻ�һ��Ŀ��x�������һ���㷨ȷ���Ƿ���ڼ������������ĺ�Ϊx
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
 *������������Ȼ������˫ָ������ҿ�ʼ�б�
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
 *���Խ���x-A[i]��i֮���һ��map��Ȼ�������ÿһ��A[i]������һ��x-A[i]��key�Ƿ������map��
 *O(N)
 */