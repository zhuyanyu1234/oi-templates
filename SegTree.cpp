#include <vector>
namespace SegTree { // 线段树
class SegTree {     // 区加区查(懒标记)
  private:
    struct SegTreeNode {
        long long Val;
        long long LazyTag;
    };
    int n = 0;
    std::vector<long long> build_t; // 建树用临时数组
    std::vector<SegTreeNode> node;
    void _push_up(int x) {
        node[x].Val = node[2 * x].Val + node[2 * x + 1].Val;
    }
    void _build(int x, int l, int r) {
        node[x].LazyTag = 0;
        if (l == r) {
            node[x].Val = build_t[l];
            return;
        }
        int mid = (l + r) >> 1;
        _build(2 * x, l, mid);
        _build(2 * x + 1, mid + 1, r);
        _push_up(x);
    }
    void apply_tag(int x, int l, int r, long long k) { // 打懒标记
        node[x].LazyTag += k;
        node[x].Val += k * (r - l + 1);
    }
    void push_down(int x, int l, int r) { // 下传懒标记
        if (node[x].LazyTag == 0)
            return;
        int mid = (l + r) >> 1;
        apply_tag(2 * x, l, mid, node[x].LazyTag);
        apply_tag(2 * x + 1, mid + 1, r, node[x].LazyTag);
        node[x].LazyTag = 0;
    }
    long long _query(int x, int l, int r, int nl, int nr) {
        if (nl <= l && r <= nr)
            return node[x].Val;
        push_down(x, l, r);
        int mid = (l + r) >> 1;
        long long res = 0;
        if (nl <= mid)
            res += _query(2 * x, l, mid, nl, nr);
        if (nr > mid)
            res += _query(2 * x + 1, mid + 1, r, nl, nr);
        return res;
    }
    void _update(int x, long long k, int l, int r, int nl, int nr) {
        if (nl <= l && r <= nr) {
            apply_tag(x, l, r, k);
            return;
        }
        push_down(x, l, r);
        int mid = (l + r) >> 1;
        if (nl <= mid)
            _update(2 * x, k, l, mid, nl, nr);
        if (nr > mid)
            _update(2 * x + 1, k, mid + 1, r, nl, nr);
        _push_up(x);
    }

  public:
    SegTree() {}
    void build(const std::vector<long long> &x) { // x[0]为第一个元素
        n = (int)x.size();
        node.resize(4 * n + 5);
        build_t.assign(n + 1, 0);
        for (int i = 0; i < n; i++)
            build_t[i + 1] = x[i];
        _build(1, 1, n);
        build_t.clear();
    }
    SegTree(const std::vector<long long> &x) { build(x); }
    long long query(int l, int r) {
        return _query(1, 1, n, l, r);
    } // a[l] + ... + a[r], 1-indexed
    void update(int l, int r, long long k) {
        _update(1, k, 1, n, l, r);
    } // a[l..r] += k, 1-indexed
};
} // namespace SegTree
