#include <vector>
namespace UnionSet { // 并查集
class UnionSet {     // 路径压缩
  private:
    std::vector<int> fa; // fa[x]: x 的父亲, 根的父亲是自己
    int cnt = 0;         // 剩余集合个数
    int _find(int x) {   // 求根, 回溯时把途中点直接挂到根(路径压缩)
        if (fa[x] == x)
            return x;
        return fa[x] = _find(fa[x]);
    }

  public:
    UnionSet() {}
    UnionSet(int size) { // 元素编号 1..n
        cnt = size;
        fa.resize(size + 5, 0);
        for (int i = 1; i <= size; i++)
            fa[i] = i;
    }
    int find(int x) { return _find(x); } // x 所在集合的根
    bool same(int x, int y) {            // x, y 是否在同一集合
        return _find(x) == _find(y);
    }
    bool merge(int x, int y) { // 合并 x, y 所在集合, 已连通返回 false
        int fx = _find(x), fy = _find(y);
        if (fx == fy)
            return false;
        fa[fx] = fy;
        cnt--;
        return true;
    }
    int count() { return cnt; } // 当前集合个数
};
class UnionSet_2 { // 路径压缩 + 按秩合并
  private:
    std::vector<int> fa;  // fa[x]: x 的父亲, 根的父亲是自己
    std::vector<int> rnk; // rnk[x]: 以 x 为根的树高上界(秩), 非根无意义
    int cnt = 0;          // 剩余集合个数
    int _find(int x) {    // 求根, 回溯时把途中点直接挂到根(路径压缩)
        if (fa[x] == x)
            return x;
        return fa[x] = _find(fa[x]);
    }

  public:
    UnionSet_2() {}
    UnionSet_2(int size) { // 元素编号 1..n
        cnt = size;
        fa.resize(size + 5, 0);
        rnk.resize(size + 5, 0);
        for (int i = 1; i <= size; i++)
            fa[i] = i;
    }
    int find(int x) { return _find(x); } // x 所在集合的根
    bool same(int x, int y) {            // x, y 是否在同一集合
        return _find(x) == _find(y);
    }
    bool merge(int x, int y) { // 合并 x, y 所在集合, 已连通返回 false
        int fx = _find(x), fy = _find(y);
        if (fx == fy)
            return false;
        if (rnk[fx] < rnk[fy]) { // 保证 fx 秩不小于 fy
            int tmp = fx;
            fx = fy;
            fy = tmp;
        }
        fa[fy] = fx;            // 矮树挂到高树下
        if (rnk[fx] == rnk[fy]) // 等高时树高才会加一
            rnk[fx]++;
        cnt--;
        return true;
    }
    int count() { return cnt; } // 当前集合个数
};
} // namespace UnionSet
