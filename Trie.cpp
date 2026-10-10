#include <cstring>
#include <string>
namespace Trie { // 字典树
class Trie {     // 词频统计: 每个字符串作为"完整词"的插入次数
  private:
    struct node {
        node *nex[26];
        int count;
        node() {
            memset(nex, 0, sizeof(nex));
            count = 0;
        }
    };
    node *root;

  public:
    Trie() { root = new node; }
    void insert(const std::string &s) { // 插入一个词
        node *now = root;
        for (int i = 0; i < (int)s.length(); i++) {
            int c = s[i] - 'a';
            if (now->nex[c] == NULL)
                now->nex[c] = new node;
            now = now->nex[c];
        }
        now->count++;
    }
    int query(const std::string &s) { // s 被作为词插入了多少次, 未插入返回 0
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
} // namespace Trie