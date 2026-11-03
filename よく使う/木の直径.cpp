// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/%E6%9C%A8%E3%81%AE%E7%9B%B4%E5%BE%84.cpp
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
ll N, M;
ll ans;
ll a[500009], b[500009];

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
    cin >> N;
    vvl G(N);
	nrep(i, N-1){
        int a, b;
		cin >> a >> b;
        a--; b--;
        G[a].push_back(b);
        G[b].push_back(a);
	}
    queue<int> q;
    q.push(0);
    vi dist(N, -1);
    dist[0] = 0;
    while(!q.empty()){
        int v = q.front(); q.pop();
        for(int nv : G[v]){
            if(dist[nv] != -1) continue;
            dist[nv] = dist[v] + 1;
            q.push(nv);
        }
    }
    int maxv = 0;
    int maxd = 0;
    nrep(i, N){
        if(chmax(maxd, dist[i])){
            maxv = i;
        }
    }
    q.push(maxv);
    vi dist2(N, -1);
    dist2[maxv] = 0;
    while(!q.empty()){
        int v = q.front(); q.pop();
        for(int nv : G[v]){
            if(dist2[nv] != -1) continue;
            dist2[nv] = dist2[v] + 1;
            q.push(nv);
        }
    }
    int ans = 0;
    nrep(i, N){
        chmax(ans, dist2[i]);
    }
    cout<<ans+1<<endl;    


  
}