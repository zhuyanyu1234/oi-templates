#pragma once
#include "UnionSet.cpp"
#include <bits/stdc++.h>

namespace Kruskal {
struct Edge {
    int u;
    int v;
    int w;
};
bool cmp(const Edge &a, const Edge &b) { return a.w < b.w; }
class Kruskal {
  private:
    long long ans = 0;
    int cnt = 0;
    bool ok = false;

  public:
    Kruskal() {}
    void solve(int n, std::vector<Edge> &edges) {
        ans = 0;
        cnt = 0;
        std::sort(edges.begin(), edges.end(), cmp);
        UnionSet::UnionSet dsu(n);
        for (const Edge &e : edges) {
            if (dsu.merge(e.u, e.v)) {
                ans += e.w;
                cnt++;
                if (cnt == n - 1)
                    break;
            }
        }
        ok = (cnt == n - 1);
    }
    Kruskal(int n, std::vector<Edge> &edges) { solve(n, edges); }
    long long query() { return ans; }
    bool exist() { return ok; }
    int count() { return cnt; }
};
} // namespace Kruskal
