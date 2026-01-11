//
// Created by lhl on 2026/1/11.
//

#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int key;     // nums value
    int val;     // index
    char used;   // 0 empty, 1 occupied
} Entry;

static uint32_t hash_int(int x) {
    return (uint32_t)x * 2654435761u;
}

static int next_pow2(int x) {
    int p = 1;
    while (p < x) p <<= 1;
    return p;
}

static int map_find(Entry *tab, int cap, int key, int *out_val) {
    uint32_t h = hash_int(key);
    int idx = (int)(h & (cap - 1));
    while (tab[idx].used) {
        if (tab[idx].key == key) {
            *out_val = tab[idx].val;
            return 1;
        }
        idx = (idx + 1) & (cap - 1);
    }
    return 0;
}

static void map_put(Entry *tab, int cap, int key, int val) {
    uint32_t h = hash_int(key);
    int idx = (int)(h & (cap - 1));
    while (tab[idx].used) {
        if (tab[idx].key == key) return; // 保留第一次出现的位置也可以
        idx = (idx + 1) & (cap - 1);
    }
    tab[idx].used = 1;
    tab[idx].key = key;
    tab[idx].val = val;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    if (returnSize) *returnSize = 0;
    if (numsSize < 2) return NULL;

    int cap = next_pow2(numsSize * 2);
    Entry *tab = (Entry*)calloc((size_t)cap, sizeof(Entry));
    if (!tab) return NULL;

    for (int i = 0; i < numsSize; i++) {
        int need = target - nums[i];
        int j;
        if (map_find(tab, cap, need, &j)) {
            int *ans = (int*)malloc(sizeof(int) * 2);
            if (!ans) { free(tab); return NULL; }  //处理ans malloc失败的情况
            ans[0] = j;
            ans[1] = i;
            if (returnSize) *returnSize = 2;
            free(tab);
            return ans;
        }
        map_put(tab, cap, nums[i], i);
    }

    free(tab);
    return NULL;
}
