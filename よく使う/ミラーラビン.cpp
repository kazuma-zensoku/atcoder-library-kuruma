// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/%E3%83%9F%E3%83%A9%E3%83%BC%E3%83%A9%E3%83%93%E3%83%B3.cpp
#include <iostream>
#include <vector>

// using namespace std; はここに書くのが一般的
using namespace std;

// a * b mod m をオーバーフローしないように計算する
long long mul_mod(long long a, long long b, long long m) {
    return (long long)((__int128_t)a * b % m);
}

// a^b mod m を繰り返し二乗法で計算する
long long pow_mod(long long a, long long b, long long m) {
    long long res = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) res = mul_mod(res, a, m);
        a = mul_mod(a, a, m);
        b >>= 1;
    }
    return res;
}

// ミラー・ラビン素数判定法
// n が素数なら true, 合成数なら false を返す
bool miller_rabin(long long n) {
    // コーナーケースの処理
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    // n - 1 = 2^s * d となる s, d を求める
    long long d = n - 1;
    long long s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    // 64ビット整数に対して決定的であることが知られている基数のリスト
    // このリストでテストすれば、2^64 未満の全ての整数に対して正しい結果を返す
    vector<long long> bases = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    // n < 3,474,749,660,383 の場合は {2, 3, 5, 7, 11, 13, 17} で十分
    // vector<long long> bases = {2, 7, 61}; // n < 4,759,123,141 の場合

    for (long long a : bases) {
        if (n == a) return true; // nが基数自身の場合は素数

        // x = a^d mod n
        long long x = pow_mod(a, d, n);

        if (x == 1 || x == n - 1) {
            continue; // テスト合格
        }

        bool composite = true;
        for (int r = 1; r < s; ++r) {
            // x = x^2 mod n
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                composite = false;
                break; // テスト合格
            }
        }

        if (composite) {
            return false; // 合成数と確定
        }
    }

    return true; // 全てのテストを合格したので、おそらく素数
}

int main() {
    // テストしたい数
    vector<long long> test_cases = {
        2,
        7,
        13,
        97,
        561, // カーマイケル数 (合成数)
        1000000007, // 素数
        4759123141, // 素数
        9223372036854775807 // long longの最大値 (素数, メルセンヌ素数)
    };

    cout << boolalpha; // bool値を true/false で出力
    for (long long n : test_cases) {
        cout << n << " is prime? " << miller_rabin(n) << endl;
    }
    while(true) {
        long long n;
        cin >> n;
        cout << n << " is prime? " << miller_rabin(n) << endl;
    }
    return 0;
}