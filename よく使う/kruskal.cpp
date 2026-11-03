// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/kruskal.cpp
// https://qiita.com/drken/items/cce6fc5c579051e64fab
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
ll N, M;
struct Edge{
    ll from, to, cost;
};

int main() {
    int N, M;
    cin >> N >> M;
    vc<Edge> edge(M);
    nrep(i, M){
        ll k, c;
        cin >> k >> c;
        vl a;
        nrep(j, k){
            ll x;
            cin >> x;
            x--;
            a.push_back(x);
        }
        nrep(j, k){
            edge.push_back({a[j], a[(j+1)%k], c});
        }
    }
    sort(edge.begin(), edge.end(), [](Edge a, Edge b){return a.cost < b.cost;});
    dsu uf(N);
    ll ans = 0;
    for(auto e : edge){
        if(!uf.same(e.from, e.to)){
            uf.merge(e.from, e.to);
            ans += e.cost;
        }
    }
    auto g = uf.groups();
    if(g.size() != 1) cout << -1 << endl;
    else cout << ans << endl;
    return 0;
}
