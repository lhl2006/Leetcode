//
// Created by Gemini on 2026/2/4.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long maxSumTrionic(int* nums, int numsSize) {
    if (numsSize < 4) return 0; 

    int n = numsSize;
    long long* inc = (long long*)malloc(n * sizeof(long long)); // 记录以 i 结尾的最大递增子数组和 (len >= 1)
    long long* dec = (long long*)malloc(n * sizeof(long long)); // 记录以 i 开始的最大递增子数组和 (len >= 1)
    long long* prefixSum = (long long*)malloc((n + 1) * sizeof(long long));

    // 1. 优化后的左侧递增和 (Left to Right)
    // inc[i] 表示：在必须包含 nums[i] 的情况下，以 i 结尾的最大递增序列和
    inc[0] = nums[0];
    for (int i = 1; i < n; i++) {
        if (nums[i] > nums[i - 1]) {
            // 如果前缀和是负的，不如不要，但必须保持递增结构。
            // 这里的 max(0, inc[i-1]) 意味着如果前面的部分拖累了总和，我们就只取当前这一段的尾巴
            // 但具体的 "长度>=2" 限制我们在最后合并时通过 nums[start] + inc[start-1] 来保证
            long long prev = inc[i - 1] > 0 ? inc[i - 1] : 0;
            inc[i] = nums[i] + prev;
        } else {
            inc[i] = nums[i];
        }
    }

    // 2. 优化后的右侧递增和 (Right to Left)
    // dec[i] 表示：在必须包含 nums[i] 的情况下，以 i 开始的最大递增序列和
    dec[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        if (nums[i] < nums[i + 1]) {
            long long next = dec[i + 1] > 0 ? dec[i + 1] : 0;
            dec[i] = nums[i] + next;
        } else {
            dec[i] = nums[i];
        }
    }

    // 3. 前缀和用于计算中间段
    prefixSum[0] = 0;
    for (int i = 0; i < n; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    long long maxVal = LLONG_MIN;
    int found = 0;

    // 4. 寻找波峰(start) 和 波谷(end)
    int i = 0;
    while (i < n - 1) {
        if (nums[i] > nums[i + 1]) { // 发现下降段
            int start = i;
            while (i < n - 1 && nums[i] > nums[i + 1]) {
                i++;
            }
            int end = i;

            // 检查是否构成合法的三段式结构
            // start > 0 且 nums[start] > nums[start-1] 保证左边有上升段
            // end < n-1 且 nums[end] < nums[end+1] 保证右边有上升段
            if (start > 0 && nums[start] > nums[start - 1] && 
                end < n - 1 && nums[end] < nums[end + 1]) {
                
                // 计算三段式总和
                // 左翼 (保证长度>=2): nums[start] + 最优的前驱 inc[start-1]
                long long leftPart = nums[start] + inc[start - 1];
                
                // 右翼 (保证长度>=2): nums[end] + 最优的后继 dec[end+1]
                long long rightPart = nums[end] + dec[end + 1];
                
                // 中间段 (不包含 start 和 end)
                long long midPart = prefixSum[end] - prefixSum[start + 1];
                
                long long currentSum = leftPart + midPart + rightPart;
                
                if (!found || currentSum > maxVal) {
                    maxVal = currentSum;
                    found = 1;
                }
            }
        } else {
            i++;
        }
    }

    free(inc);
    free(dec);
    free(prefixSum);

    return found ? maxVal : 0;
}