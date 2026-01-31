//
// Created by Gemini on 2026/1/30.
//

import java.util.*;

class Solution {
    public long minimumCost(String source, String target, String[] original, String[] changed, int[] cost) {
        // 1. 字符串离散化：将所有 original 和 changed 中的字符串映射为整数 ID
        Map<String, Integer> map = new HashMap<>();
        int idCounter = 0;
        
        for (String s : original) {
            if (!map.containsKey(s)) map.put(s, idCounter++);
        }
        for (String s : changed) {
            if (!map.containsKey(s)) map.put(s, idCounter++);
        }

        // 2. 初始化距离矩阵 (Floyd-Warshall)
        int n = map.size();
        long[][] dist = new long[n][n];
        // 使用 Long.MAX_VALUE / 2 防止加法溢出
        long INF = Long.MAX_VALUE / 2;

        // 初始化矩阵
        for (int i = 0; i < n; i++) {
            Arrays.fill(dist[i], INF);
            dist[i][i] = 0;
        }

        // 填充初始边
        for (int i = 0; i < original.length; i++) {
            int u = map.get(original[i]);
            int v = map.get(changed[i]);
            // 注意：可能会有多条边连接相同的两个字符串，取最小代价
            dist[u][v] = Math.min(dist[u][v], (long) cost[i]);
        }

        // 3. Floyd-Warshall 算法计算所有子串对之间的最短路径
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                if (dist[i][k] == INF) continue; // 剪枝
                for (int j = 0; j < n; j++) {
                    if (dist[k][j] != INF) {
                        dist[i][j] = Math.min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }

        // 优化：记录所有出现过的子串长度，DP 时只遍历这些长度
        Set<Integer> lengths = new HashSet<>();
        for (String s : original) {
            lengths.add(s.length());
        }

        // 4. 动态规划
        int lenS = source.length();
        long[] dp = new long[lenS + 1];
        Arrays.fill(dp, INF);
        dp[lenS] = 0; // 终点状态为 0

        // 从后往前 DP
        for (int i = lenS - 1; i >= 0; i--) {
            // 情况 A: 当前字符相同，可以尝试直接匹配（代价为 0），继承后一个状态
            if (source.charAt(i) == target.charAt(i)) {
                dp[i] = Math.min(dp[i], dp[i + 1]);
            }

            // 情况 B: 尝试匹配并转换子串
            for (int len : lengths) {
                if (i + len > lenS) continue;

                // 截取子串
                String subS = source.substring(i, i + len);
                String subT = target.substring(i, i + len);

                // 检查子串是否在映射表中
                Integer u = map.get(subS);
                Integer v = map.get(subT);

                // 如果两个子串都在表中，且存在通路，且后续状态可达
                if (u != null && v != null && dist[u][v] < INF && dp[i + len] < INF) {
                    dp[i] = Math.min(dp[i], dist[u][v] + dp[i + len]);
                }
            }
        }

        return dp[0] >= INF ? -1 : dp[0];
    }
}