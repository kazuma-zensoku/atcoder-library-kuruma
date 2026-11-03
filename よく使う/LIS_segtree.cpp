#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <tuple>
#include <iomanip>
#include <cmath>
#include <numeric>
#include <functional>
#include <cassert>
#include <random>
#include <bitset>
#include <complex>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
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
#define vc_cout(v){ll n = v.size();nrep(i,n)cout<<v[i]<<" \n"[i+1==n];}//一次元配列を出力する
#define vv_cout(v){ll n = v.size();nrep(i,n){nrep(j,v[i].size()){cout<<v[i][j]<<' ';}cout<<endl;}}//二次元配列を出力する
template<class T> using pq = priority_queue<T, vc<T>>;//★大きい順に取り出す コスト,頂点 bfs系で使う　小さい順じゃないですABC305E
template<class T> using pq_g = priority_queue<T, vc<T>, greater<T>>;//小さい順に取り出す　ダイクストラ法で使う
#define cout(n) cout<<n<<endl;

ll op(ll a, ll b) { return max(a, b); }
ll e() { return 0; }

// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/LIS_segtree.cpp
ll LIS(const vector<long long> &a) {
    ll N = a.size();
    // 座標圧縮
    vector<ll> aval;
    for (int i = 0; i < N; ++i) aval.push_back(a[i]);
    sort(aval.begin(), aval.end());
    aval.erase(unique(aval.begin(), aval.end()), aval.end());
    // セグメント木 (区間取得を max としたもの)
    segtree<ll, op, e> dp(aval.size() + 1);
    // 更新
    ll res = 0;
    for (ll i = 0; i < N; ++i) {
        // a[i] が何番目か
        ll h = lower_bound(aval.begin(), aval.end(), a[i]) - aval.begin();
        // 値取得
        ll A = dp.prod(0, h+1);
        // 更新
        if (A + 1 > dp.get(h)) {
            dp.set(h, A + 1);
            res = max(res, A + 1);
        }
    }
    return res;
}

// Verify: https://atcoder.jp/contests/abc006/tasks/abc006_4
int main () {
    ll n; cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    cout << n - LIS(a) << endl;
}

