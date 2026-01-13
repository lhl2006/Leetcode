//
// Created by lhl on 2026/1/13.
//
#include<stdio.h>

int getKthElement(int* nums1, int nums1Size, int* nums2, int nums2Size, int k) {
    if (nums1Size == 0){
        return nums2[k - 1];
    }
    if (nums2Size == 0){
        return nums1[k - 1];
    }
    if (k == 1){
        return nums1[0] < nums2[0] ? nums1[0] : nums2[0];
    }
    int nums1Index = k / 2 - 1 > nums1Size - 1 ? nums1Size - 1 : k / 2 - 1;
    int nums2Index = k / 2 - 1 > nums2Size - 1 ? nums2Size - 1 : k / 2 - 1;
    if (nums1[nums1Index] <= nums2[nums2Index]){
        return getKthElement(nums1 + nums1Index + 1, nums1Size - nums1Index - 1, nums2, nums2Size, k - nums1Index - 1);
    }
    return getKthElement(nums1, nums1Size, nums2 + nums2Index + 1, nums2Size - nums2Index - 1, k - nums2Index - 1);
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int size = nums1Size + nums2Size;
    if (size % 2 == 0){
        return (double)(getKthElement(nums1, nums1Size, nums2, nums2Size, size / 2) + getKthElement(
            nums1, nums1Size, nums2, nums2Size, size / 2 + 1)) / 2;
    }
    return (double)getKthElement(nums1, nums1Size, nums2, nums2Size, size / 2 + 1);
}

int main(void) {
    int nums1[] = {100};
    int nums2[] = {3, 4};
    printf("%.5lf", findMedianSortedArrays(nums1, 1, nums2, 2));
}

/*double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size);

int main(void) {
    int nums1[] = {1, 2};
    int nums2[] = {3, 4};
    printf("%.5lf", findMedianSortedArrays(nums1, 2, nums2, 2));
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int aim_index = (nums1Size + nums2Size) / 2;
    bool need_avg = (nums1Size + nums2Size) % 2 == 0;
    int from1 = 0, from2 = 0;
    int drop = 0;
    // while
    while (aim_index - (drop - 1) > 32){
        int index1 = (from1 + nums1Size - 1) / 2, index2 = (from2 + nums2Size - 1) / 2;
        int num1 = nums1[index1];
        int num2 = nums2[index2];

        if (num1 <= num2){
            drop = index1 - from1 + 1;
            from1 = index1 + 1;
        }
        else{
            drop = index2 - from2 + 1;
            from2 = index2 + 1;
        }
    }
    while (1){
        if (from1 + from2 == aim_index){
            if (!need_avg){
                return nums1[from1] < nums2[from2] ? (double)nums1[from1] : (double)nums2[from2];
            }
            int min1 = nums1[from1 + 1], min2 = nums2[from2 + 1];
            if (nums1[from1 + 2] < min1 || nums1[from1 + 2] < min2){
                if (min1 < min2){
                    min2 = nums1[from1 + 2];
                }
                else{
                    min1 = nums1[from1 + 2];
                }
            }
            if (nums2[from2 + 2] < min1 || nums2[from2 + 2] < min2){
                if (min1 < min2){
                    min2 = nums2[from2 + 2];
                }
                else{
                    min1 = nums2[from2 + 2];
                }
            }
            return (double)(min1 + min2) / 2;
        }
        if (nums1[from1] < nums2[from2]){
            from1++;
        }
        else{
            from2++;
        }
    }
}*/
