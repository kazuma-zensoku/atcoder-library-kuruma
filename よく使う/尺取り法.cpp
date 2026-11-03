// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/%E5%B0%BA%E5%8F%96%E3%82%8A%E6%B3%95.cpp
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
ll X, Y;
ll f(vl &a) { // 条件を満たす最大の長さ 外側は満たさない
    ll N = a.size();
    ll res = N*(N+1)/2; 
    deque<ll> dq;
    ll cnt_X = 0;
    ll cnt_Y = 0;
    for(int i = 0; i < N; ++i) {
        ll x = a[i];
        dq.push_back(x);
        if(x == X) cnt_X++;
        if(x == Y) cnt_Y++;
        while(dq.size() > 0 && cnt_X > 0 && cnt_Y > 0) {
            if(dq.front() == X) cnt_X--;
            if(dq.front() == Y) cnt_Y--;
            dq.pop_front();
        }
        res -= dq.size();
    }
    return res;
}
ll f1_1() {
    ll r = 1;
    ll ans = 0;
    ll N = 100;
    nfor(l, 1, N+1) {
        while(r<N) {
            cout << "? " << l << " " << r+1 << endl;
            string s;
            cin >> s;
            if(s[0]=='Y') {
                r++;
            } else {
                break;
            }
        }
        ans += (r-l);
        DEBUG(l, r, ans);
        if(l==r) r++;
    }
    cout << "! " << ans << endl;
}

ll f2(vl &a) { // 条件を満たす最小の長さ 外側は満たす
    ll N = a.size();
    ll res = 0; 
    deque<ll> dq;
    ll cnt_X = 0;
    ll cnt_Y = 0;
    ll r = 0;
    for(int i = 0; i < N; ++i) {
        while(r < N && !(dq.size() > 0 && cnt_X > 0 && cnt_Y > 0)) {
            if(a[r] == X) cnt_X++;
            if(a[r] == Y) cnt_Y++;
            dq.push_back(a[r]);
            r++;
        }
        if((dq.size() > 0 && cnt_X > 0 && cnt_Y > 0)) res += N+1-r;
        ll x = dq.front();
        dq.pop_front();
        if(x == X) cnt_X--;
        if(x == Y) cnt_Y--;
    }
    return res;
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    ll N;
    cin >> N >> X >> Y;
    vl b;
    ll ans = 0;
    nrep(i, N) {
        ll x;
        cin >> x;
        if(Y<=x && x<=X) b.push_back(x);
        else {
            ans += f(b);
            b.clear();
        }
    }
    ans += f(b);
    cout(ans);
    return 0;
}