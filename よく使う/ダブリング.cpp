// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/%E3%83%80%E3%83%96%E3%83%AA%E3%83%B3%E3%82%B0.cpp
// https://atcoder.jp/contests/abc367/submissions/57153095

#include <bits/stdc++.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
using ll = long long;
using Graph = vector<vector<ll>>;
const int inf = INT_MAX / 2;
const ll infl = 1LL << 60;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }
const vector<int> dx = {1, 0, -1, 0};
const vector<int> dy = {0, 1, 0, -1};
using mint=modint998244353;
template<typename T> using vc = vector<T>;
template<typename T> using vv = vc<vc<T>>;
using vi = vc<int>; using vvi = vv<int>;
using vl = vc<ll>; using vvl = vv<ll>; using vvvl = vv<vl>; using vvvvl = vv<vvl>;
using vs = vc<string>; using vvs = vv<string>;
using P = pair<ll, ll>;
#define nrep(i,n) for (int i = 0; i < (n); ++i)
#define rrep(i,n) for(ll i = 1; i <= (n); ++i)
#define drep(i,n) for(ll i = (n)-1; i >= 0; --i)
#define nfor(i,s,n) for(ll i=s;i<n;i++)//i=s,s+1...n-1 ノーマルfor
#define rfor(i,s,n) for(ll i = s;i<=n;i++)//i=s,s-1...n
#define dfor(i,s,n) for(ll i = (s)-1; i>=n;i--)//s-1スタートでnまで落ちる
#define vc_cout(v){ll n = v.size();nrep(i,n)cout<<v[i]<<" \n"[i+1==n];}//一次元配列を出力する
#define vv_cout(v){ll n = v.size();nrep(i,n){nrep(j,v[i].size()){cout<<v[i][j]<<' ';}cout<<endl;}}//二次元配列を出力する
template<class T> using pq = priority_queue<T, vc<T>>;//★大きい順に取り出す コスト,頂点 bfs系で使う　小さい順じゃないですABC305E
template<class T> using pq_g = priority_queue<T, vc<T>, greater<T>>;//小さい順に取り出す　ダイクストラ法で使う
#define dame cout<<-1<<endl
#define YES cout<<"Yes"<<endl
#define NO cout<<"No"<<endl
#define YN {cout<<"Yes"<<endl;}else{cout<<"No"<<endl;}// if(ans[i])YN;
#define cout(n) cout<<n<<endl;
ll N, K;
ll ans;
vl x, a;

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
    cin >> N >> K;
    a.resize(N);
    x.resize(N);
	nrep(i, N){
		cin>>x[i];
        x[i]--;
	}
    nrep(i, N){
        cin>>a[i];
    }
    vvl dp(70, vl(N, 0));
    nrep(i, N){
        dp[0][i] = x[i];
    }
    nfor(i, 1, 70){
        nfor(j, 0, N){
            dp[i][j] = dp[i-1][dp[i-1][j]];
        }
    }
    // vc_cout(dp[2]);
    vl f(N, 0);
    nrep(i, N){
        f[i]=i;
    }
    nrep(i, N){
        ll j=0;
        ll tmp=K;
        while(tmp>0){
            if(tmp&1){
                f[i]=dp[j][f[i]];
            }
            tmp>>=1;
            j++;
        }
    }
    nrep(i, N){
        cout<<a[f[i]]<<" \n"[i+1==N];
    }



  
}