// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/unionfind_weighted.cpp
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

template <typename T>
class WeightedUnionFind {
private:
    vector<int> parent;
    vector<T> diff_weight;

public:
    WeightedUnionFind(int n) {
        parent.resize(n, -1); // サイズ管理のため負の値で初期化
        diff_weight.resize(n, T(0));
    }

    int find(int x) {
        if (parent[x] < 0) {
            return x;
        }
        int root = find(parent[x]);
        diff_weight[x] += diff_weight[parent[x]];
        return parent[x] = root;
    }

    // xが属するグループのサイズを取得
    int size(int x) {
        return -parent[find(x)];
    }

    // weight(y) - weight(x) = w となるように合併
    bool unite(int x, int y, T w) {
        int root_x = find(x);
        int root_y = find(y);

        if (root_x == root_y) {
            // 既に連結なら矛盾チェック
            if (difference(x, y) != w) {
                // 矛盾
                return false;
            }
            // 既に同じ差分で連結済み（何もしないが成功扱い）
            return true;
        }

        // Union by Size: サイズが小さい方を大きい方につなぐ
        if (size(root_x) < size(root_y)) {
            swap(root_x, root_y);
            w = -w;
            diff_weight[root_y] = diff_weight[y] - diff_weight[x] - w;
            parent[root_x] += parent[root_y];
            parent[root_y] = root_x;
        } else {
            diff_weight[root_y] = diff_weight[x] - diff_weight[y] + w;
            parent[root_x] += parent[root_y];
            parent[root_y] = root_x;
        }

        return true;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    T difference(int x, int y) {
        if (!same(x, y)) {
            // 連結でなければ -1 を返す
            return T(-1);
        }
        return diff_weight[y] - diff_weight[x];
    }
};

// --- 使用例 ---
int main() {
    WeightedUnionFind<int> wuf(5); // 5つの要素 {0, 1, 2, 3, 4}

    wuf.unite(0, 1, 10); // v[1] - v[0] = 10
    wuf.unite(1, 2, 20); // v[2] - v[1] = 20
    wuf.unite(3, 4, 30); // v[4] - v[3] = 30

    cout << "Size of component containing 1: " << wuf.size(1) << endl; // 3
    cout << "Size of component containing 4: " << wuf.size(4) << endl; // 2

    // サイズが大きい方(0,1,2)に、小さい方(3,4)が合併される
    wuf.unite(0, 3, 100); // v[3] - v[0] = 100

    cout << "\nAfter merging all components:" << endl;
    cout << "Size of component containing 2: " << wuf.size(2) << endl; // 5

    // v[4] - v[2] を計算してみる
    // v[4] - v[3] = 30
    // v[3] - v[0] = 100
    // v[0] - v[2] = -(v[2]-v[0]) = -30
    // v[4]-v[2] = (v[4]-v[3])+(v[3]-v[0])+(v[0]-v[2]) = 30 + 100 - 30 = 100
    cout << "Difference between 4 and 2: " << wuf.difference(2, 4) << endl; // 100

    return 0;
}