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
#define nfor(i,s,n) for(ll i=s;i<n;i++)
#define vc_cout(v){ll n = v.size();nrep(i,n)cout<<v[i]<<" \n"[i+1==n];}
#define vv_cout(v){ll n = v.size();nrep(i,n){nrep(j,v[i].size()){cout<<v[i][j]<<' ';}cout<<endl;}}
template<class T> using pq = priority_queue<T, vc<T>>;
template<class T> using pq_g = priority_queue<T, vc<T>, greater<T>>;
#define cout(n) cout<<n<<endl;

// verify: https://atcoder.jp/contests/abc202/tasks/abc202_e
struct Edge {long long to;};

// LCA計算用セグメント木の型
struct S_rmq {long long value; long long index;};
S_rmq op_rmq(S_rmq a, S_rmq b){
    if(a.value < b.value) return a;
    else return b;
}
S_rmq E_rmq(){return {(1LL << 60),-1LL};}

ll op(ll a, ll b) {
    return a + b; // 加算を行う
}
ll e() {
    return 0; // 単位元は0
}

struct euler_tour {
    // 部分木クエリ用: in, outはオイラーツアーの入出時刻。node_depthは各頂点の深さ。
    vector<long long> in, out;
    vector<long long> node_depth;
    segtree<ll, op, e> weight; // 部分木クエリ用の重み
    // LCA用: visitはオイラーツアーの頂点列、depth_tourは各ステップの深さ、first_occurrenceは各頂点の最初の訪問位置。
    vector<long long> visit, depth_tour, first_occurrence;
    atcoder::segtree<S_rmq, op_rmq, E_rmq> rmq;
    // グラフ本体
    vector<vector<Edge>> g;
    long long n;
    int timer;

    euler_tour(long long n_val = 1) { init(n_val); }
    void init(long long n_val) {
        this->n = n_val;
        g.assign(n, vector<Edge>());
        in.assign(n, -1LL);
        out.assign(n, -1LL);
        node_depth.assign(n, -1LL);
        first_occurrence.assign(n, -1LL);
        weight = segtree<ll, op, e>(n); // 部分木クエリ用の重みを初期化
    }
    // 無向辺を追加
    void add_edge(long long u, long long v){
        g[u].push_back({v});
        g[v].push_back({u});
    }

    // in, out, node_depth, LCA用情報を記録するDFS
    void Dfs_internal(long long v_node, long long p_node, long long d_val) {
        in[v_node] = timer++;
        node_depth[v_node] = d_val;
        first_occurrence[v_node] = visit.size();
        visit.push_back(v_node);
        depth_tour.push_back(d_val);

        for (Edge edge_to_child : g[v_node]) {
            long long u_child = edge_to_child.to;
            if (u_child == p_node) continue;
            Dfs_internal(u_child, v_node, d_val + 1);
            // LCA用: 子から親に戻るときも記録
            visit.push_back(v_node);
            depth_tour.push_back(d_val);
        }
        out[v_node] = timer;
    }

    // 全情報を構築するDFSラッパー
    void build(long long root_node = 0){
        timer = 0;
        visit.clear();
        depth_tour.clear();
        Dfs_internal(root_node, -1, 0);
        // LCA用セグメント木構築
        vector<S_rmq> rmq_init_data(depth_tour.size());
        for(long long i = 0; i < (long long)depth_tour.size(); i++){
            rmq_init_data[i] = {depth_tour[i], visit[i]};
        }
        rmq = atcoder::segtree<S_rmq, op_rmq, E_rmq>(rmq_init_data);
    }
    
    // LCA: u, vの最小共通祖先
    long long lca(long long u, long long v){
        long long u_first = first_occurrence[u];
        long long v_first = first_occurrence[v];
        if (u_first > v_first) swap(u_first, v_first);
        return rmq.prod(u_first, v_first + 1).index;
    }
    // dist: u, v間の距離
    long long dist(long long u, long long v){
        long long lca_node = lca(u,v);
        return node_depth[u] + node_depth[v] - 2 * node_depth[lca_node];
    }
    // 部分木クエリ: uの部分木にwを加算
    void add_weight(long long u, long long w) {
        weight.set(in[u], weight.get(in[u]) + w);
    }
    // 部分木クエリ: uの部分木の重みを取得
    long long get_weight(long long u) {
        return weight.prod(in[u], out[u]);
    }
};

int main() {
    ll N;
    cin >> N;
    euler_tour et(N);
    vc<P> edges(N-1);
    nrep(i, N-1){
        ll u, v;
        cin >> u >> v;
        u--; v--;
        et.add_edge(u, v);
        edges[i] = {u, v}; 
    }
    et.build(0);
    nrep(i, N){
        et.add_weight(i, 1); // 各頂点の部分木の初期重みを1に設定
    }
    ll Q;
    cin >> Q;
    while(Q--){
        ll t;
        cin >> t;
        if(t == 1){
            ll x, w;
            cin >> x >> w;
            x--;
            et.add_weight(x, w);
        } else if(t == 2){
            ll y;
            cin >> y;
            y--;
            auto [u, v] = edges[y];
            if(et.in[u] > et.in[v]) swap(u, v); // uを常にinが小さい方に
            ll weight_u = et.get_weight(0) - et.get_weight(v); 
            ll weight_v = et.get_weight(v);
            cout << abs(weight_u - weight_v) << endl; 
        }
    }
    return 0;
}