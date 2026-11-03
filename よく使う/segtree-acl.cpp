// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/segtree-acl.cpp
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
const vector<int> dx = {1, 0, -1, 0};
const vector<int> dy = {0, 1, 0, -1};

ll N, Q;
ll a[300009];


int op(int a, int b){return max(a, b);}
int e(){return -inf;}

int v;
bool f(int seg_val) { return seg_val < v; }

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
    cin >> N >> Q;
    segtree<int, op, e> seg(N);
    for(int i=0;i<N;i++){
        ll a;
        cin >> a;
        seg.set(i, a);
    }
    for(int i=0;i<Q;i++){
        int t;
        cin >> t;
        if(t==1){
            int x, v;
            cin>>x>>v;
            x--;
            seg.set(x, v);
        }
        else if(t==2){
            int l, r;
            cin>>l>>r;
            l--; r--;
            cout<<seg.prod(l, r+1)<<endl;
        }
        else{
            int x;
            cin>>x>>v;
            x--;
            cout<<seg.max_right<f>(x)+1<<endl;
        }
    }
  
}