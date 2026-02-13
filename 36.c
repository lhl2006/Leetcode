//
// Created by Gemini on 2026/2/13.
//
#include <string.h>
#include <stdlib.h>

#define MAX_N 100005
#define HASH_SIZE 200003

// 手写哈希表的节点结构
typedef struct {
    int diff1;
    int diff2;
    int first_idx;
    int next;
} HashNode;

// 静态数组分配，防止堆栈溢出并提高访问速度
HashNode hash_nodes[MAX_N + 5];
int hash_head[HASH_SIZE];
int modified_hashes[MAX_N + 5]; // 记录修改过的哈希桶索引，用于 O(1) 级别的重置
int mod_cnt = 0;

int segment_id[MAX_N * 2 + 5] = {0}; // 用代号标记当前轮次，避免昂贵的 memset
int first_idx_arr[MAX_N * 2 + 5];
int current_seg = 0;

int is_initialized = 0;

int longestBalanced(char* s) {
    // 判题机可能会多次调用这个函数，这里的逻辑确保哈希表只重置被用过的部分
    if (!is_initialized) {
        memset(hash_head, -1, sizeof(hash_head));
        is_initialized = 1;
    } else {
        for (int i = 0; i < mod_cnt; i++) {
            hash_head[modified_hashes[i]] = -1;
        }
    }
    mod_cnt = 0;

    int n = strlen(s);
    if (n == 0) return 0;

    int max_len = 1;

    // ============================================
    // 1. 只包含 1 种字符的情况
    // ============================================
    int cur_len = 1;
    for (int i = 1; i < n; i++) {
        if (s[i] == s[i-1]) cur_len++;
        else cur_len = 1;
        if (cur_len > max_len) max_len = cur_len;
    }

    // ============================================
    // 2. 恰好包含 2 种字符的情况
    // ============================================
    char pairs[3][3] = { {'a', 'b', 'c'}, {'a', 'c', 'b'}, {'b', 'c', 'a'} };
    for (int p = 0; p < 3; p++) {
        char c1 = pairs[p][0];
        char c2 = pairs[p][1];
        char exclude = pairs[p][2];

        current_seg++;
        int diff = 0;

        first_idx_arr[MAX_N + diff] = -1;
        segment_id[MAX_N + diff] = current_seg;

        for (int i = 0; i < n; i++) {
            if (s[i] == exclude) {
                // 遇到被排除的字符，强制重置前缀和并开启新的分段
                current_seg++;
                diff = 0;
                first_idx_arr[MAX_N + diff] = i;
                segment_id[MAX_N + diff] = current_seg;
            } else {
                if (s[i] == c1) diff++;
                else diff--;

                // 使用 segment_id 来验证数据是否属于当前的有效分段
                if (segment_id[MAX_N + diff] == current_seg) {
                    int len = i - first_idx_arr[MAX_N + diff];
                    if (len > max_len) max_len = len;
                } else {
                    first_idx_arr[MAX_N + diff] = i;
                    segment_id[MAX_N + diff] = current_seg;
                }
            }
        }
    }

    // ============================================
    // 3. 恰好包含 3 种字符的情况
    // ============================================
    int node_cnt = 0;
    int a = 0, b = 0, c = 0;

    // 初始化 diff1 = 0, diff2 = 0 的前缀状态（处理前缀本身就是答案的情况）
    unsigned long long ud1_init = (unsigned long long)MAX_N;
    unsigned long long ud2_init = (unsigned long long)MAX_N;
    unsigned long long h0 = (ud1_init * 131313ULL + ud2_init) % HASH_SIZE;

    hash_nodes[node_cnt].diff1 = 0;
    hash_nodes[node_cnt].diff2 = 0;
    hash_nodes[node_cnt].first_idx = -1;
    hash_nodes[node_cnt].next = hash_head[h0];

    if (hash_head[h0] == -1) {
        modified_hashes[mod_cnt++] = h0;
    }
    hash_head[h0] = node_cnt++;

    for (int i = 0; i < n; i++) {
        if (s[i] == 'a') a++;
        else if (s[i] == 'b') b++;
        else if (s[i] == 'c') c++;

        int d1 = a - b;
        int d2 = b - c;

        // 防治负数取模问题，统一平移 MAX_N 并进行哈希散列
        unsigned long long ud1 = (unsigned long long)(d1 + MAX_N);
        unsigned long long ud2 = (unsigned long long)(d2 + MAX_N);
        unsigned long long h = (ud1 * 131313ULL + ud2) % HASH_SIZE;

        int curr = hash_head[h];
        int found = 0;

        // 遍历冲突链表
        while (curr != -1) {
            if (hash_nodes[curr].diff1 == d1 && hash_nodes[curr].diff2 == d2) {
                found = 1;
                int len = i - hash_nodes[curr].first_idx;
                if (len > max_len) max_len = len;
                break; // 只需最早的位置，所以找到了直接 break
            }
            curr = hash_nodes[curr].next;
        }

        // 如果是第一次出现这个差值，记录下来
        if (!found) {
            hash_nodes[node_cnt].diff1 = d1;
            hash_nodes[node_cnt].diff2 = d2;
            hash_nodes[node_cnt].first_idx = i;
            hash_nodes[node_cnt].next = hash_head[h];
            if (hash_head[h] == -1) {
                modified_hashes[mod_cnt++] = h;
            }
            hash_head[h] = node_cnt++;
        }
    }

    return max_len;
}