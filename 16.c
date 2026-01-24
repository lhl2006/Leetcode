#include<stdlib.h>
#include<limits.h>
#define MAX 100005

int comp(const void* a, const void* b) {
	if (*(int*)a > *(int*)b){
		return 1;
	}
	return -1;
}

int minPairSum(int* nums, int numsSize) {
	qsort(nums, numsSize, sizeof(int), comp);
	int max = INT_MIN;
	for (int i = 0; i < numsSize / 2; i++){
		int sum = nums[i] + nums[numsSize - i - 1];
		if (sum > max){
			max = sum;
		}
	}
	return max;
}
