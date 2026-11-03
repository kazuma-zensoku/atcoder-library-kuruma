#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef basic_string<int> BI;
typedef long long ll;
typedef pair<int,int> PII;
typedef double db;
mt19937_64 mrand(random_device{}()); 
const ll mod=1000000007;
//int rnd(int x) { return mrand() % x;}
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
// head

const int N=111;
int a[N][N][N];
int n,q;
// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/3%E6%AC%A1%E5%85%83%E7%B4%AF%E7%A9%8D%E5%92%8C.cpp
int main() {
	scanf("%d",&n);
    //　ここ参考になる. 3次元累積和
	rep(i,1,n+1) rep(j,1,n+1) rep(k,1,n+1) scanf("%d",&a[i][j][k]);
	rep(i,1,n+1) rep(j,1,n+1) rep(k,1,n+1) a[i][j][k]+=a[i][j][k-1];
	rep(i,1,n+1) rep(j,1,n+1) rep(k,1,n+1) a[i][j][k]+=a[i][j-1][k];
	rep(i,1,n+1) rep(j,1,n+1) rep(k,1,n+1) a[i][j][k]+=a[i-1][j][k];
	scanf("%d",&q);
	rep(i,0,q) {
		int x1,x2,y1,y2,z1,z2;
		scanf("%d%d%d%d%d%d",&x1,&x2,&y1,&y2,&z1,&z2);
		--x1; --y1; --z1;
		printf("%d\n",a[x2][y2][z2]-a[x1][y2][z2]-a[x2][y1][z2]-a[x2][y2][z1]
			+a[x2][y1][z1]+a[x1][y2][z1]+a[x1][y1][z2]-a[x1][y1][z1]);
	}
}