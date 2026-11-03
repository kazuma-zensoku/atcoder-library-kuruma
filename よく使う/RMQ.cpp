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

int N, Q;
int ans;

int op(int a, int b){return max(a, b);}
int e(){return 0;}

// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/RMQ.cpp
int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
    cin >> N >> Q;
    segtree<int, op, e> seg(100009);
    for(int i=0;i<Q;i++){
      int t;
      cin >> t;
      if(t==1){
        int pos, x;
        cin >> pos >> x;
        seg.set(pos ,x);
      }
      else{
        int l, r;
        cin >> l >> r;
        cout<<seg.prod(l, r)<<endl;
      }
    }
}