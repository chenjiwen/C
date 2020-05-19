/*
 *sort.c
 *
 *implement several typical sort algorithm and selection algorithm introduced by:
 *
 * <INTRODUCTION TO ALGORITHM>
 * <DATA STRUCTURE AND ALGORITHM ANALYSIS>
 *
 *BUBBLE SORT
 *SELECTION SORT
 *INSERTION SORT
 *MERGE SORT
 *QUICK SORT
 *BIBARY_SEARCH
 *QUICK_SELECTION
 *
 */

#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
/*
 *swap the two value x, y
 */
void swap(int* x, int* y) {
	int temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

/*
 *Bubble-sort:
 *    like the bubble in water, the heavier bubble will sink, the lighter bubble will come-up
 *    swap the two neighbor array, the heavier up, the lighter down 
 *
 */
void bubbleSort(int array[], int len) {
	int i, j;

	for (i = 0; i < len - 1; i++){
		for (j = 0; j < len - i - 1; j++) {
			if (array[j] > array[j + 1]){
				swap(array + j, array + j + 1);
			}
		}
	}
}



/*
 *selection sort:
 *    select the min from the A[0,...,n-1], swap(min/A[k], with A[0])
 *    select the min from the A[1,...,n-1], swap(min/A[k], with A[1])
 *    ...
 *
 *    select the min from the A[i,...,n-1], swap(min/A[k], with A[1])
 *    ,,,
 *    end when i = n-2
 */
void selectionSort(int array[], int len) {
	int min = 0, i = 0, j = 0, k= 0;

	for (i = 0; i < len; i++) {
		min = array[i];
		k = i;
		for (j = i + 1; j < len; j++){
			if (min > array[j]){
				min = array[j];
				k = j;
			}
		}
		swap(array + i, array + k);
	}
}

/*
 *insertion sort:
 *    suppose the sub-array A[0,...i-1] is well sorted, insert A[i] into the sorted sub-array
 *A[0, ... ,  i - 1]
 *
 *    key = A[i]
 *    from i - 1 to 0
 *    compare key with A[j], if A[j] < key. move A[j] afterwords
 *
 */
void insertionSort(int array[], int len) {
	int key, i, j;

	for (i = 1; i < len; i++){
		key = array[i];
		for (j = i - 1; j >= 0 && array[j] > key; j--){
			array[j + 1] = array[j];
		}
		array[j + 1] = key;
	}
}

/*
 *int ShellOptIncrement(int pShellIncTable[], int tableLen, int limit):
 *     pShellIncTable[]: table to store the optimized shell increment
 *     tableLen:         table size of the shall table
 *     limit:            max limit of the shell increment
 *
 *    9*4^i - 9*2^i + 1
 *    4^i - 3*2^i + 1
 */
int ShellOptIncrement(int pShellIncTable[], int tableLen, int limit)
{
	int i = 0, j = 0, k = 0;
	int increment = 0;
	int tableB[32] = {0};
	int tableS[32] = {0};

	i = 0;
	while (increment <= limit && i < min(tableLen,16))
	{
		tableB[i] = increment = (9 * ((((1 << i) - 1)) << i)) + 1;
		i++;
	}
	

	j = 2;
	increment = 0;
	while (increment <= limit && j < min(tableLen, 16))
	{
		tableS[j-2] = increment = (((1 << j) - 3) << j) + 1;
		j++;
	}
	
	j -= 2;
	merge(tableB, i, tableS, j, pShellIncTable);

	return i + j;
}

/*
 *shell sort(diminishing increment sort):
 *
 *    increment/step table: h[k] > h[k-1] >... > h[0] = 1
 *    use the insertion sort to sort the subarray A[i], A[i + h[j]], A[i+2*h[j]],... A[i+n*h[j]] , where 0<=j<=k
 *
 */
void shellsort(int array[], int len, shellSortIncType incType)
{
	int increment;
	int i, j ,k;
	int temp;

	int incTable[SHELL_INC_TABLE_SIZE] = {1, 5, 0};

	int index = 0;

	index = ShellOptIncrement(incTable, SHELL_INC_TABLE_SIZE, len >> 1);

	for (k = 0; k < index; k++){
		increment = incTable[index - k - 1];
		for (i = increment; i < len; i++){
			temp = array[i];
			for (j = i - increment; j >= 0; j -= increment) {
				if (array[j] > temp) {
					array[j + increment] = array[j];
				}else{
					break;
				}
			}
			array[j + increment] = temp;
		}
	}
}

/*
 *shellSort internally
 */
void shellSortByIncrement(int array[], int len, int increment)
{
	int i =0, j = 0;
	int temp;

	for (i = increment; i < len; i++) {
		temp = array[i];
		for (j = i - increment; j >= 0; j -= increment) {
			if (array[j] > temp) 
				array[j + increment] = array[j];
			else 
				break;
		}
		array[j + increment] = temp;
	}
	
}

/*
 *    9*4^i - 9*2^i + 1
 *    4^i - 3*2^i + 1
 */
void shellSortWithSedgwickIncrement(int array[], int len)
{
	int i = 0, j= 0, increment = 0;
	int inc1, inc2;

	while (increment < len)
	{
		increment = (9 * ((((1 << i) - 1)) << i)) + 1;
		i++;
	}
	i--;


	j = 0;
	increment = 0;
	while (increment < len)
	{
		increment = (((1 << j) - 3) << j) + 1;
		j++;
	}
	j--;

	while (i && j)
	{
		
		inc1 = (9 * ((((1 << i) - 1)) << i)) + 1;
		inc2 = (((1 << j) - 3) << j) + 1;
		if (inc1 > inc2)
		{
			increment = inc1;
			i--;
		}
		else
		{
			increment = inc2;
			j--;
		}

		shellSortByIncrement(array, len, increment);
	}

	while (j >= 0)
	{
		increment = (((1 << j) - 3) << j) + 1;
		if (increment < 0)
			break;
		shellSortByIncrement(array, len, increment);
		j--;
	}

	while (i >= 0)
	{
		increment = (9 * ((((1 << i) - 1)) << i)) + 1;
		shellSortByIncrement(array, len, increment);
		i--;
	}
}

/*
 *increment = 2^k - 1
 */
void shellSortWithHillbardIncrement(int array[], int len)
{
	int step = 0, i = 0;

	while (step < len)
	{
		step = (1 << i) - 1;
		i++;
	}

	i--;

	while (i > 0)
	{
		step = (1 << i) - 1;
		shellSortByIncrement(array, len, step);
		i--;
	}
}

/*
 * increment = (3^k + 1)/2
 */
void shellSortWithKnuthIncrement(int array[], int len)
{
	int step = 0;
	int i = 0;

	while (step < len)
	{
		step = (int)pow(3, i) + 1;
		step >>= 1;
		i++;
	}

	i--;


	while (i >= 0)
	{
		step = (int)pow(3, i) + 1;
		step >>= 1;
		shellSortByIncrement(array, len, step);
		i--;
	}
}

extern unsigned long* makePrimeTable(unsigned long num);
extern int removeDupGivenVal(int* nums, int numsSize, int val);
extern unsigned long* primeTable;
extern unsigned long  primeTableSize ;
/*
 *the increment is from the prime table
 */
void shellRandomPrimeIncrement(int array[], int len)
{
	unsigned long* primeT = NULL;
	int size = 0;
	int allocated = 0;


	primeT = primeTable;
	size = primeTableSize;

	if (!primeT)
	{
		primeT = makePrimeTable(len);
		allocated = 1;
		size = removeDupGivenVal(primeT, len, 0);
	}


	while (size)
	{
		shellSortByIncrement(array, len, primeT[size - 1]);
		size >>= 1;
	}

	shellSortByIncrement(array, len, 1);

	if(allocated)
	    free(primeT);
	
}

void shellSort(int array[], int len, shellSortIncType incType)
{
	switch (incType)
	{
	case INC_HIBBARD:
		shellSortWithHillbardIncrement(array, len);
		break;
	case INC_KNUTH:
		shellSortWithKnuthIncrement(array, len);
		break;
	case INC_SEDWIDGE:
		shellSortWithSedgwickIncrement(array, len);
		break;
	case INC_BEST:
	default:
		shellRandomPrimeIncrement(array,len);
		break;
	}
}

/*
 *counting sort:
 *    
 */
void countingSort(int array[], int sortedArr[], int len, int k) {
	int* countArr = NULL;
	int i = 0;

	countArr = (int*)malloc((k + 1) * sizeof(int));
	if (!countArr)
		return;
	

	memset(countArr, 0, (k + 1) * sizeof(int));

	for (i = 0; i < len; i++)
		countArr[array[i]]++;


	for (i = 1; i <= k; i++)
		countArr[i] += countArr[i - 1];


	for (i = len - 1; i >= 0; i--){
		sortedArr[countArr[array[i]] - 1] = array[i];
		countArr[array[i]]--;
	}

	free(countArr);
}

/*
 *merge(int sortedA[], int lenA, int sortedB[], int lenB, int sortedC[]):
 *    sortedA: sorted Array[]
 *    sortedB: sorted Array[]
 *    sortedC: used to store the merge of sortedA and sortedB
 *    lenA:    length of sortedA
 *    lenB:    length of sortedB
 *
 *algorithm description:
 *    C[k++] = A[i++] if A[i] > B[j]
 *           = B[j++] if A[i] <= B[j]
 */
void merge(int sortedA[], int lenA, int sortedB[], int lenB, int sortedC[])
{
	int i, j, k;

	i = j = k = 0;
	while (i < lenA && j < lenB){
		if (sortedA[i] < sortedB[j])
			sortedC[k++] = sortedA[i++];
		else
			sortedC[k++] = sortedB[j++];
	}

	while (i < lenA)
		sortedC[k++] = sortedA[i++];

	while (j < lenB)
		sortedC[k++] = sortedB[j++];
}

/*
 *void mergeSort(int array[], int len):
 *    A[]: the array to sort
 *    len: the length of the array to sort
 *
 *algorithm description:
 *    divide the array into two small parts and mergeSort for each part, then merge the two sorted parts 
 *    step1: recursively call mergeSort(A, mid)
 *    step2: recursively call mergeSort(A + mid, len - mid)
 *    step3: merge the first sorted part and the second sorted part
 */
void mergeSort(int array[], int len)
{
	int mid;
	if (len <= 1)
		return;
	

	int* pSortedArray;
	pSortedArray = (int*)malloc(sizeof(int) * len);
	if (!pSortedArray)
		return;
	
	mid = len >> 1;
	mergeSort(array, mid);                                  //mergeSort the first half
	mergeSort(array + mid, len - mid);                      //mergeSort the last half
	merge(array, mid, array + mid, len - mid, pSortedArray);//merge the first and last half
	memcpy(array, pSortedArray, len*sizeof(int));
	free(pSortedArray);
}

/*
 *quickPartition(int A[], int len):
 *    A[]: the array to be partitioned
 *    len: length of the array
 *    return the index which partitioned the array to three parts(index of the pivot)
 *
 *algorithm description:
 *    partition the A[] into three parts:  (<=) (pivot) (>= pivot) 
 *    set two pointer: i, j
 *    i is from start of the array, j is from the end of the array
 *    find i which is larger than pivot, find j which is smaller than pivot
 *    exchange A[i] with A[j] till i equals to j
 *
 */
int quickPartition(int A[], int len) 
{
	int pivot;
	int i, j;

	pivot = A[(len - 1) >> 1];//choose the medium as the pivot
	i = 0;                    //from the begin of A
	j = len - 1;              //from the end of A

	while (i < j){
		if (A[i] < pivot)
			i++;
		else if (A[j] > pivot)
			j--;
		else if (A[i] == A[j])
		{
			if (i < len - j)
				i++;
			else
				j--;
		}
		else
			swap(A + i, A + j);	
	}

	return i;
}

int quick_sort_partition(int left_idx, int right_idx, int array[])
{
	int sentential = 0;
	int idx = 0;
	int sentential_idx = 0;
	int temp = 0;
	int mid = 0;

	//
	mid = (left_idx + right_idx) >> 1;

	//哨兵可以选取任意位置
	sentential_idx = mid;
	sentential = array[sentential_idx];

	for (idx = left_idx; idx < right_idx; )
	{   //找出左半部不小于给定哨兵的元素
		if (array[idx] < sentential)
		{
			idx++;
			//当前左半部的元素小于给定的元素，继续找
			continue;
		}
		else
		{
			//当前的头部元素不小于哨兵元素，从尾部找出尾部小于给定元素的位置
			while ((right_idx > idx) && (array[right_idx] >= sentential))
				right_idx--;
			if (sentential == array[right_idx])
				sentential_idx = right_idx;
			//找到了一个小于哨兵的元素，与前半部的小于哨兵元素交换
			if (right_idx != idx)
			{
				temp = array[right_idx];
				array[right_idx] = array[idx];
				array[idx] = temp;
			}

			//如果idx == right_idx，则表明，当前元素与哨兵相等,退出循环，直接返回当前位置
		}

	}
	if (array[idx] < sentential)
	{
		swap(&array[++idx], &array[sentential_idx]);
	}
	else if (array[idx] > sentential)
	{
		swap(&array[idx], &array[sentential_idx]);
	}
	return idx;
}

int quickPartitionT(int A[], int len)
{
	int i, j, pivot;

	i = -1;//the last element which is not bigger than pivot
	j = 0; //the current element to be process, j - 1 is the last element which is not smaller than pivot
	pivot = A[len - 1];

	for (j = 0; j < len - 1; j++)
	{
		if (A[j] < pivot)
		{
			swap(&A[i + 1], &A[j]);
			++i;
		}
	}

	swap(&A[i + 1], &A[len - 1]);
	return i + 1;
}

/*
 *quickSort(int A[], int len):
 *    A[]: the array to sort
 *    len: the length of the array to sort
 *
 *algorithm description:
 *    1. call quickPartition to partition the array into three parts:
 *    <part1: No greater than pivot>-- <part2: pivot>-- <part3: No smaller than pivot>
 *    2. recursively quicksort part1
 *    3. recursively quicksort part2
 * 
 */
void quickSort(int A[], int len)
{
	int partitionIdx = 0;

	//partitionIdx should be possible 0 when recursively called, thus here is len <= 1
	if (len <= 1)                    
		return;
	

	partitionIdx = quick_sort_partition(0, len - 1, A);

	quickSort(A, partitionIdx);                             //quickSort the first part
	quickSort(A + partitionIdx + 1, len - partitionIdx - 1);//quickSort the last part
}


/*
 *binarySearch(int A[], int len, int key):
 *    A[]: the array to search
 *    len: length of the array
 *    key: the key to search from the array A[]
 *
 *algorithm description:
 *    1. mid = len/2
 *    2. compare the key with A[mid], if A[mid] == key, return key
 *    3. if A[mid] < key, search the key from right part
 *    4. if A[mid] > key, search the key from the left part
 */
int binarySearch(int A[], int len, int key)
{
	int low, mid, high;

	low = 0;
	high = len - 1;
	while (low <= high)
	{
		mid = low + ((high - low) >> 1);//(low + high)/2 may overflow
		if (A[mid] == key)
		{
			return mid;
		}
		else if (A[mid] < key)
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}

	return -1;
}

/*
 *recursive version of binarySearch
 */
int binarySearchR(int A[], int low, int high, int key)
{
	int mid;

	if (low > high)
	{
		return -1;
	}

	mid = low + ((high - low) >> 1);//(low + high)/2 may overflow
	if (A[mid] == key)
	{
		return mid;
	}
	else if (A[mid] < key)
	{
		return binarySearchR(A, low, mid - 1, key);
	}
	else
	{
		return binarySearchR(A, mid + 1, high, key);
	}
}

/*
 *selectionKthR(int A[], int len, int K):
 *search the Kth smallest key from the array A[]
 *
 *
 */
int selectionKthR(int A[], int len, int K)
{
	int ith = -1;

	ith = quickPartition(A, len);
	if (K == ith)
	{
		return A[K];
	}
	else if(ith < K)
	{
		return selectionKthR(A + ith + 1, len - ith - 1, K - ith - 1);
	}
	else
	{ 
		return selectionKthR(A, ith, K);
	}
}

/*
 *quickSelectionPartition(int A[], int len, int pivot):
 *    A[]: the array to be partitioned
 *    len: length of the array to be partitioned
 *    pivot: partition the array with pivot
 *    
 *return the partition index of the pivot
 *
 */
int quickSelectionPartition(int A[], int len, int pivot)
{
	int i, j;
	i = 0;                    //from the begin of A
	j = len - 1;              //from the end of A


	i = 0;                    //from the begin of A
	j = len - 1;              //from the end of A

	while (i < j) {
		if (A[i] < pivot)
			i++;
		else if (A[j] > pivot)
			j--;
		else if (A[i] == A[j])
		{
			if (i < len - j)
				i++;
			else
				j--;
		}
		else
			swap(A + i, A + j);
	}	
	return i;
}

/*
 *quickSelectKth(int A[], int len, int k):
 *    A[]: the array to be selected
 *    len: length of array A[]
 *    k:   select the kth smallest, k is from 0 to len - 1
 *
 *algorithm description:
 *    1. make each 5 elements from the A[] in a group
 *    2. use insertion-sort to sort the [n/5] small arrays and add the median of each small array into a temp array medianArray
 *    3. call quickSelectKth recursively to find the median of temp array medianArray
 *    4. use the median of medianArray to partition the A[] and get the partition_index
 *    5. compare the partition index with k, if k == partition_index return A[k]
 *    6. if k < partition_index, recursively call quickSelectKth for the left part
 *    7. if k > partition_index, recursively call quickSelectKth for the right part
 */
int quickSelectKth(int A[], int len, int k)
{
	int size = 5, step = 0, j = 0;
	int i = 0, median = 0, medianIdx = 0, partitionIdx = -1;

	int* medianArra;
	int medianArraSize;

	if (len == 1)
	{
		return A[0];
	}

	size = 5;
	medianArraSize = (len % size == 0) ? (len / size) : (len / size + 1);
	medianArra = (int*)malloc(medianArraSize * sizeof(A[0]));

	if (!medianArra)
	{
		return -1;
	}

	i = 0;
	j = 0;
	while (i < len)
	{
		step = min(size, len - i);
		insertionSort(A + i, step);
		*(medianArra + j++) = *(A + i + (step >> 1));
		i += step;
	}

	medianIdx = medianArraSize >> 1;
	if (!(medianArraSize & 0x1))
	{
		medianIdx -= 1;
	}

	median = quickSelectKth(medianArra, medianArraSize, medianIdx);
	free(medianArra);
	medianArra = NULL;

	partitionIdx = quickSelectionPartition(A, len, median);
	if (partitionIdx == k)
	{
		return A[k];
	}
	else if (partitionIdx < k)
	{
		return quickSelectKth(A + partitionIdx + 1, len - partitionIdx - 1, k - partitionIdx - 1);
	}
	else
	{
		return quickSelectKth(A, partitionIdx, k);
	}
}

int median3(int A[], int left, int right)
{
	int mid = left + ((right - left) >> 1);

	if (A[left] > A[mid])
		swap(A + left, A + mid);

	if (A[left] > A[right])
		swap(A + left, A + right);

	if (A[mid] > A[right])
		swap(A + mid, A + right);

	swap(A + mid, A + right - 1);

	return A[right - 1];
}

#define CUTTOFF (20)

void Qsort(int A[], int left, int right)
{
	int i = 0, j = 0;
	int pivot = -1;

	if (left + CUTTOFF <= right)
	{
		pivot = median3(A, left, right);

		i = left;
		j = right - 1;

		for (;;)
		{
			while (A[++i] < pivot);
			while (A[--j] > pivot);
			if (i < j)
				swap(A + i, A + j);
			else
				break;
		}

		swap(A + i, A + right - 1);
		Qsort(A, left, i - 1);
		Qsort(A, i + 1, right);
	}
	else
	{
		insertionSort(A + left, right - left + 1);
	}
}

void QuickSort(int A[], int N)
{
	Qsort(A, 0, N - 1);
}

void Qselect(int A[], int k, int left, int right)
{
	int i = 0, j = 0;
	int pivot = -1;

	if (left + CUTTOFF <= right)
	{
		pivot = median3(A, left, right);

		i = left;
		j = right - 1;

		for (;;)
		{
			while (A[++i] < pivot);
			while (A[--j] > pivot);
			if (i < j)
				swap(A + i, A + j);
			else
				break;
		}

		swap(A + i, A + right - 1);

		if(k <= i)
		    Qselect(A, k, left, i - 1);
		else
			Qselect(A, k, i + 1, right);
	}
	else
	{
		insertionSort(A + left, right - left + 1);
	}
}