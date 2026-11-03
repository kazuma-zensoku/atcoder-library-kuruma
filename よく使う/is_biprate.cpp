// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/is_biprate.cpp
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
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define nfor(i,s,n) for(ll i=s;i<n;i++)//i=s,s+1...n-1 ノーマルfor
#define rrep(i,n) for(ll i = 1; i <= (n); ++i)
#define rfor(i,s,n) for(ll i = s;i<=n;i++)//i=s,s-1...n
#define drep(i,n) for(ll i = (n)-1; i >= 0; --i)
#define dfor(i,s,n) for(ll i = (s)-1; i>=n;i--)//s-1スタートでnまで落ちる
const vector<int> dx = {1, 0, -1, 0};
const vector<int> dy = {0, 1, 0, -1};
using mint=modint998244353;
template<typename T> using vc = vector<T>;
template<typename T> using vv = vc<vc<T>>;
using vi = vc<int>; using vvi = vv<int>;
using vl = vc<ll>; using vvl = vv<ll>; using vvvl = vv<vl>; using vvvvl = vv<vvl>;
using vs = vc<string>; using vvs = vv<string>;
using P = pair<ll, ll>;
#define vc_cout(v){ll n = v.size();rep(i,n)cout<<v[i]<<" \n"[i+1==n];}//一次元配列を出力する
#define vv_cout(v){ll n = v.size();rep(i,n){rep(j,v[i].size()){cout<<v[i][j]<<' ';}cout<<endl;}}//二次元配列を出力する

ll N, M;
ll u[500009], v[500009];
ll ans, edge_size;
ll a[500009];

bool is_bipartite(vvl &g, vl &color, ll v, ll c){
    bool res=true;
    color[v]=c;
    // cout<<v<<endl;
    for(int child: g[v]){
        if(color[child]==-1){
            res &=is_bipartite(g, color, child, 1-c);
        }
        else {
            if(color[child]!=1-c) return false;
        }
    }
    return res;
}

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
    cin >> N >> M;
    dsu uf(N);
    vvl g(N);
    vl color(N, -1);
    rep(i, M){
        int u, v;
		cin>>u>>v;
        u--; v--;
        uf.merge(u, v);
        g[u].push_back(v);
        g[v].push_back(u);
	}
    int tmp=0;
    for(vi group: uf.groups()){
        int size=group.size();
        // vc_cout(group);
        edge_size=0;
        if(!is_bipartite(g, color, group[0], 0)){
            cout<<0<<endl;
            return 0;
        }
        vl count(2);
            for(int v: group){
            count[color[v]]++;
        }
        ans-=count[0]*(count[0]-1)/2+count[1]*(count[1]-1)/2;
    }
    ans+=N*(N-1)/2;
    ans-=M;
    cout<<ans<<endl; 
}