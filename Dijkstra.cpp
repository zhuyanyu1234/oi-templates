#pragma once
#include "Graph.cpp"
#include <array>
#include <functional>
#include <queue>
namespace Dijkstra {                        // Dijkstra 单源最短路, 边权必须非负
const long long INF = 0x3f3f3f3f3f3f3f3fLL; // 无穷大, 加一次边权也不会溢出
typedef std::pair<long long, int> pdi;      // 堆里的 {距离, 点}
class Dijkstra { // 堆优化(优先队列 + 懒删除), 稀疏图首选
  private:
    std::vector<long long> dis; // dis[x]: 源点到 x 的最短距离
  public:
    Dijkstra() {}
    void solve(const Graph::Graph &g,
               int s) { // 以 s 为源点跑一遍, 可反复换源点调用
        dis.assign(g.n + 5, INF);
        std::priority_queue<pdi, std::vector<pdi>, std::greater<pdi>>
            q; // 小根堆
        q.push({0, s});
        dis[s] = 0;
        while (!q.empty()) {
            pdi top = q.top();
            q.pop();
            int u = top.second;
            if (top.first > dis[u]) // 堆里存的是旧距离, 跳过(懒删除)
                continue;
            for (const Graph::edge &ed : g.e[u]) {
                if (dis[u] + ed.w < dis[ed.v]) {
                    dis[ed.v] = dis[u] + ed.w;
                    q.push({dis[ed.v], ed.v});
                }
            }
        }
    }
    Dijkstra(const Graph::Graph &g, int s) { solve(g, s); }
    long long query(int v) { return dis[v]; }   // 源点到 v 的最短距离
    bool reach(int v) { return dis[v] != INF; } // v 是否可达
    const std::vector<long long> &get_dis() { return dis; } // 整个 dis 数组
};
class Dijkstra_2 { // 朴素版 O(n^2) 线性扫最小, 点数少或稠密图时用
  private:
    std::vector<long long> dis;

  public:
    Dijkstra_2() {}
    void solve(const Graph::Graph &g, int s) {
        dis.assign(g.n + 5, INF);
        std::vector<bool> vis(g.n + 5, false); // 最短路是否已确定
        dis[s] = 0;
        for (int i = 1; i <= g.n; i++) {
            int u = 0; // 未确定的点里 dis 最小的
            for (int j = 1; j <= g.n; j++)
                if (!vis[j] && (u == 0 || dis[j] < dis[u]))
                    u = j;
            if (u == 0 || dis[u] == INF) // 剩下的点都不可达
                break;
            vis[u] = true;
            for (const Graph::edge &ed : g.e[u])
                if (dis[u] + ed.w < dis[ed.v])
                    dis[ed.v] = dis[u] + ed.w;
        }
    }
    Dijkstra_2(const Graph::Graph &g, int s) { solve(g, s); }
    long long query(int v) { return dis[v]; }
    bool reach(int v) { return dis[v] != INF; }
    const std::vector<long long> &get_dis() { return dis; }
};
class Dijkstra_3 { // 严格次短路(堆优化): 路径可以重复走点/边,
                   // 长度必须大于最短路
  private:
    std::vector<std::array<long long, 2>>
        dis; // dis[v][0] 最短路, dis[v][1] 严格次短路
  public:
    Dijkstra_3() {}
    void solve(const Graph::Graph &g, int s) {
        dis.assign(g.n + 5, {INF, INF});
        std::priority_queue<pdi, std::vector<pdi>, std::greater<pdi>> q;
        q.push({0, s});
        dis[s][0] = 0;
        while (!q.empty()) {
            pdi top = q.top();
            q.pop();
            long long d = top.first;
            int u = top.second;
            if (d > dis[u][1]) // 比次短路还长的状态不会再有贡献
                continue;
            for (const Graph::edge &ed : g.e[u]) {
                long long nd = d + ed.w;
                if (nd < dis[ed.v][0]) { // 出现更短路: 原最短路降级为次短路,
                                         // 两个都入队
                    dis[ed.v][1] = dis[ed.v][0];
                    dis[ed.v][0] = nd;
                    q.push({dis[ed.v][0], ed.v});
                    q.push({dis[ed.v][1], ed.v});
                } else if (nd > dis[ed.v][0] &&
                           nd < dis[ed.v][1]) { // 严格卡在最短和次短之间
                    dis[ed.v][1] = nd;
                    q.push({dis[ed.v][1], ed.v});
                }
            }
        }
    }
    Dijkstra_3(const Graph::Graph &g, int s) { solve(g, s); }
    long long query(int v, int k) {
        return dis[v][k];
    } // k=0 最短路, k=1 严格次短路
};
} // namespace Dijkstra
