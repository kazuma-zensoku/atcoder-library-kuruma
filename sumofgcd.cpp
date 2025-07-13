#include <iostream>
#include <vector>
#include <cmath>

using ll = long long;

// φ関数（1個の整数に対して）を求める関数
ll phi(ll x) {
    ll res = x;
    for (ll p = 2; p * p <= x; ++p) {
        if (x % p == 0) {
            while (x % p == 0) x /= p;
            res -= res / p;
        }
    }
    if (x > 1) res -= res / x;
    return res;
}

// 約数列挙して計算
ll solve(ll N) {
    ll ans = 0;
    for (ll d = 1; d * d <= N; ++d) {
        if (N % d == 0) {
            ans += d * phi(N / d);
            if (d * d != N) {
                ans += (N / d) * phi(d);
            }
        }
    }
    return ans;
}

int main() {
    ll N; std::cin >> N;
    std::cout << solve(N) << "\n";
}
