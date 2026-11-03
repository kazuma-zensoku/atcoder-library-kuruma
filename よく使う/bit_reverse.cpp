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
ll T;
ll ans;
ll POW(ll a, ll t) {
    ll res = 1;
    for (int i = 0; i < t; i++) res *= a;
    return res;
}

void ll2bit(ll n, ll k) {
    string s = "";
    while(n > 0) {
        s += (n % 2) + '0';
        n /= 2;
    }
    reverse(s.begin(), s.end());
    while(s.size() < k) s = '0' + s;
    cout << s << endl;
}
// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/bit_reverse.cpp
ll bit_reverse(ll n, ll k) {
    ll res = 0;
    for (int i = 0; i < k; i++) {
        res <<= 1;
        res += n & 1;
        n >>= 1;
    }
    return res;
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cin >> T;
    while(T--){
        ll N, K;
        cin >> N >> K;
        ll res = 1;
        ll MX = POW(2, K-1);
        vl ans;
        if(N > MX) {
            ans.resize(N, MX);
            nrep(i, MX) {
                ans[i] += i;
            }
        } else {
            // cout << MX << endl;
            ll x = 0;
            while(1) {
                if(N > MX/2) break;
                MX /= 2;
                x++;
            }
            ans.resize(N, POW(2, K-1));
            nrep(i, N) {
                ans[i] += bit_reverse(i, K-1-x) * POW(2, x);
            }
        }
        // nrep(i, N) {
        //     ll2bit(ans[i], K);
        // }
        vc_cout(ans);
    }
}