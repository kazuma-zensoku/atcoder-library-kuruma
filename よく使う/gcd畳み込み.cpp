// AGC 038 C - LCMs
// https://atcoder.jp/contests/agc038/tasks/agc038_c

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
ll N, K;
ll ans;
vl primes;
vector<long long> sieve() {
    const int X = 2000009;
    vector<bool> isp(X+1, true);
    isp[0] = false;
    isp[1] = false;
    for (int i = 2; i * i <= X; i++) {
        if (isp[i]) {
            for (int j = i * i; j <= X; j += i) {
                isp[j] = false;
            }
        }
    }
    vector<long long> res;
    for (int i = 2; i <= X; i++) {
        if (isp[i]) {
            res.push_back(i);
        }
    }
    return res;
}

// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/gcd%E7%95%B3%E3%81%BF%E8%BE%BC%E3%81%BF.cpp
vc<mint> zeta(vc<mint> a) {
    vc<mint> res = a;
    for (int p : primes) { // 素数
        for(size_t i = (a.size()-1)/p; i > 0; i--) {
            res[i] += res[i*p];
        }   
    }
    return res;
}
vc<mint> mebius(vc<mint> a) {
    vc<mint> res = a;
    for (ll p : primes) { // 素数
        for(size_t i = 1; i*p < a.size(); i++) {
            res[i] -= res[i*p];
        }   
    }
    return res;
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cin >> N;
    vl a(N);
    nrep(i, N){
        cin >> a[i];
    }
    ll MX = *max_element(a.begin(), a.end());
    vc<mint> b(MX+1, 0);
    nrep(i, N) {
        b[a[i]] += a[i];
    }
    primes = sieve();
    vc<mint> zeta_a = zeta(b);
    vc<mint> y(MX+1, 0);
    nrep(i, MX+1) y[i] = zeta_a[i] * zeta_a[i];
    vc<mint> mebius_y = mebius(y); // gcd畳み込みの結果
    nrep(i, N) {
        mebius_y[a[i]] -= (a[i] * a[i]);
    }
    nrep(i, MX+1) mebius_y[i] /= 2;
    mint ans = 0;
    nfor(i, 1, MX+1) {
        ans += mebius_y[i]/i;
    }
    cout << ans.val() << endl;
}