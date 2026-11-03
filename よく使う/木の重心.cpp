// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/%E6%9C%A8%E3%81%AE%E9%87%8D%E5%BF%83.cpp
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
string S;
ll ans;

vector<ll> Centroid(const vector<vector<ll>> &g) {
        int n = g.size();
        vector<ll> centroid;
        vector<ll> sz(n);
        function<void (ll, ll)> dfs = [&](int u, int prev) {
                sz[u] = 1;
                bool is_centroid = true;
                for (auto v : g[u]) if (v != prev) {
                        dfs(v, u);
                        sz[u] += sz[v];
                        if (sz[v] > n / 2) is_centroid = false;
                }
                if (n - sz[u] > n / 2) is_centroid = false;
                if (is_centroid) centroid.push_back(u);
        };
        dfs(0, -1);
        return centroid;
}


int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cin >> N;
    vvl G(N);
    nrep(i, N-1){
        ll a, b;
        cin >> a >> b;
        a--; b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    ll max_x = 0;
    ll max_y = 0;
    vector<ll> centroid = Centroid(G);
    for (int c = 0; c < N; c++){ 
        ll res = 0;
        vl child_num;
        nrep(i, G[c].size()){
            ll child = G[c][i];
            child_num.push_back(G[child].size()-1);
        }
        sort(child_num.begin(), child_num.end());
        ll size = child_num.size();
        nrep(i, size){
            ll x = size - i;
            ll y = child_num[i];
            if (y==0) continue;
            if(chmax(res, x*y+x+1)){
                max_x = x;
                max_y = y;
            }
        }
        chmax(ans, res);
    }
    cout << N-ans << endl;
    return 0;
}