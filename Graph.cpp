#pragma once
#include <vector>
namespace Graph { // 存图
struct edge {     // 一条有向边
    int v;        // 指向的点
    int w;        // 边权
};
class Graph { // 邻接表, 点编号 1..n
  public:
    int n = 0;                        // 点数
    std::vector<std::vector<edge>> e; // e[u]: u 的所有出边
    Graph() {}
    Graph(int size) {
        n = size;
        e.resize(n + 5);
    }
    void add(int u, int v, int w) { // 有向边 u -> v, 边权 w
        e[u].push_back({v, w});
    }
    void add2(int u, int v, int w) { // 无向边, 正反各存一条
        add(u, v, w);
        add(v, u, w);
    }
};
} // namespace Graph
