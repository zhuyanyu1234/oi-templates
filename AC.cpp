#include <cstring>
#include <queue>
#include <string>
#include <vector>
namespace AC { // AC 自动机
class Trie {  // 字典树部分, 结点上额外挂模式串编号
  public:     // AC_Automation 需要直接访问结点
    struct node {
        node *nex[26];
        node *fail;
        int count;            // 以该结点结尾的模式串的插入次数(词频)
        int vis;              // 最近一次被计数查询统计时的版本号, 用于替代 -1 标记
        std::vector<int> ids; // 以该结点结尾的模式串编号, 一次 insert 一个编号
        node() {
            memset(nex, 0, sizeof(nex));
            fail = NULL;
            count = 0;
            vis = 0;
        }
    };
    node *root;
    Trie() { root = new node; }
    void insert(const std::string &s, int id) { // 插入模式串, id 从 0 开始编号
        node *now = root;
        for (int i = 0; i < (int)s.length(); i++) {
            int c = s[i] - 'a';
            if (now->nex[c] == NULL)
                now->nex[c] = new node;
            now = now->nex[c];
        }
        now->count++;
        now->ids.push_back(id);
    }
    int query(const std::string &s) { // s 被作为模式串插入了多少次
        node *now = root;
        for (int i = 0; i < (int)s.length(); i++) {
            int c = s[i] - 'a';
            if (now->nex[c] == NULL)
                return 0;
            now = now->nex[c];
        }
        return now->count;
    }
};
class AC_Automation { // 多模式串在文本中的匹配
  private:
    Trie x;
    int tot = 0;             // 模式串总数(insert 次数)
    int qver = 0;            // 计数查询的版本号, 递增, 用于代替 -1 污染 count
    std::vector<int> patLen; // patLen[id] = 模式串 id 的长度

  public:
    void insert(const std::string &s) {
        patLen.push_back((int)s.length());
        x.insert(s, tot++);
    }
    void build() { // 构造 fail 指针并补齐 nex 转移, 之后 nex 不会为 NULL
        std::queue<Trie::node *> q;
        for (int i = 0; i < 26; i++) {
            if (x.root->nex[i]) {
                x.root->nex[i]->fail = x.root;
                q.push(x.root->nex[i]);
            } else {
                x.root->nex[i] = x.root;
            }
        }
        while (!q.empty()) {
            Trie::node *now = q.front();
            q.pop();
            for (int i = 0; i < 26; i++) {
                if (now->nex[i]) {
                    now->nex[i]->fail = now->fail->nex[i];
                    q.push(now->nex[i]);
                } else {
                    now->nex[i] = now->fail->nex[i];
                }
            }
        }
    }
    // 计数查询: 返回文本中出现了多少个模式串, 同一模式串多次出现只计一次。
    // 不修改 count, 可重复调用; 每次调用版本号 qver 递增, 结点 vis == qver
    // 表示本次查询已统计过, 沿 fail 链遇到它即可停止(其祖先本次也必已统计)。
    int query(const std::string &s) {
        ++qver;
        int len = (int)s.length();
        Trie::node *now = x.root;
        int ans = 0;
        for (int i = 0; i < len; i++) {
            int c = s[i] - 'a';
            now = now->nex[c];
            for (Trie::node *t = now; t; t = t->fail) {
                if (t->vis == qver)
                    break; // 已统计; fail 祖先也必已统计, 直接剪枝
                t->vis = qver;
                ans += t->count;
            }
        }
        return ans;
    }
    // 位置查询: 依次扫描 texts 中每条文本, 返回 res[id] = 模式串 id 的全部出现起点
    // 位置为 1-indexed; 多条文本按传入顺序拼接, 位置全局编号(第 t 条文本内的
    // 起点需加上前面所有文本的长度); 可重叠。不修改 count, 可反复调用
    std::vector<std::vector<int>> query(const std::vector<std::string> &texts) {
        std::vector<std::vector<int>> res;
        if (tot == 0)
            return res;
        res.resize(tot);
        int offset = 0; // 已处理文本的累计长度
        for (const std::string &t : texts) {
            Trie::node *now = x.root;
            for (int i = 0; i < (int)t.length(); i++) {
                int c = t[i] - 'a';
                now = now->nex[c];
                for (Trie::node *u = now; u && u != x.root; u = u->fail)
                    for (int id : u->ids)
                        res[id].push_back(offset + i - patLen[id] + 2);
            }
            offset += (int)t.length();
        }
        return res;
    }
};
} // namespace AC