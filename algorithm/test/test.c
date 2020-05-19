#include "sort.h"
#include <stdio.h>
#include <time.h>
#include <memory.h>
#include <stdlib.h>

extern int* randomPermutationBySwap(int n);
extern int* randomArrayBySwap(int n);

typedef enum {
	SORT_TEST_DATA_RANDOM,
	SORT_TEST_DATA_PERMUTATION
}TestDataT;

#define MAX_NUMS_TO_PRINTED 200

void printNums(int* pNumArray, int len)
{
	int i = 0;

	printf("\nPrintNums:\n");
	for (i = 0; i < min(len, MAX_NUMS_TO_PRINTED); i++)
	{
		if (i % 5 == 0)
		{
			printf("\n");
		}
		printf("%10d ", *(pNumArray + i));
	}
}

/*
 *void quickSort_test(int nums)
 */
void quickSort_test(int nums, TestDataT testData)
{
	clock_t begin, end;
	int* pNumArra = NULL;

	if (testData == SORT_TEST_DATA_PERMUTATION)
		pNumArra = randomPermutationBySwap(nums);
	else
		pNumArra = randomArrayBySwap(nums);

	begin = clock();
	//quickSort(pNumArra, nums);
	QuickSort(pNumArra, nums);
	end = clock();
	
	printf("\nquickSort: scale:%d, mdedia:%d, duration: %.4f sec\n",nums, *(pNumArra + ((nums >> 1) - 1)), (double)(end - begin) / CLOCKS_PER_SEC);
	printNums(pNumArra, nums);
	free(pNumArra);
}



/*
 *void shellSort_test(int nums)
 */
unsigned long* primeTable = NULL;
unsigned long  primeTableSize = 0;
extern unsigned long* makePrimeTable(unsigned long num);
extern int removeDupGivenVal(int* nums, int numsSize, int val);
void shellSort_test(int nums, TestDataT testData)
{
	clock_t begin, end;
	int* pNumArra = NULL;
	shellSortIncType incType = INC_SEDWIDGE;
	char ch = 0;
	

	printf("\nplease select the increment to test, default is using the Sedgewick increment.\n");
	printf("please input the selction:\n");
	printf("K: Knuth increment\n");
	printf("H: Hibbard increment\n");
	printf("S: Sedgewick increment\n");
	printf("R: Prime number increment\n");

	while (ch != 'K' && ch != 'H' && ch != 'S' && ch != 'R')
	{
		scanf("%c", &ch);
	}
	
	switch (ch)
	{
	case 'K':
		incType = INC_KNUTH;
		break;
	case 'H':
		incType = INC_HIBBARD;
		break;
	case 'S':
		incType = INC_SEDWIDGE;
		break;
	default:
		incType = INC_RANDOM_PRIME;
		break;
	}

	if (testData == SORT_TEST_DATA_PERMUTATION)
		pNumArra = randomPermutationBySwap(nums);
	else
		pNumArra = randomArrayBySwap(nums);

	primeTable = makePrimeTable(nums);
	primeTableSize = removeDupGivenVal(primeTable, nums, 0);

	begin = clock();
	shellSort(pNumArra, nums, incType);
	end = clock();
	
	printf("\nshellsort: scale:%d, median:%d, duration: %.4f sec\n", nums, *(pNumArra + ((nums >> 1) - 1)), (double)(end - begin) / CLOCKS_PER_SEC);
	printNums(pNumArra, nums);
	free(pNumArra);
	free(primeTable);
}

/*
 *void mergeSort_test(int nums)
 */
void mergeSort_test(int nums, TestDataT testData)
{
	clock_t begin, end;
	int* pNumArra = NULL;

	if (testData == SORT_TEST_DATA_PERMUTATION)
		pNumArra = randomPermutationBySwap(nums);
	else
		pNumArra = randomArrayBySwap(nums);

	begin = clock();
	mergeSort(pNumArra, nums);
	end = clock();
	printf("\nmergeSort: scale:%d, %d, duration: %.4f sec\n", nums, *(pNumArra + (nums/2 - 1)), (double)(end - begin) / CLOCKS_PER_SEC);
	printNums(pNumArra, nums);
	free(pNumArra);
	
}

/*
 *void selection_test(int nums)
 */
void selection_test(int nums, int kth, TestDataT testData)
{
	clock_t begin, end;
	int* pNumArra = NULL;
	int value = 0;

	if (testData == SORT_TEST_DATA_PERMUTATION)
		pNumArra = randomPermutationBySwap(nums);
	else
		pNumArra = randomArrayBySwap(nums);
	begin = clock();
	value = selectionKthR(pNumArra, nums, kth);
	end = clock();
	printf("\nselectionKthR: scale:%d, value:%d, duration: %.4f sec\n", nums, value, (double)(end - begin) / CLOCKS_PER_SEC);
	printNums(pNumArra, nums);
	free(pNumArra);

	if (testData == SORT_TEST_DATA_PERMUTATION)
		pNumArra = randomPermutationBySwap(nums);
	else
		pNumArra = randomArrayBySwap(nums);
	begin = clock();
	Qselect(pNumArra, kth, 0, nums - 1);
	value = *(pNumArra+ kth);
	end = clock();	
	printf("\nQselect: scale:%d, value:%d, duration: %.4f sec\n", nums, value, (double)(end - begin) / CLOCKS_PER_SEC);
	printNums(pNumArra, nums);
	free(pNumArra);
}

/*
 *void medianSelection_test(int nums)
 */
void medianSelection_test(int nums, int kth, TestDataT testData)
{
	clock_t begin, end;
	int* pNumArra = NULL;
	int value = 0;

	if (testData == SORT_TEST_DATA_PERMUTATION)
		pNumArra = randomPermutationBySwap(nums);
	else
		pNumArra = randomArrayBySwap(nums);
	begin = clock();
	value = quickSelectKth(pNumArra, nums, kth);
	end = clock();
	
	printf("\nmedianSelection_test: scale:%d, value:%d, duration: %.4f sec\n", nums, value, (double)(end - begin) / CLOCKS_PER_SEC);
	printNums(pNumArra, nums);
	free(pNumArra);
}

void sort_selection_all_test(int nums)
{
	char ch = 0;
	TestDataT testData = SORT_TEST_DATA_PERMUTATION;

	printf("please select the test data:\n");
	printf("R: random data\n");
	printf("P: permutation\n");

	while (ch != 'P' && ch != 'R')
	{
		scanf("%c", &ch);
	}

	if (ch == 'P')
		testData = SORT_TEST_DATA_PERMUTATION;
	else
		testData = SORT_TEST_DATA_RANDOM;

	quickSort_test(nums, testData);
	mergeSort_test(nums, testData);
	shellSort_test(nums, testData);
	selection_test(nums, (nums >> 1) - 1, testData);
	medianSelection_test(nums, (nums >> 1) - 1, testData);
}

#define SORT_TEST_DEFAULT_SCALE 12800000

void sort_algo_perf_analysis() 
{
    int nums = SORT_TEST_DEFAULT_SCALE;
	sortAlgT sortalg = SORT_SHELL;
	TestDataT testData = SORT_TEST_DATA_PERMUTATION;

	printf(
	"\nThis program is testing the  performance of typical sort/selection algorithm.\n \
     Please select the sort/selection algorithm to test:\n \
     1: shell sort \n \
     2: merge sort \n \
     3: quick sort \n \
     4: selection \n \
     5: quickSelection \n \
     6: test all, default scale is %d, select median\n", nums);

	scanf("%d", &sortalg);
	if (sortalg < SORT_DEFAULT || sortalg > SORT_SELECTION_ALL)
	{
		printf("\n input invalid test parameter. default is test all, please waiting ...\n");
		sortalg = SORT_SELECTION_ALL;
	}

	printf("please enter the test scale, the default scale is %d.\n", nums);
	scanf("%d", &nums);

	if (nums < 0)
	{
		printf("Invalid scale inputed, use the default....\n");
		nums = SORT_TEST_DEFAULT_SCALE;
	}
	srand((unsigned)time(NULL));
	switch (sortalg)
	{
	case SORT_SHELL:
		shellSort_test(nums, testData);
		break;
	case SORT_QUICKSORT:
		quickSort_test(nums, testData);
		break;
	case SORT_MERGE:
		mergeSort_test(nums, testData);
		break;
	case SORT_SELECTION_ALL:
	default:
		sort_selection_all_test(nums);
		break;
	}

}


