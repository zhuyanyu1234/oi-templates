#include <string>
#include <vector>
namespace KMP { // KMP 字符串匹配
class KMP {     // 失配数组 + 单模式串匹配
  private:
    std::string t;        // 模式串
    int m = 0;            // 模式串长度
    std::vector<int> nex; // nex[0]为哨兵-1, nex[i]: t[0..i-1]最长相等前后缀长度
    void build() {        // O(m) 求失配数组
        int i = 0, j = -1;
        nex.resize(m + 1);
        nex[0] = -1;
        while (i < m) {
            if (j == -1 || t[i] == t[j])
                nex[++i] = ++j;
            else
                j = nex[j];
        }
    }

  public:
    KMP() {}
    KMP(const std::string &pat) { // pat 为模式串
        t = pat;
        m = (int)t.size();
        build();
    }
    // 返回 s 中 t 的所有出现位置(1-indexed, 可重叠), 按出现顺序, O(n+m)
    std::vector<int> match(const std::string &s) {
        std::vector<int> res;
        if (m == 0)
            return res;
        int n = (int)s.size();
        int i = 0, j = 0;
        while (i < n) {
            if (j == -1 || s[i] == t[j])
                i++, j++;
            else
                j = nex[j];
            if (j == m) {
                res.push_back(i - m + 1);
                j = nex[j];
            }
        }
        return res;
    }
    const std::vector<int> &get_nex() { return nex; } // nex[1..m] 有效
};
} // namespace KMP