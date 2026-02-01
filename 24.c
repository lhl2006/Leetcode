#include<limits.h>
void check(int *min2,int *min3,int num){
    if(num < *min3) *min3 = num;
    if(*min3 < *min2){
        int temp = *min2;
        *min2 = *min3;
        *min3 = temp;
    }
}

int minimumCost(int* nums, int numsSize) {
    int min1 = nums[0], min2 = INT_MAX, min3 = INT_MAX;
    for(int i = 1;i < numsSize;i++){
        check(&min2,&min3,nums[i]);
    }
    return min1 + min2 + min3;
}