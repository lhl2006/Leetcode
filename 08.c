#include <stdlib.h>
// 602 * 601 / 2 = 180901
#define MAX 200000
#define NUM 1000000007

int compare(const void *a, const void *b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}


int maximizeSquareArea(int m, int n, int* hFences, int hFencesSize, int* vFences, int vFencesSize) {
    qsort(hFences , hFencesSize, sizeof(int), compare);
    qsort(vFences , vFencesSize, sizeof(int), compare);
    int *box1 = malloc(sizeof(int) * MAX);
    int index1 = 0;
    int *box2 = malloc(sizeof(int) * MAX);
    int index2 = 0;
    
    for(int i = 0;i < hFencesSize;i++){
        box1[index1++] = hFences[i] - 1;
        box1[index1++] = m - hFences[i];
    }
    box1[index1++] = m - 1;
    for(int i = 0;i < vFencesSize;i++){
        box2[index2++] = vFences[i] - 1;
        box2[index2++] = n - vFences[i];
    }
    box2[index2++] = n - 1;
    for(int i = 0;i < hFencesSize;i++){
        for(int j = i + 1;j < hFencesSize;j++){
            box1[index1++] = hFences[j] - hFences[i];
        }
    }
    for(int i = 0;i < vFencesSize;i++){
        for(int j = i + 1;j < vFencesSize;j++){
            box2[index2++] = vFences[j] - vFences[i];
        }
    }
    qsort(box1 , index1, sizeof(int), compare);
    qsort(box2 , index2, sizeof(int), compare);
    for(int i = index1 - 1,j = index2 - 1;i >= 0 && j >= 0;){
        if(box1[i] == box2[j]){
            long ans = (long)box1[i] * box1[i] % NUM;
            return (int)ans;
        }
        if(box1[i] < box2[j]){
            j--;
        }else{
            i--;
        }
    }
    return -1;
}