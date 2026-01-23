//
// Created by Gemini on 2026/1/23.
//
#include <stdlib.h>
#include <stdbool.h>

#define MAX 200005

typedef struct node
{
    long long data;
    struct node* next;
    struct node* prev;
    int index; // 新增：用于记录原始位置，确保 Tie-breaking 稳定
    bool valid;
} Node;

typedef struct
{
    long long sum;
    Node* node;
} HeapElement;

HeapElement heap[MAX];
int heapSize = 0;

Node* createNode(long long data, int index) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->index = index; // 记录索引
    new_node->valid = true;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

Node* init(int* nums, int numsSize) {
    Node* head = createNode(0, -1);
    head->valid = false;
    Node* cur = head;
    for (int i = 0; i < numsSize; i++){
        Node* new_node = createNode(nums[i], i); // 传入 i 作为索引
        cur->next = new_node;
        new_node->prev = cur;
        cur = new_node;
    }
    Node* end = createNode(0, numsSize);
    end->valid = false;
    cur->next = end;
    end->prev = cur;
    return head;
}

void swap(int i, int j) {
    HeapElement temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

// 核心修改：比较逻辑改用 node->index
bool isSmaller(HeapElement a, HeapElement b) {
    if (a.sum != b.sum) return a.sum < b.sum;
    return a.node->index < b.node->index; // 和相同时，索引小的优先
}

void siftUp(int i) {
    while (i > 1){
        int p = i / 2;
        if (isSmaller(heap[i], heap[p])){
            swap(i, p);
            i = p;
        }
        else{
            break;
        }
    }
}

void siftDown(int i) {
    while (2 * i <= heapSize){
        int left = 2 * i;
        int right = 2 * i + 1;
        int smallest = i;

        if (left <= heapSize && isSmaller(heap[left], heap[smallest])){
            smallest = left;
        }
        if (right <= heapSize && isSmaller(heap[right], heap[smallest])){
            smallest = right;
        }

        if (smallest != i){
            swap(i, smallest);
            i = smallest;
        }
        else{
            break;
        }
    }
}

void push(long long sum, Node* node) {
    heapSize++;
    heap[heapSize].sum = sum;
    heap[heapSize].node = node;
    siftUp(heapSize);
}

HeapElement pop() {
    HeapElement res = heap[1];
    heap[1] = heap[heapSize];
    heapSize--;
    if (heapSize > 0) siftDown(1);
    return res;
}

void initCnt(Node* head, int* cnt) {
    Node* cur = head->next;
    while (cur->next && cur->next->valid){
        if (cur->data > cur->next->data){
            (*cnt)++;
        }
        cur = cur->next;
    }
}

int minimumPairRemoval(int* nums, int numsSize) {
    Node* head = init(nums, numsSize);
    int cnt = 0;
    initCnt(head, &cnt);

    heapSize = 0;
    Node* cur = head->next;
    while (cur->next && cur->next->valid){
        push(cur->data + cur->next->data, cur);
        cur = cur->next;
    }

    int ops = 0;

    while (cnt > 0){
        if (heapSize == 0) break;
        HeapElement top = pop();
        Node* node = top.node;
        long long sum = top.sum;

        // 懒删除检查：确保当前 sum 依然有效
        if (!node->valid || !node->next || !node->next->valid) continue;
        if (node->data + node->next->data != sum) continue;

        Node* next_node = node->next;
        Node* prev_node = node->prev;
        Node* next_next = next_node->next;

        // 1. 扣除旧账
        if (prev_node->valid && prev_node->data > node->data) cnt--;
        if (node->data > next_node->data) cnt--;
        if (next_next->valid && next_node->data > next_next->data) cnt--;

        // 2. 合并操作
        node->data += next_node->data;
        node->next = next_next;
        if (next_next) next_next->prev = node;
        next_node->valid = false;

        // 3. 记入新账
        if (prev_node->valid && prev_node->data > node->data) cnt++;
        if (next_next->valid && node->data > next_next->data) cnt++;

        // 4. 推入新关系
        if (prev_node->valid){
            push(prev_node->data + node->data, prev_node);
        }
        if (next_next->valid){
            push(node->data + next_next->data, node);
        }

        ops++;
    }

    return ops;
}
