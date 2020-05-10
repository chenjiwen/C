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

int ramdonInt(int m)
{
    return rand() % m;
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


int nums[1000];

void dsa_test_random()
{
	int count = 0, limit = 100;
	int lineCnt = 5;
	int i = 0;
    int m = 0, n = 0;

	printf("Please enter two number, number of random and limit of random:");
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
	printf("\nplease enter two numbers m and n to generate random number,m < n:");
	scanf_s("%d,%d", &m, &n);
	if (m >= n)
	{
		printf("make sure the first number is smaller than the second!\n");
		goto INPUT;
	}

	for (i = 0; i < count; i++)
	{
		if (i % lineCnt == 0)
		{
			printf("\n");
		}
		printf("%4d ", nums[i] = random(m, n));
	}

	quickSort(nums, sizeof(nums) / sizeof(nums[0]));
	printf("\nsorted nums:");
	for (i = 0; i < count; i++)
	{
		if (i % lineCnt == 0)
		{
			printf("\n");
		}
		printf("%4d ", nums[i]);
	}
}

#define PERMUTATION_TEST_CNT 8
#define MAX_PATH_LENGTH 1024
void dsa_permutation_alg_analysis() {
	int i = 0;
	int* pAns = NULL;
	clock_t start, end;
	double duration;
	int permuNumByComp[PERMUTATION_TEST_CNT] = { 500, 1000, 2000, 4000, 8000, 16000, 32000, 64000 };
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
	fp = fopen(pFileName, "wb");
	if (!fp)
	{
		printf("Fail to open file:%s", pFileName);
		return;
	}

	srand((unsigned)time(NULL));

	fprintf(fp, "randomPermutation:\n");
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
		printf("numbers:%d, randomPermutation: %.4f seconds, %.4f \n", permuNumByComp[i], duration, log(permuNumByComp[i]));
		fprintf(fp, "%10d				%10.4f\n", permuNumByComp[i], duration);
		if (i > 0)
		{
			printf("duration[%d]/duration[%d]=%.2f\n", i, i - 1, durationByComp[i] / durationByComp[i - 1]);
		}
	}
	

	fprintf(fp, "randomPermutation:\n");
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
		printf("numbers:%d, randomPermutationByArray: %.4f seconds, %.4f\n", permuNumByArra[i], duration, log(permuNumByArra[i]));
		fprintf(fp, "%10d				%10.4f\n", permuNumByArra[i], duration);
		if (i > 0)
		{
			printf("duration[%d]/duration[%d]=%.2f\n", i, i - 1, durationByArra[i] / durationByArra[i - 1]);
		}
	}

	fprintf(fp, "randomPermutation:\n");
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
		printf("numbers:%d, randomPermutationBySwap: %.4f seconds, %.4f\n", permuNumBySwap[i], duration, log(permuNumBySwap[i]));
		fprintf(fp, "%10d				%10.4f\n", permuNumBySwap[i], duration);
		if (i > 0)
		{
			printf("duration[%d]/duration[%d]=%.2f\n", i, i - 1, durationBySwap[i] / durationBySwap[i - 1]);
		}
	}

	fclose(fp);
}

void dsa_chap2_test()
{
	char c;
	printf("Do you want to try the permutation algorithm performance test?Y or N\n");
	scanf("%c", &c);
	if (c == 'N' || c == 'n')
	{
		return;
	}
	dsa_permutation_alg_analysis();
}