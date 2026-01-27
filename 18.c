/**
* Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include<stdlib.h>

int comp(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int** minimumAbsDifference(int* arr, int arrSize, int* returnSize, int** returnColumnSizes) {
    qsort(arr, arrSize, sizeof(int), comp);
    *returnSize = 0;
    int min_diff = arr[1] - arr[0];
    for (int i = 1; i < arrSize; i++){
        int diff = arr[i] - arr[i - 1];
        if (diff == min_diff){
            (*returnSize)++;
        }
        if (diff < min_diff){
            *returnSize = 1;
            min_diff = diff;
        }
    }
    int** result = (int**)malloc(sizeof(int*) * (*returnSize));
    int* returnCol = (int*)malloc(sizeof(int) * (*returnSize));
    *returnColumnSizes = returnCol;
    int index = 0;
    for (int i = 1; i < arrSize; i++){
        int diff = arr[i] - arr[i - 1];
        if (diff == min_diff){
            returnCol[index] = 2;
            int* box = (int*)malloc(sizeof(int) * 2);
            box[0] = arr[i - 1];
            box[1] = arr[i];
            result[index++] = box;
        }
    }
    return result;
}
