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
ll h, w;

// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/bfs%E7%B5%8C%E8%B7%AF%E5%BE%A9%E5%85%83.cpp
int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cin >> h >> w;
    vc<string> s(h);
    nrep(i, h){
        cin >> s[i];
    }
    ll sr, sc, gr, gc, gdir;
    nrep(i, h) nrep(j, w) {
        if(s[i][j] == 'S') {
            sr = i, sc = j;
        }
        if(s[i][j] == 'G') {
            gr = i, gc = j;
        }
    }
    // cout << sr << " " << sc << endl;
    vvvl dist(h+5, vvl(w, vl(4, -1))); // DRUL 0123
    vvvc<tuple<ll,ll,ll>> prev(h+5, vvc<tuple<ll,ll,ll>>(w, vc<tuple<ll,ll,ll>>(4, {-1,-1,-1}))); // DRUL 0123
    queue<tuple<ll,ll,ll>> q;
    nrep(i, 4) {
        dist[sr][sc][i] = 0;
        q.push({sr, sc, i});
    }
    bool ok = false;
    while (!q.empty()) {
        auto [r, c, dir] = q.front(); q.pop();
        // cout << r << " " << c << " " << dir << endl;
        if(r == gr && c == gc) {
            // cout << "goal: ";
            //         cout << r << " " << c << " " << dir << endl;  
            gdir = dir;
            ok = true;
            break;
        }
        nrep(i, 4) {
            if(s[r][c] == 'o') {
                if(i != dir) continue;
            }
            if(s[r][c] == 'x') {
                if(i == dir) continue;
            }
            ll nr = r + dx[i];
            ll nc = c + dy[i];
        //     cout << "next: ";
        // cout << nr << " " << nc << endl;            
            if(0<=nr && nr<h && 0<=nc && nc<w && s[nr][nc]!='#'){
                if(dist[nr][nc][i]!=-1)continue;
                dist[nr][nc][i] = dist[r][c][dir] + 1;
                prev[nr][nc][i] = {r,c,dir};
                q.push({nr,nc, i});
            }
        }
    }
    if(!ok) {
        print("No");
        return 0;
    }
//     nrep(p, 4){
//     nrep(i, h) {
//         nrep(j, w) {
//             cerr << dist[i][j][p] << " ";
//         }
//         cerr << endl;
//     }
//     cerr << endl;
// }
    print("Yes");
    string ans = "";
    ll r = gr, c = gc, dir = gdir;
    ll d = dist[r][c][dir];
    if(dir == 0) ans += "D";
    if(dir == 1) ans += "R";
    if(dir == 2) ans += "U";
    if(dir == 3) ans += "L";
    while(d>1) {
        // cout << r << " " << c << " " << dir << " " << d << endl;  
        auto [nr,nc,ndir] = prev[r][c][dir];
        r=nr,c=nc,dir=ndir;
        if(dir == 0) ans += "D";
        if(dir == 1) ans += "R";
        if(dir == 2) ans += "U";
        if(dir == 3) ans += "L";
        d--;
    }
    reverse(ans.begin(), ans.end());
    print(ans);

}
