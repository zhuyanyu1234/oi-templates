#include <algorithm>
#include <vector>
namespace Disc { // 离散化
class Disc {     // 把大值域的数映射成 1..m 的编号
  private:
    std::vector<long long> v; // 排序去重后的所有原值, 从小到大

  public:
    Disc() {}
    void build(const std::vector<long long> &a) { // a[0]为第一个元素
        v = a;
        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
    }
    Disc(const std::vector<long long> &a) { build(a); }
    int size() { return (int)v.size(); } // 不同值的个数 m
    int rank(long long x) { // x 的编号 1..m; x 不在其中时取第一个 >= x
                            // 的编号(没有则为 m+1)
        return (int)(std::lower_bound(v.begin(), v.end(), x) - v.begin()) + 1;
    }
    long long val(int k) { return v[k - 1]; } // 编号 k 对应的原值, 与 rank 互逆
};
std::vector<int>
solve(const std::vector<long long> &a) { // 一步把整个数组变成编号数组
    Disc d(a);
    std::vector<int> res(a.size());
    for (int i = 0; i < (int)a.size(); i++)
        res[i] = d.rank(a[i]);
    return res;
}
} // namespace Disc
