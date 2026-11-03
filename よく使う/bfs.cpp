// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/bfs.cpp
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
using P = pair<ll, ll>;


ll r,c;
ll sx,sy,gx,gy;
vector<string> grid;
int seen[59][59];
int dist[59][59];

int main() {
    cin>>r>>c>>sy>>sx>>gy>>gx;
    grid.resize(r);

    for(int i=0;i<r;i++) cin>>grid[i];
    queue<P> que;
    sy--; sx--; gy--;gx--;
    que.push({sy,sx});
    while(!que.empty()){
        auto [y,x] = que.front(); que.pop();
        ll ny, nx;
        for(int i=0;i<4;i++){
            ny = y + dy[i]; nx = x +dx[i];
            if(seen[ny][nx]!=0)continue;
            if(0<=nx && nx<c && 0<=ny && ny<r && grid[ny][nx]!='#'){
                dist[ny][nx] = dist[y][x] + 1;
                seen[ny][nx] = 1;
                que.push({ny,nx});
            }
        }
    }
  cout<<dist[gy][gx]<<endl;
}