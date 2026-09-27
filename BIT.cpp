#include <vector>
namespace BIT { // 树状数组
class BIT {     // 单改区查
  private:
    std::vector<int> c;
    int n = 0;
    int lowbit(int x) { return x & (-x); }
    int prefix(int x) { // a[1] + a[2] + ... + a[x]
        int cnt = 0;
        while (x > 0) {
            cnt += c[x];
            x -= lowbit(x);
        }
        return cnt;
    }

  public:
    BIT() {}
    BIT(int size) {
        n = size;
        c.resize(n + 5, 0);
    }
    void add(int x, int k) {
        if (x <= 0)
            return;
        while (x <= n) {
            c[x] += k;
            x += lowbit(x);
        }
    }
    int query(int l, int r) { return prefix(r) - prefix(l - 1); }
    BIT(const std::vector<int> &a) { // a[1]为第一个元素, a[0]不使用
        if(a.empty())BIT(0);
        n = (int)a.size() - 1;
        c.resize(n + 5, 0);
        for (int i = 1; i <= n; i++) { // O(n) 建树
            c[i] += a[i];
            int j = i + lowbit(i);
            if (j <= n)
                c[j] += c[i];
        }
    }
};
class BIT_2 { // 区改单查
  private:
    BIT tree;
    int n = 0;

  public:
    BIT_2() {}
    BIT_2(int size) : tree(size) { n = size; }
    BIT_2(const std::vector<int> &a)
        : tree((int)a.size()) { // a[1]为第一个元素, a[0]不使用
        n = (int)a.size() - 1;
        int prev = 0;
        for (int i = 1; i < (int)a.size(); i++) {
            tree.add(i, a[i] - prev);
            prev = a[i];
        }
    }
    void add(int l, int r, int k) { // a[l..r] += k
        tree.add(l, k);
        tree.add(r + 1, -k);
    }
    int query(int x) { return tree.query(1, x); } // a[x]
};
} // namespace BIT
