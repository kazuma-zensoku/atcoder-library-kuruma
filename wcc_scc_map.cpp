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

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cin >> N >> M;
    dsu uf(N);
    scc_graph g(N);
    nrep(i, M) {
        ll u, v;
        cin >> u >> v;
        g.add_edge(v-1, u-1);
        uf.merge(u-1, v-1);
    }
    map<int, std::vector<std::vector<int>>> wcc_scc_map;
    auto scc_groups = g.scc();
    for (const auto& scc : scc_groups) {
        if (scc.empty()) continue;
        int root = uf.leader(scc[0]); // SCC内の任意の頂点の根でOK
        wcc_scc_map[root].push_back(scc);
    }
    for (const auto& [root, sccs] : wcc_scc_map) {
        cout << "WCC Root: " << root + 1 << endl;
        for (const auto& scc : sccs) {
            cout << "  SCC: ";
            for (int v : scc) {
                cout << v + 1 << " ";
            }
            cout << endl;
        }
    }

    return 0;
}