#pragma once
#include <queue>
#include "Graph.cpp"
namespace SPFA { // SPFA 单源最短路
const long long INF = 0x3f3f3f3f3f3f3f3fLL; // 无穷大, 加一次边权也不会溢出
class SPFA {     // 队列优化的 Bellman-Ford, 图里不能有负环
  private:
    std::vector<long long> dis; // dis[x]: 源点到 x 的最短距离
  public:
    SPFA() {}
    void solve(const Graph::Graph &g, int s) { // 以 s 为源点跑一遍, 可反复换源点调用
        dis.assign(g.n + 5, INF);
        std::vector<bool> inq(g.n + 5, false); // 点是否在队列中
        std::queue<int> q;
        q.push(s);
        dis[s] = 0;
        inq[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = false;
            for (const Graph::edge &ed : g.e[u]) {
                if (dis[u] + ed.w < dis[ed.v]) { // 松弛
                    dis[ed.v] = dis[u] + ed.w;
                    if (!inq[ed.v]) {
                        q.push(ed.v);
                        inq[ed.v] = true;
                    }
                }
            }
        }
    }
    SPFA(const Graph::Graph &g, int s) { solve(g, s); }
    long long query(int v) { return dis[v]; }               // 源点到 v 的最短距离
    bool reach(int v) { return dis[v] != INF; }             // v 是否可达
    const std::vector<long long> &get_dis() { return dis; } // 整个 dis 数组
};
} // namespace SPFA
