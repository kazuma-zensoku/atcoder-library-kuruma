// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/%E3%82%AA%E3%82%A4%E3%83%A9%E3%83%BC%E3%81%AE%E3%83%95%E3%82%A1%E3%82%A4%E9%96%A2%E6%95%B0.cpp
#include <bits/stdc++.h>
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

vector<int> euler_phi_table(int N) {
    std::vector<int> phi(N + 1);
    for (int i = 0; i <= N; ++i) {
        phi[i] = i;
    }
    for (int i = 2; i <= N; ++i) {
        if (phi[i] == i) { // iが素数の場合
            for (int j = i; j <= N; j = j + i) {
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
    return phi;
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cin >> N;
    vector<int> phi = euler_phi_table(N);
    nrep(i, N + 1) {
        cout << "φ(" << i << ") = " << phi[i] << endl;
    }
}