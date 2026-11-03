// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/LIS.cpp
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
using ll = long long;

// https://qiita.com/drken/items/68b8503ad4ffb469624c
// 最長増加部分列の長さを求める
int LIS(const vector<long long> &a) {
    int N = (int)a.size();
    vector<long long> dp(N, INF);
    for (int i = 0; i < N; ++i) {
        // dp[k] >= a[i] となる最小のイテレータを見つける
        auto it = lower_bound(dp.begin(), dp.end(), a[i]);

        // そこを a[i] で書き換える
        *it = a[i];
    }

    // dp[k] < INF となる最大の k に対して k+1 が答え
    // それは dp[k] >= INF となる最小の k に一致する
    return lower_bound(dp.begin(), dp.end(), INF) - dp.begin();
}

template<class T> vector<T> LIS_array(vector<T> a,  bool is_strong = true) {
    const T INF = 1<<30; // to be set appropriately
    int n = (int)a.size();
    vector<T> res(n, INF);
    vector<T> dp(n, INF);
    for (int i = 0; i < n; ++i) {
        if (is_strong) *lower_bound(dp.begin(), dp.end(), a[i]) = a[i];
        else *upper_bound(dp.begin(), dp.end(), a[i]) = a[i];
        res[i] = lower_bound(dp.begin(), dp.end(), INF) - dp.begin();
    }
    return res;
}

// Verify: https://atcoder.jp/contests/abc006/tasks/abc006_4
int main () {
    int n; cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    cout << n - LIS(a) << endl;
}

