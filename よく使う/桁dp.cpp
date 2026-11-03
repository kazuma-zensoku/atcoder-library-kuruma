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

string S; // N を文字列化したもの
ll memo[20][2][11][2]; // pos, tight, prev is_leading_zero

// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/%E6%A1%81dp.cpp
ll solve(int pos, bool tight, int prev, bool is_leading_zero) {
    if (pos == S.length()) {
        return 1;
    }
    if (memo[pos][tight][prev][is_leading_zero] != -1) {
        return memo[pos][tight][prev][is_leading_zero];
    }
    ll res = 0;
    int limit = tight ? (S[pos] - '0') : 9;
    for (int digit = 0; digit <= limit; ++digit) {
        if (is_leading_zero && digit == 0) {
            res += solve(pos + 1, tight && (digit == limit), 10, true);
        } else {
            if (digit == prev) continue; // 前の桁と同じ数字は使わない
            bool new_tight = tight && (digit == limit);
            bool new_is_leading_zero = false; 
            res += solve(pos + 1, new_tight, digit, new_is_leading_zero);
        }
    }
    return memo[pos][tight][prev][is_leading_zero] = res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll T;
    cin >> T;
    while (T--) {
        ll n;
        cin >> n; 
        n++;
        ll ng = -1, ok = 1e18+1;
        while(ok - ng > 1) {
            ll mid = (ok + ng) / 2;
            S = to_string(mid);
            memset(memo, -1, sizeof(memo));
            ll result = solve(0, true, 10, true); // 初期状態では先行ゼロが続いている
            if (result >= n) {
                ok = mid; 
            } else {
                ng = mid; 
            }
        }
        cout << ok << endl;
    }
    return 0;
}