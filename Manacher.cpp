#pragma once
#include <algorithm>
#include <string>
#include <vector>
namespace Manacher { // 马拉车
class Manacher {     // O(n) 求出以每个位置为中心的最大回文半径
  private:
    std::string t; // 插入 '#' 的串: #a#b#a#, 长度 2n+1
    std::vector<int>
        p; // p[i]: 以 t[i] 为中心的最大回文半径, 即 t[i-p[i]..i+p[i]] 是回文
    int maxlen = 0;    // 最长回文子串长度
    int st = 0;        // 最长回文子串在原串中的起点(0-indexed)
    long long tot = 0; // 回文子串个数(按出现位置计)

  public:
    Manacher() {}
    void build(const std::string &s) { // s[0]为第一个字符
        int n = (int)s.size();
        t.assign(2 * n + 1, '#');
        for (int i = 0; i < n; i++)
            t[2 * i + 1] = s[i];
        int m = (int)t.size();
        p.assign(m, 0);
        maxlen = 0;
        st = 0;
        tot = 0;
        int mid = 0, r = 0; // r: 已知回文到达的最右位置, mid: 对应中心
        for (int i = 0; i < m; i++) {
            if (i < r) // 半径取镜像位置的半径与到右边界距离的较小值
                p[i] = std::min(p[2 * mid - i], r - i);
            while (i - p[i] - 1 >= 0 && i + p[i] + 1 < m &&
                   t[i - p[i] - 1] == t[i + p[i] + 1])
                p[i]++;
            if (i + p[i] > r) {
                mid = i;
                r = i + p[i];
            }
            tot += (p[i] + 1) / 2; // 中心 i 处有 (p[i]+1)/2 个回文子串
            if (p[i] > maxlen) {
                maxlen = p[i];
                st = (i - p[i]) / 2;
            }
        }
    }
    Manacher(const std::string &s) { build(s); }
    int odd(int i) { return p[2 * i + 1]; } // 以 s[i] 为中心的最长奇回文长度
    int even(int i) { // 以 s[i], s[i+1] 中间为中心的最长偶回文长度, 0 表示没有
        return p[2 * i + 2];
    }
    int max_len() { return maxlen; } // 最长回文子串长度
    int start() { return st; } // 最长回文子串起点(0-indexed), 多个时取最左
    long long count() { return tot; } // 回文子串个数(按出现位置计)
};
} // namespace Manacher
