// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/%E6%9C%A8%E3%81%AE%E3%83%88%E3%83%9D%E3%82%BD.cpp
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

using mint=modint998244353;
ll a[1000009];

const int MAX = 1000009;
mint fac[MAX], fac_inv[MAX];

void POWTABLE() {
    fac[0] = fac[1] = 1;
    for (int i = 2; i < MAX; i++) {
        fac[i] = fac[i - 1] * i;
    }
    fac_inv[MAX - 1] = fac[MAX - 1].inv();
    for (int i = MAX - 2; i >= 0; i--) {
        fac_inv[i] = fac_inv[i + 1] * (i + 1);
    }
}

mint COM(ll n, ll k) {
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    mint res = 1;
    nrep(i, k) res *= n-i;
    return res * fac_inv[k];
}
ll N, M;
vvl g;
vl in;
vl out;
void dfs(ll v, ll p, ll& time) {
    in[v] = time++;
    for (auto nv : g[v]) {
        if (nv == p) continue;
        dfs(nv, v, time);
    }
    out[v] = time;
}
ll op(ll a, ll b) { return a + b; }
ll e() { return 0; }
mint f(){
    ll res = 0;
    return res;
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    POWTABLE();
    cin >> N;
    g.resize(N);
    nrep(i, N-1){
        ll p;
        cin >> p;
        p--;
        g[i+1].push_back(p);
        g[p].push_back(i+1);
    }
    vl parent(N, -1);
    queue<ll> que;
    que.push(0);
    vl R;
    while(!que.empty()) {
        ll i = que.front(); que.pop();
        R.push_back(i);
        for(ll v : g[i]) {
            DEBUG(v);
            if(v == parent[i]) continue;
            parent[v] = i;
            que.push(v);
        }
    }
    DEBUG(parent);
    DEBUG(g);
    DEBUG(R);
    in.resize(N);
    out.resize(N);
    vl c(N), d(N);
    nrep(i, N) cin >> c[i];    
    nrep(i, N) cin >> d[i];    
    ll time = 0;
    dfs(0, -1, time);
    segtree<ll, op, e> seg(N);
    nrep(i, N){
        seg.set(in[i], seg.get(in[i]) + c[i]);
        DEBUG(seg.get(i));
    }
    mint ans = 1;
    nrep(i, N) {
        ll v = R[N-1-i];
        DEBUG(v, seg.prod(in[v], out[v]), d[v]);
        ans *= COM(seg.prod(in[v], out[v]), d[v]);
        seg.set(in[v], seg.get(in[v]) -  d[v]);
    }
    print(ans.val());
}
