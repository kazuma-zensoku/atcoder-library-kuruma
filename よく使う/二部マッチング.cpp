// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/%E4%BA%8C%E9%83%A8%E3%83%9E%E3%83%83%E3%83%81%E3%83%B3%E3%82%B0.cpp
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

// 単なるcout関数
template<typename T>
void print(const T& n) {
    cout << n << "\n";
}
// デバッグ出力ユーティリティ
// 基本型（数値系）
template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
void debug_print(const T& v) { cout << v; }
// string
inline void debug_print(const std::string& s) { cout << s; }
inline void debug_print(const char* s) { cout << s; }
// pair
template<typename A, typename B>
void debug_print(const std::pair<A, B>& p) {
    cout << "{";
    debug_print(p.first);
    cout << ", ";
    debug_print(p.second);
    cout << "}";
}
// queue
template<typename T, typename Cont>
void debug_print(const std::queue<T, Cont>& q) {
    auto q2 = q;
    cout << "queue[";
    while (!q2.empty()) {
        debug_print(q2.front());
        q2.pop();
        if (!q2.empty()) cout << ", ";
    }
    cout << "]";
}
// stack
template<typename T, typename Cont>
void debug_print(const std::stack<T, Cont>& s) {
    auto s2 = s;
    cout << "stack[";
    std::vector<T> tmp;
    while (!s2.empty()) {
        tmp.push_back(s2.top());
        s2.pop();
    }
    for (size_t i = 0; i < tmp.size(); ++i) {
        debug_print(tmp[i]);
        if (i + 1 != tmp.size()) cout << ", ";
    }
    cout << "]";
}
// priority_queue
template<typename T, typename Cont, typename Comp>
void debug_print(const std::priority_queue<T, Cont, Comp>& pq) {
    auto q2 = pq;
    cout << "priority_queue[";
    std::vector<T> tmp;
    while (!q2.empty()) {
        tmp.push_back(q2.top());
        q2.pop();
    }
    for (size_t i = 0; i < tmp.size(); ++i) {
        debug_print(tmp[i]);
        if (i + 1 != tmp.size()) cout << ", ";
    }
    cout << "]";
}
// イテレータを持つコンテナ（string, queue, stack, priority_queue 以外）
template<typename T>
auto debug_print(const T& c) -> decltype(std::begin(c), void()) {
    cout << "[";
    auto it = std::begin(c);
    while (it != std::end(c)) {
        debug_print(*it);
        if (++it != std::end(c)) cout << ", ";
    }
    cout << "]";
}
// デバッグ用のマクロ（変数名と値を一緒に出力）
#ifndef ONLINE_JUDGE
#define DEBUG(...) cerr << #__VA_ARGS__ << " = "; debug_print(__VA_ARGS__); cerr << endl;
#else
#define DEBUG(...)
#endif  
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
ll N, M;
// https://atcoder.jp/contests/abc434/tasks/abc434_e
int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cin >> N;
    map<ll, ll> pos2idx;
    ll id = N;
    mf_graph<ll> mf(4*N);
    nrep(i, N){
        ll x, r;
        cin >> x >> r;
        if(!pos2idx.count(x-r)) pos2idx[x-r] = id++;
        if(!pos2idx.count(x+r)) pos2idx[x+r] = id++;
        ll u = pos2idx[x-r];
        ll v = pos2idx[x+r];
        mf.add_edge(i, v, 1ll);
        mf.add_edge(i, u, 1ll);
    }
    ll S = id++;
    ll T = id++;
    for(auto[p, idx]: pos2idx){
        mf.add_edge(idx, T, 1ll);
    }
    nrep(i, N){
        mf.add_edge(S, i, 1ll);
    }
    ll flow = mf.flow(S, T);
    print(flow);
}
