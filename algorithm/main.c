#include <stdio.h>
#include "sort.h"
#include <string.h>

extern void dsa_chap2_test();
extern void math_test();
extern void sort_algo_perf_analysis();
extern void listTest();
extern void dsaChap3Test();
extern void stackTest();
extern void arrayTest();

typedef enum 
{
	ALG_SORT,
	ALG_SELECTION,
	ALG_BINARY_TREE,
	ALG_HASH,
	ALG_PRI_QUE,
	ALG_BASIC_DATA_STRUCTTURE,
	ALG_DP,
	ALG_DIVIDE_CONCUR,
	ALG_MISC,
	ALG_ALL
}AlgItem;

char* alg_project[] = {
	"sort",
	"selection",
	"hash",
	"heap",
	"list",
	"stack",
	"queue",
	"dynamic programming",
	"divide concur",
	"misc",
	"chap",
	NULL,
};

void dumpProgramParam(int argc, char ** argv)
{
	int i = 0;
	for (i = 0; i < argc; i++)
	{
		printf("argv[%d], %s\n", i, argv[i]);
	}
}

AlgItem getOp(int argc, char** argv)
{
	int i = 0;
	char* pCmd = argv[1];
	char** pAlgList = alg_project;

	while (*pAlgList)
	{
		if (!strcmp(*pAlgList, pCmd + 1))
		{
			return (AlgItem)i;
		}
		i++;
		pAlgList++;
	}

	return ALG_ALL;
}

int main(int argc, char **argv)
{
	AlgItem alg = ALG_ALL;
	int nums[] = { 0,0,0,0,0,0,0,0,0,0,1,0,0 };
	int value = -1;
	int chap = -1;
	dumpProgramParam(argc, argv);
	alg = getOp(argc, argv);
	listTest();
	arrayTest();
	dsaChap3Test();
	if(chap == 2)
	    dsa_chap2_test();

	value = quickSelectKth(nums, 13, 2);

	switch (alg)
	{
	case ALG_SORT:
	case ALG_SELECTION:
		sort_algo_perf_analysis();
		break;
	default:
		break;
	}
	return 0;
}