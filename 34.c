//
// Created by Gemini on 2026/2/11.
//
#include <stdlib.h>
#include <string.h>
#include <math.h>

// 假设元素值最大不超过 100005。如果题目数值范围更大，需要调整这个值。
#define MAX_VAL 100005
#define MAX_N 100005

// 线段树节点
typedef struct
{
    int minVal;
    int maxVal;
    int lazy;
} Node;

// --- 线段树操作 ---

void pushUp(Node* tree, int node) {
    int left = 2 * node;
    int right = 2 * node + 1;
    tree[node].minVal = (tree[left].minVal < tree[right].minVal) ? tree[left].minVal : tree[right].minVal;
    tree[node].maxVal = (tree[left].maxVal > tree[right].maxVal) ? tree[left].maxVal : tree[right].maxVal;
}

void pushDown(Node* tree, int node) {
    if (tree[node].lazy != 0){
        int left = 2 * node;
        int right = 2 * node + 1;
        int v = tree[node].lazy;

        tree[left].lazy += v;
        tree[left].minVal += v;
        tree[left].maxVal += v;

        tree[right].lazy += v;
        tree[right].minVal += v;
        tree[right].maxVal += v;

        tree[node].lazy = 0;
    }
}

// 建树
void build(Node* tree, int node, int start, int end) {
    tree[node].lazy = 0;
    tree[node].minVal = 0;
    tree[node].maxVal = 0;
    if (start == end) return;
    int mid = (start + end) / 2;
    build(tree, 2 * node, start, mid);
    build(tree, 2 * node + 1, mid + 1, end);
}

// 区间更新
void update(Node* tree, int node, int start, int end, int l, int r, int val) {
    if (l > end || r < start) return;
    if (l <= start && end <= r){
        tree[node].minVal += val;
        tree[node].maxVal += val;
        tree[node].lazy += val;
        return;
    }
    pushDown(tree, node);
    int mid = (start + end) / 2;
    update(tree, 2 * node, start, mid, l, r, val);
    update(tree, 2 * node + 1, mid + 1, end, l, r, val);
    pushUp(tree, node);
}

// 查询最左边的 0
int queryLeftmostZero(Node* tree, int node, int start, int end, int l, int r) {
    if (l > end || r < start) return -1;

    // 核心剪枝：如果区间最小值 > 0 或 最大值 < 0，说明不可能有 0
    if (tree[node].minVal > 0 || tree[node].maxVal < 0) return -1;

    if (start == end){
        return (tree[node].minVal == 0) ? start : -1;
    }

    pushDown(tree, node);
    int mid = (start + end) / 2;

    // 贪心：优先找左边
    int res = queryLeftmostZero(tree, 2 * node, start, mid, l, r);
    if (res != -1) return res;

    return queryLeftmostZero(tree, 2 * node + 1, mid + 1, end, l, r);
}

// --- 主函数 ---

int longestBalanced(int* nums, int numsSize) {
    if (numsSize == 0) return 0;

    // 1. 分配内存
    // 线段树数组大小为 4 * numsSize
    Node* tree = (Node*)malloc(sizeof(Node) * 4 * numsSize);

    // 桶：last_pos[v] 记录数值 v 上一次出现的下标
    int* last_pos = (int*)malloc(sizeof(int) * MAX_VAL);

    // 初始化 last_pos 为 -1
    // 注意：memset 对 int 数组只能赋 0 或 -1
    memset(last_pos, -1, sizeof(int) * MAX_VAL);

    // 2. 初始化线段树
    build(tree, 1, 0, numsSize - 1);

    int maxLen = 0;

    // 3. 扫描线
    for (int i = 0; i < numsSize; i++){
        int val = nums[i];

        // 安全检查：如果数值超过桶的大小，直接跳过或处理（防止越界崩溃）
        if (val >= MAX_VAL || val < 0){
            // 在实际比赛中这里应该报错或者根据题目调整 MAX_VAL
            // 这里我们假设输入合法
            continue;
        }

        int prev = last_pos[val];

        // 偶数 +1, 奇数 -1
        // 注意位运算优先级，(val & 1) 需要括号
        int delta = ((val & 1) == 0) ? 1 : -1;

        // 更新区间：从 (上一次出现的位置 + 1) 到 (当前位置 i)
        update(tree, 1, 0, numsSize - 1, prev + 1, i, delta);

        // 更新桶
        last_pos[val] = i;

        // 查询：在 [0, i] 范围内找最左边的 0
        int l = queryLeftmostZero(tree, 1, 0, numsSize - 1, 0, i);
        if (l != -1){
            int currentLen = i - l + 1;
            if (currentLen > maxLen){
                maxLen = currentLen;
            }
        }
    }

    // 释放内存
    free(tree);
    free(last_pos);

    return maxLen;
}
