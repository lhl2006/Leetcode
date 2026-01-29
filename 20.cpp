//
// Created by Gemini on 2026/1/28.
//
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>

using namespace std;

class Solution

public
:
int minCost(vector<vector<int>>& grid, int k) {
    int m = grid.size();
    int n = grid[0].size();

    // 使用 long long 防止路径累加溢出（虽然题目数据范围可能 int 够用，但更安全）
    const long long INF = 1e18;
    vector<vector<long long>> dist(m, vector<long long>(n, INF));

    // 起点代价为 0 (通常题目定义网格移动代价为进入格子的数值，起点本身若算移动则需改为 grid[0][0])
    // 根据题目常规理解：从 (0,0) 出发，移动到 (0,1) 产生 grid[0][1] 代价。
    dist[0][0] = 0;

    // 预处理网格最大值，用于确定后缀数组的大小
    int max_val = 0;
    for (const auto& row : grid){
        for (int val : row) max_val = max(max_val, val);
    }

    long long ans = INF;

    // 循环 k+1 次，t 代表已经使用的传送次数
    // t=0: 只做普通移动
    // t=1: 传送1次 + 普通移动 ...
    for (int t = 0; t <= k; ++t){
        // --- 阶段 1: 当前层 Dijkstra (处理普通移动) ---
        // 小顶堆存储 {cost, r, c}
        priority_queue<tuple<long long, int, int>,
                       vector<tuple<long long, int, int>>,
                       greater<tuple<long long, int, int>>> pq;

        // 将当前层所有可达点加入队列
        for (int i = 0; i < m; ++i){
            for (int j = 0; j < n; ++j){
                if (dist[i][j] != INF){
                    pq.push({dist[i][j], i, j});
                }
            }
        }

        while (!pq.empty()){
            auto [d, r, c] = pq.top();
            pq.pop();

            if (d > dist[r][c]) continue;

            // 向右、向下移动
            int dr[] = {0, 1};
            int dc[] = {1, 0};

            for (int i = 0; i < 2; ++i){
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < m && nc >= 0 && nc < n){
                    long long new_cost = d + grid[nr][nc];
                    if (new_cost < dist[nr][nc]){
                        dist[nr][nc] = new_cost;
                        pq.push({new_cost, nr, nc});
                    }
                }
            }
        }

        // 更新全局最小答案（因为不一定要用完 k 次传送）
        ans = min(ans, dist[m - 1][n - 1]);

        // 如果是最后一次循环，不需要再计算下一层的传送状态
        if (t == k) break;

        // --- 阶段 2: 准备下一层 (处理传送逻辑) ---

        // min_val[v] 表示：在当前层中，所有数值 >= v 的格子里的最小路径代价
        vector<long long> min_val(max_val + 2, INF);

        // 1. 收集当前层的信息
        for (int i = 0; i < m; ++i){
            for (int j = 0; j < n; ++j){
                if (dist[i][j] != INF){
                    int val = grid[i][j];
                    min_val[val] = min(min_val[val], dist[i][j]);
                }
            }
        }

        // 2. 计算后缀最小值 (Suffix Minimum)
        // 如果能从数值 v+1 的点传送，那么也一定能从数值 v 的点传送 (因为 target <= source)
        // 所以 min_val[v] 应该是 min_val[v] 和 min_val[v+1] 的较小值
        for (int v = max_val; v >= 0; --v){
            min_val[v] = min(min_val[v], min_val[v + 1]);
        }

        // 3. 初始化下一层 dist 数组
        vector<vector<long long>> next_dist(m, vector<long long>(n, INF));
        for (int i = 0; i < m; ++i){
            for (int j = 0; j < n; ++j){
                int val = grid[i][j];
                // 如果我想传送去 (i, j)，只要上一层有任何 grid[source] >= grid[i][j] 的点即可
                // 代价就是那个源点的代价 (传送花费为0)
                if (min_val[val] != INF){
                    next_dist[i][j] = min_val[val];
                }
            }
        }

        // 滚动数组进入下一轮
        dist = move(next_dist);
    }

    return (int)ans;
}

};
