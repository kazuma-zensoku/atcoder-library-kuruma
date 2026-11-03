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

ll W, H;
using mint=modint998244353;
ll a[1000009];

const int MAX = 8010000;
mint fac[MAX], fac_inv[MAX];

void POWTABLE() {
    fac[0] = fac[1] = 1;
    for (int i = 2; i < MAX; i++) {
        fac[i] = fac[i - 1] * i;
    }
    fac_inv[MAX - 1] = fac[MAX - 1].inv();
    for (int i = MAX - 2; i >= 0; i--) {
        fac_inv[i] = fac_inv[i + 1] * (i + 1);
    }
}

// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/combination.cpp
mint COM(ll n, ll k) {
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * fac_inv[k] * fac_inv[n - k];
}

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
    cin >> W >> H;
    // 前処理
    POWTABLE();

    // 計算例
    cout << COM(0, 2).val() << endl;
}
