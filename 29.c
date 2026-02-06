#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int locate(int* nums, int numsSize, long long tar) {
    int left = 0, right = numsSize - 1;
    int mid = 0;
    while (left + 32 < right){
        mid = left + (right - left) / 2;
        if (nums[mid] <= tar) left = mid;
        else if (nums[mid] > tar) right = mid - 1;
    }
    while (left < numsSize - 1 && nums[left + 1] <= tar) left++;
    return left;
}

int minRemoval(int* nums, int numsSize, int k) {
    int max_size = 1;
    qsort(nums, numsSize, sizeof(int), compare);
    for (int i = 0; i < numsSize; i++){
        int temp = locate(nums, numsSize, (long long)k * nums[i]);
        if (temp - i + 1 > max_size) max_size = temp - i + 1;
    }
    return numsSize - max_size;
}


int main() {
    int box[4] = {1, 6, 2, 9};
    int result = minRemoval(box, 4, 3);
    printf("%d\n", result);
}


/*int locate(int* nums, int numsSize, long long tar) {
    int left = 0;
    int right = numsSize - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] <= tar) {
            // mid 可能是答案，但也可能右边还有更大的符合条件的
            // 所以让 left 往右移，尝试找更大的
            left = mid + 1;
        } else {
            // mid 太大了，答案肯定在左边
            right = mid - 1;
        }
    }
    // 循环结束时，right 指向的就是小于等于 tar 的最后一个元素下标
    // 如果所有元素都大于 tar，right 会变成 -1
    return right;
}*/
