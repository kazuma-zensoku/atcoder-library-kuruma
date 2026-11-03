// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/%E5%BA%A7%E6%A8%99%E5%9C%A7%E7%B8%AE.cpp
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

// 座標圧縮の配列を返す
// avalは圧縮後の値の配列
// resは元の配列の各要素が圧縮後の何番目に対応するかを示す配列
// res[i].firstは元の配列のインデックス、res[i].secondは圧縮後のインデックス
pair<vl, vc<P>> compress(vector<long long> &a) {
    vector<long long> aval;
    for (int i = 0; i < a.size(); ++i) aval.push_back(a[i]);
    sort(aval.begin(), aval.end());
    aval.erase(unique(aval.begin(), aval.end()), aval.end());
    vc<P> res(a.size());
    for (int i = 0; i < a.size(); ++i) {
        res[i].second = lower_bound(aval.begin(), aval.end(), a[i]) - aval.begin();
        res[i].first = i;
    }
    return {aval, res};
}

int main() {
    // 座標圧縮したい数列
    vector<int> A = {8, 100, 33, 33, 33, 12, 6, 1211};

    // コピー
    vector<int> B = A;
    
    // B を小さい順にソート
    sort(B.begin(), B.end());
    
    // B から重複を除去する
    B.erase(unique(B.begin(), B.end()), B.end());

    // 座標圧縮した結果を求める
    vector<int> res(A.size());
    for (int i = 0; i < A.size(); ++i) {
        res[i] = lower_bound(B.begin(), B.end(), A[i]) - B.begin();
    }


    for (auto v: res) cout << v << ", ";
    cout << endl;
}