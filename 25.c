//
// Created by Gemini on 2026/1/28.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义长整型简写，方便书写
typedef long long ll;

// 树状数组大小，最大为 numsSize
int n_uniq; 
int *bit_cnt;   // 记录元素个数
ll *bit_sum;    // 记录元素之和
int *sorted_vals; // 存储离散化后的原始数值

// 比较函数，用于 qsort
int cmp(const void *a, const void *b) {
    int val_a = *(const int*)a;
    int val_b = *(const int*)b;
    return (val_a > val_b) - (val_a < val_b);
}

// 树状数组：更新
// idx: 排名 (1-based)
// cnt_delta: 数量变化 (+1 或 -1)
// sum_delta: 数值变化 (+val 或 -val)
void update(int idx, int cnt_delta, ll sum_delta) {
    while (idx <= n_uniq) {
        bit_cnt[idx] += cnt_delta;
        bit_sum[idx] += sum_delta;
        idx += idx & (-idx);
    }
}

// 树状数组：查询前缀和
// 返回: 排名 <= idx 的所有元素的数量和数值总和
void query(int idx, int *cnt_out, ll *sum_out) {
    int c = 0;
    ll s = 0;
    while (idx > 0) {
        c += bit_cnt[idx];
        s += bit_sum[idx];
        idx -= idx & (-idx);
    }
    *cnt_out = c;
    *sum_out = s;
}

// 二分查找：获取数值 val 在 sorted_vals 中的排名 (1-based index)
int get_rank(int val, int size) {
    int l = 0, r = size - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (sorted_vals[mid] == val) return mid + 1;
        else if (sorted_vals[mid] < val) l = mid + 1;
        else r = mid - 1;
    }
    return -1; // Should not happen
}

// 核心函数：计算窗口内最小的 k 个元素之和
ll get_smallest_k_sum(int k) {
    if (k == 0) return 0;
    
    // 二分查找树状数组的“排名”，找到一个 rank，使得 <= rank 的元素数量刚好 >= k
    int l = 1, r = n_uniq, pos = -1;
    
    while (l <= r) {
        int mid = l + (r - l) / 2;
        int c;
        ll s;
        query(mid, &c, &s);
        if (c >= k) {
            pos = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    
    // 计算结果
    int total_cnt;
    ll total_sum;
    query(pos, &total_cnt, &total_sum);
    
    // 如果累加的数量超过了 k，需要减去多余的部分
    // 多余的部分数值一定都等于 sorted_vals[pos-1]
    if (total_cnt > k) {
        total_sum -= (ll)(total_cnt - k) * sorted_vals[pos - 1];
    }
    
    return total_sum;
}

long long minimumCost(int* nums, int numsSize, int k, int dist) {
    // 1. 离散化处理
    // 复制数组用于排序去重
    int *temp = (int*)malloc(numsSize * sizeof(int));
    memcpy(temp, nums, numsSize * sizeof(int));
    qsort(temp, numsSize, sizeof(int), cmp);
    
    // 去重，构建 value -> rank 的映射
    sorted_vals = (int*)malloc(numsSize * sizeof(int));
    n_uniq = 0;
    if (numsSize > 0) {
        sorted_vals[n_uniq++] = temp[0];
        for (int i = 1; i < numsSize; i++) {
            if (temp[i] != temp[i-1]) {
                sorted_vals[n_uniq++] = temp[i];
            }
        }
    }
    free(temp);
    
    // 2. 初始化树状数组
    bit_cnt = (int*)calloc(n_uniq + 1, sizeof(int));
    bit_sum = (ll*)calloc(n_uniq + 1, sizeof(ll));
    
    // 3. 滑动窗口处理
    // 我们需要选取 nums[1...n-1] 中的 k-1 个元素
    // 使得这些元素的下标 span 不超过 dist
    // 也就是说，我们在 nums[1...n-1] 上维护一个长度最大为 dist+1 的窗口
    
    int target_count = k - 1;
    ll min_cost = -1;
    
    // 窗口范围 [left, right]
    int left = 1;
    
    for (int right = 1; right < numsSize; right++) {
        // 将当前数字加入窗口：更新树状数组
        int r = get_rank(nums[right], n_uniq);
        update(r, 1, nums[right]);
        
        // 如果窗口过大，移除最左边的元素
        // 题目要求：ik - i2 <= dist. 
        // 这里的 i2 是选中的第一个元素的下标，ik 是选中的最后一个。
        // 所以我们维护的窗口实际长度是 dist + 1。
        // 当 right - left == dist + 1 时，我们需要移除 left。
        if (right - left > dist) {
            int l_rank = get_rank(nums[left], n_uniq);
            update(l_rank, -1, -nums[left]);
            left++;
        }
        
        // 当窗口内的元素数量足够选出 k-1 个时
        if (right - left + 1 >= target_count) {
            ll current_window_sum = get_smallest_k_sum(target_count);
            ll total_cost = (ll)nums[0] + current_window_sum;
            
            if (min_cost == -1 || total_cost < min_cost) {
                min_cost = total_cost;
            }
        }
    }
    
    // 释放内存
    free(sorted_vals);
    free(bit_cnt);
    free(bit_sum);
    
    return min_cost;
}