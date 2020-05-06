#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

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
 *    swap the two neighbour, the heavier up, the lighter down 
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

	int incTable[] = { 5, 3, 1};

	for (k = 0, increment = incTable[k]; k < (sizeof(incTable)/sizeof(incTable[0])) && (increment = incTable[k]); k++){
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
	return;
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
	mergeSort(array, mid);             //sort the first half
	mergeSort(array + mid, len - mid); //sort the last half
	merge(array, mid, array + mid, len - mid, pSortedArray);//merge the first and last half
	memcpy(array, pSortedArray, len*sizeof(int));
	free(pSortedArray);
}

/*
 *quickPartition(int A[], int len):
 *    partition the A[] into three parts:  <= pivot >= pivot 
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
		else
			swap(A + i, A + j);
	}

	A[i] = pivot;
	return i;
}

/*
 *quickSort(int A[], int len):
 *    A[]: the array to sort
 *    len: the length of the array to sort
 */
void quickSort(int A[], int len)
{
	int partitionIdx;
	if (len <= 1)
		return;
	

	partitionIdx = quickPartition(A, len);

	quickSort(A, partitionIdx);//quickSort the first part
	quickSort(A + partitionIdx + 1, len - partitionIdx - 1);//quickSort the last part
}