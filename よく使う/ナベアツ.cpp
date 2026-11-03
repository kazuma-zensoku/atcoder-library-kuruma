// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/%E3%83%8A%E3%83%99%E3%82%A2%E3%83%84.cpp
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 
#endif
#include <bits/stdc++.h>
#include <atcoder/all>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace atcoder;
using namespace __gnu_pbds;
using ll = long long; using mint=modint998244353; using ld = long double; 
const ll infl = 1LL << 60;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }
const vector<int> dx = {1, 0, -1, 0}; const vector<int> dy = {0, 1, 0, -1};
template<typename T> using vc = vector<T>; template<typename T> using vvc = vc<vc<T>>; template<typename T> using vvvc = vc<vvc<T>>;
using vi = vc<int>;  using vvi = vvc<int>; using vl = vc<ll>; using vvl = vvc<ll>; using vvvl = vvc<vl>; using vvvvl = vvc<vvl>;
using vs = vc<string>; using vvs = vvc<string>; using P = pair<ll, ll>;
#define nrep(i,n) for (ll i = 0; i < (n); ++i)
#define nfor(i,s,n) for(ll i=s;i<n;i++)//i=s,s+1...n-1 ノーマルfor
template<class T> using pq = priority_queue<T, vc<T>>;//★大きい順に取り出す コスト,頂点 bfs系で使う　小さい順じゃないですABC305E
template<class T> using pq_g = priority_queue<T, vc<T>, greater<T>>;//小さい順に取り出す　ダイクストラ法で使う
template<typename T> void so(T& v) { sort(v.begin(), v.end()); }    // 昇順ソート
template<typename T> void sor(T& v) { sort(v.rbegin(), v.rend()); } // 降順ソート

// print: 可変長引数対応（スペース区切り、末尾改行）
namespace impl {
    template<typename T>
    void print_one(const T& v) { cout << v; }
    inline void print_impl() { cout << "\n"; }
    template<typename T, typename... Rest>
    void print_impl(const T& first, const Rest&... rest) {
        print_one(first);
        if constexpr (sizeof...(rest) > 0) cout << " ";
        print_impl(rest...);
    }
}
template<typename... Args>
void print(const Args&... args) { impl::print_impl(args...); }
// デバッグ出力ユーティリティ
// 基本型（数値系）
template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
void debug_print(const T& v) { cerr << v; }
// string
inline void debug_print(const std::string& s) { cerr << s; }
inline void debug_print(const char* s) { cerr << s; }
// pair
template<typename A, typename B>
void debug_print(const std::pair<A, B>& p) {
    cerr << "{";
    debug_print(p.first);
    cerr << ", ";
    debug_print(p.second);
    cerr << "}";
}
// queue
template<typename T, typename Cont>
void debug_print(const std::queue<T, Cont>& q) {
    auto q2 = q;
    cerr << "queue[";
    while (!q2.empty()) {
        debug_print(q2.front());
        q2.pop();
        if (!q2.empty()) cerr << ", ";
    }
    cerr << "]";
}
// stack
template<typename T, typename Cont>
void debug_print(const std::stack<T, Cont>& s) {
    auto s2 = s;
    cerr << "stack[";
    std::vector<T> tmp;
    while (!s2.empty()) {
        tmp.push_back(s2.top());
        s2.pop();
    }
    for (size_t i = 0; i < tmp.size(); ++i) {
        debug_print(tmp[i]);
        if (i + 1 != tmp.size()) cerr << ", ";
    }
    cerr << "]";
}
// priority_queue
template<typename T, typename Cont, typename Comp>
void debug_print(const std::priority_queue<T, Cont, Comp>& pq) {
    auto q2 = pq;
    cerr << "priority_queue[";
    std::vector<T> tmp;
    while (!q2.empty()) {
        tmp.push_back(q2.top());
        q2.pop();
    }
    for (size_t i = 0; i < tmp.size(); ++i) {
        debug_print(tmp[i]);
        if (i + 1 != tmp.size()) cerr << ", ";
    }
    cerr << "]";
}
// イテレータを持つコンテナ（string, queue, stack, priority_queue 以外）
template<typename T>
auto debug_print(const T& c) -> decltype(std::begin(c), void()) {
    cerr << "[";
    auto it = std::begin(c);
    while (it != std::end(c)) {
        debug_print(*it);
        if (++it != std::end(c)) cerr << ", ";
    }
    cerr << "]";
}
// DEBUG: 可変長引数対応（"var1 = val1, var2 = val2" 形式）
namespace impl {
    inline std::string get_token(const char* s, int idx) {
        std::string src(s);
        int cnt = 0, start = 0;
        for (int i = 0; i <= (int)src.size(); ++i) {
            if (i == (int)src.size() || src[i] == ',') {
                if (cnt == idx) {
                    std::string tok = src.substr(start, i - start);
                    int l = 0, r = (int)tok.size() - 1;
                    while (l <= r && tok[l] == ' ') l++;
                    while (r >= l && tok[r] == ' ') r--;
                    return tok.substr(l, r - l + 1);
                }
                cnt++;
                start = i + 1;
            }
        }
        return "";
    }
    template<typename T, typename... Rest>
    void debug_impl(const char* names, int idx, const T& val, const Rest&... rest) {
        if (idx > 0) cerr << ", ";
        cerr << get_token(names, idx) << " = ";
        debug_print(val);
        if constexpr (sizeof...(rest) > 0)
            debug_impl(names, idx + 1, rest...);
    }
}
#ifndef ONLINE_JUDGE
#define DEBUG(...) do { \
    cerr << "[" << __LINE__ << "] "; \
    impl::debug_impl(#__VA_ARGS__, 0, __VA_ARGS__); \
    cerr << endl; \
} while(0)
#else
#define DEBUG(...)
#endif
void YN(bool v, string y="Yes", string n="No") { cout << (v ? y : n) << "\n"; }
// 1次元vector出力関数
template<typename T>
void vc_cout(const vector<T>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
        if (i + 1 != v.size()) cout << " ";
    }
    cout << "\n";
}
// 2次元vector出力関数
template<typename T>
void vv_cout(const vector<vector<T>>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        for (size_t j = 0; j < v[i].size(); ++j) {
            cout << v[i][j];
            if (j + 1 != v[i].size()) cout << " ";
        }
        cout << "\n";
    }
}
// `vector<string>` 用のオーバーロード: 各文字列をそのまま1行で出力する
void vv_cout(const vector<string>& v) {
    for (const auto& s : v) cout << s << "\n";
}
/* 
    ********************************************************** ここまでテンプレ **********************************************************
*/

string S;
using Result = array<mint, 3>;
Result memo[509][2][3][2][1024];
bool seen[509][2][3][2][1024];

Result solve(int pos, bool tight, int sum, bool is_leading_zero, int kinds) {
    // DEBUG(pos, tight, sum, is_leading_zero, kinds);
    if (pos == (int)S.length()) {
        if (is_leading_zero) { 
            return {0, 0, 0};
        }
        bool f1 = sum%3==0;
        bool f2 = (kinds >> 3) & 1;
        bool f3 = __builtin_popcountll(kinds)==3;
        // DEBUG(sum, kinds, __builtin_popcountll(kinds));
        if(f1 && !f2 && !f3) {
            return {1, 0, 0};
        }
        if(!f1 && f2 && !f3) {
            return {0, 1, 0};
        }
        if(!f1 && !f2 && f3) {
            return {0, 0, 1};
        }
        return {0, 0, 0};
    }
    if (seen[pos][tight][sum][is_leading_zero][kinds]) {
        return memo[pos][tight][sum][is_leading_zero][kinds];
    }

    Result res = {0, 0, 0};
    int limit = tight ? (S[pos] - '0') : 9;

    for (int digit = 0; digit <= limit; ++digit) {
        bool nxt_tight = tight && (digit == limit);
        bool nxt_is_leading_zero = is_leading_zero && (digit == 0);
        int nxtkinds = kinds;
        // DEBUG(digit);
        if(!nxt_is_leading_zero && !((kinds >> digit) & 1)) {
            nxtkinds |= (1 << digit);
        }
        int nxtsum;
        if (nxt_is_leading_zero) { 
            nxtsum = 0; 
        } else {
            nxtsum = (sum + digit) % 3;
        }
        Result nxt = solve(pos + 1, nxt_tight, nxtsum, nxt_is_leading_zero, nxtkinds);
        res[0] += nxt[0];
        res[1] += nxt[1];
        res[2] += nxt[2];
    }

    seen[pos][tight][sum][is_leading_zero][kinds] = true;
    return memo[pos][tight][sum][is_leading_zero][kinds] = res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> S; 
    Result res = solve(0, true, 0, true, 0);
    DEBUG(res[0].val());
    DEBUG(res[1].val());
    DEBUG(res[2].val());
    mint ans = res[0] + res[1] + res[2];
    print(ans.val());
    return 0;
}
