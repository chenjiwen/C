
#ifndef __SORT_H__
#define __SORT_H__//define header file guarder


#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
	typedef enum shellSortIncType
	{
		INC_SHELL,
		INC_HIBBARD,
		INC_KNUTH,
		INC_SEDWIDGE,
		INC_BEST,
		INC_RANDOM_PRIME
	}shellSortIncType;
	#define SHELL_INC_TABLE_SIZE 64

	typedef enum {
		SORT_DEFAULT = 1,
		SORT_SHELL = SORT_DEFAULT,
		SORT_MERGE,
		SORT_QUICKSORT,
		SORT_INSERTION,
		SORT_BUBBLE,
		SORT_SELECTION,
		SORT_SELECTION_ALL
	}sortAlgT;

	void shellsort(int array[], int len, shellSortIncType incType);
	void bubbleSort(int array[], int len);
	void selectionSort(int array[], int len);
	void shellSort(int array[], int len, shellSortIncType incType);
	void shellSortWithSedgwickIncrement(pNumArra, nums);
	void insertionSort(int array[], int len);
	void countingSort(int array[], int sortedArr[], int len, int k);
	int quickPartition(int A[], int len);
	void quickSort(int A[], int len);
	void mergeSort(int array[], int len);
	int selectionKthR(int A[], int len, int K);
	int quickSelectKth(int A[], int len, int k);
	int binarySearch(int A[], int len, int key);
	void swap(int* x, int* y);
	void merge(int sortedA[], int lenA, int sortedB[], int lenB, int sortedC[]);
	void QuickSort(int A[], int N);
	void Qselect(int A[], int k, int left, int right);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // 






