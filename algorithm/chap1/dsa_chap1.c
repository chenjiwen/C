
#include "sort.h"
#include <string.h>

/*
 *algorithm description:
 *return the kth biggest number of the array:
 *    use shellsort to sort the array first, return the kth element of the kth array
 */
int selectionKth(int array[], int len, int k){
    shellsort(array, len, INC_SHELL);
    return array[k];
}


#define WORD_BOARD_SIZE 10
enum WordDir
{
    HORIZONTAL,
    VERTICAL,
    DIAG
};

char* wordDict[] =
{
    "this",
    "that",
    "two",
    NULL
};

int isValidWord(char *word, char** dict){
    int i = 0;
    while (dict[i])
    {
        if (!strcmp(word, dict[i])){
            return 0;
        }
    }
    return 1;
}

char** word_puzzle(char board[][WORD_BOARD_SIZE], int boardLineCnt,char **dict) {
    int i = 0, j = 0, k = 0;

    return NULL;
}