//
// Created by lhl on 2026/1/27.
//


//--------
// 这是 LeetCode C 语言刷题最大的坑。
// LeetCode 的判题机在运行你的代码时，并不是每一个测试用例都重新启动程序。它是跑完一个用例，紧接着跑下一个。
//--------

// Dijkstra
#include<limits.h>
#include<string.h>
#define MAX 200005

int head[MAX];
int to[MAX];
int w[MAX];
int nxt[MAX];
int edge_cnt = 0;

void add(int x, int y, int weight) {
    to[++edge_cnt] = y;
    w[edge_cnt] = weight;
    nxt[edge_cnt] = head[x];
    head[x] = edge_cnt;
}

int dist[MAX];
int visited[MAX];

typedef struct
{
    int u; // 节点编号
    int d; // 当前距离
} HeapNode;

HeapNode heap[MAX]; // 堆数组
int heap_size = 0;

void swap(int i, int j) {
    HeapNode temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void push(int u, int d) {
    heap[++heap_size] = (HeapNode){u, d};
    int curr = heap_size;
    while (curr > 1){
        int parent = curr / 2;
        if (heap[curr].d < heap[parent].d){
            // 小根堆：小的上浮
            swap(curr, parent);
            curr = parent;
        }
        else break;
    }
}

HeapNode pop() {
    HeapNode ret = heap[1];
    heap[1] = heap[heap_size--];
    int curr = 1;
    while (curr * 2 <= heap_size){
        int child = curr * 2;
        if (child + 1 <= heap_size && heap[child + 1].d < heap[child].d) child++;
        if (heap[child].d < heap[curr].d){
            // 小的下沉
            swap(curr, child);
            curr = child;
        }
        else break;
    }
    return ret;
}

void init_environment() {
    // 每次跑新用例前，必须清空 head 和计数器
    // head 数组全部刷为 0
    memset(head, 0, sizeof(head));
    edge_cnt = 0;
    heap_size = 0;
}

int minCost(int n, int** edges, int edgesSize, int* edgesColSize) {
    init_environment();
    for (int i = 0; i < edgesSize; i++){
        add(edges[i][0], edges[i][1], edges[i][2]);
        add(edges[i][1], edges[i][0], edges[i][2] * 2);
    }
    for (int i = 0; i < n; i++){
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[0] = 0;
    push(0, 0);

    while (heap_size > 0){
        HeapNode node = pop();
        int u = node.u;
        int d = node.d;
        if (visited[u]) continue;
        visited[u] = 1;
        if (u == n - 1) return d;
        for (int i = head[u]; i; i = nxt[i]){
            int v = to[i];
            int weight = w[i];

            if (dist[v] > dist[u] + weight){
                dist[v] = dist[u] + weight;
                push(v, dist[v]);
            }
        }
    }
    if (dist[n - 1] == INT_MAX) return -1;
    return dist[n - 1];
}
