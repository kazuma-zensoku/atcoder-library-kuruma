// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/%E6%8C%BF%E5%85%A5dp.cpp
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int N, K;
    cin >> N >> K;

    // dp[i][j]: i個の数で転倒数がjになるものの個数
    vector<vector<int>> dp(N + 1, vector<int>(K + 1, 0));

    // 初期条件: 0個の数で転倒数0は1通り（空の順列）
    dp[0][0] = 1;

    for (int i = 1; i <= N; ++i) {
        // dp[i-1] の累積和を計算
        vector<int> sum(K + 2, 0);
        for (int j = 0; j <= K; ++j) {
            sum[j + 1] = (sum[j] + dp[i - 1][j]) % MOD;
        }

        for (int j = 0; j <= K; ++j) {
            // iを挿入して新たに作られる転倒数は 0, 1, ..., i-1
            // 元の転倒数をkとすると、新しい転倒数は j = k + (0...i-1)
            // つまり k = j - (0...i-1)
            // よって、dp[i][j] = sum_{l=0}^{i-1} dp[i-1][j-l] を求めたい
            
            // 累積和を使って区間和を求める
            // sum_{k=max(0, j-i+1)}^{j} dp[i-1][k] を計算
            int upper_bound = j;
            int lower_bound = j - (i - 1);

            int total = (sum[upper_bound + 1] - sum[max(0, lower_bound)] + MOD) % MOD;
            dp[i][j] = total;
        }
    }

    cout << dp[N][K] << endl;

    return 0;
}