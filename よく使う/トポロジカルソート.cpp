#include <bits/stdc++.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
using ll = long long; using mint=modint998244353;
const int inf = INT_MAX / 2; const ll infl = 1LL << 60;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }
const vector<int> dx = {1, 0, -1, 0}; const vector<int> dy = {0, 1, 0, -1};
template<typename T> using vc = vector<T>; template<typename T> using vv = vc<vc<T>>;
using vi = vc<int>;  using vvi = vv<int>; using vl = vc<ll>; using vvl = vv<ll>; using vvvl = vv<vl>; using vvvvl = vv<vvl>;
using vs = vc<string>; using vvs = vv<string>; using P = pair<ll, ll>;
#define nrep(i,n) for (int i = 0; i < (n); ++i)
#define nfor(i,s,n) for(ll i=s;i<n;i++)//i=s,s+1...n-1 ノーマルfor
#define vc_cout(v){ll n = v.size();nrep(i,n)cout<<v[i]<<" \n"[i+1==n];}//一次元配列を出力する
#define vv_cout(v){ll n = v.size();nrep(i,n){nrep(j,v[i].size()){cout<<v[i][j]<<' ';}cout<<endl;}}//二次元配列を出力する
template<class T> using pq = priority_queue<T, vc<T>>;//★大きい順に取り出す コスト,頂点 bfs系で使う　小さい順じゃないですABC305E
template<class T> using pq_g = priority_queue<T, vc<T>, greater<T>>;//小さい順に取り出す　ダイクストラ法で使う
#define cout(n) cout<<n<<endl;
ll N, M;

// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/%E3%83%88%E3%83%9D%E3%83%AD%E3%82%B8%E3%82%AB%E3%83%AB%E3%82%BD%E3%83%BC%E3%83%88.cpp
int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	cin >> N >> M;
	vl a(N), deg(N, 0);
    vvl g(N);
	nrep(i, M){
        ll a, b; cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        deg[b]++;
	}
    pq_g<ll> pq;
    vl ans;
    nrep(i, N){
        if(deg[i] == 0) pq.push(i);
    }
    while(!pq.empty()){
        ll now = pq.top(); pq.pop();
        ans.push_back(now+1);
        for(auto next : g[now]){
            deg[next]--;
            if(deg[next] == 0) pq.push(next);
        }
    }
    if(ans.size() != N) cout << -1 << endl;
    else vc_cout(ans);
}