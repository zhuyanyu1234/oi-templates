#include <bits/stdc++.h>

namespace fastio {
class FastIO {
  private:
    char putback_buf = 0;
    bool has_putback = false;

    char gc() {
        if (has_putback) {
            has_putback = false;
            return putback_buf;
        }
        return getchar_unlocked();
    }

    void ungetc_buf(char c) {
        putback_buf = c;
        has_putback = true;
    }

    char skip_ws() {
        char c = gc();
        while (c != EOF && isspace((unsigned char)c))
            c = gc();
        return c;
    }

    template <typename T> T read_impl(std::false_type) {
        T x = 0;
        char c = skip_ws();
        bool neg = false;
        if (c == '-') {
            neg = true;
            c = gc();
        }
        while (isdigit((unsigned char)c)) {
            x = x * 10 + (c - '0');
            c = gc();
        }
        if (c != EOF)
            ungetc_buf(c);
        return neg ? -x : x;
    }

    char read_impl(std::true_type) { return skip_ws(); }

  public:
    template <typename T> T read() {
        return read_impl<T>(std::is_same<T, char>{});
    }

    void read(char *s) {
        char c = skip_ws();
        while (c != EOF && !isspace((unsigned char)c)) {
            *s++ = c;
            c = gc();
        }
        *s = '\0';
        if (c != EOF)
            ungetc_buf(c);
    }

    std::string read_str() {
        std::string s;
        char c = skip_ws();
        while (c != EOF && !isspace((unsigned char)c)) {
            s.push_back(c);
            c = gc();
        }
        if (c != EOF)
            ungetc_buf(c);
        return s;
    }

    template <typename T> void write(T x) {
        if (x == 0) {
            putchar_unlocked('0');
            return;
        }
        if (x < 0) {
            putchar_unlocked('-');
            x = -x;
        }
        char tmp[32];
        int len = 0;
        while (x > 0) {
            tmp[len++] = char('0' + x % 10);
            x /= 10;
        }
        while (len--)
            putchar_unlocked(tmp[len]);
    }

    void putc(char c) { putchar_unlocked(c); }

    void write(const char *s) {
        while (*s)
            putchar_unlocked(*s++);
    }

    void write(const std::string &s) {
        for (char c : s)
            putchar_unlocked(c);
    }

    template <typename T> void writeln(T x) {
        write(x);
        putchar_unlocked('\n');
    }
};

FastIO fio;
} // namespace fastio