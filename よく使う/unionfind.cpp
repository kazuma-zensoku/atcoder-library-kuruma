// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/unionfind.cpp
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class UnionFind {
private:
    vector<int> parent;

public:
    vector<int> min_node; 
    UnionFind(int n) {
        parent.resize(n, -1); 
        min_node.resize(n);
        iota(min_node.begin(), min_node.end(), 0); 
    }

    int find(int x) {
        if (parent[x] < 0) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    bool unite(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);

        if (root_x == root_y) {
            return false;
        }

        if (size(root_x) < size(root_y)) {
            swap(root_x, root_y);
        }

        parent[root_x] += parent[root_y];
        parent[root_y] = root_x;
        min_node[root_x] = min(min_node[root_x], min_node[root_y]);

        return true;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int size(int x) {
        return -parent[find(x)];
    }

    int get_min_node(int x) {
        return min_node[find(x)];
    }
};

// --- 使用例 ---
int main() {
    // 10個の要素 (0から9) で初期化
    UnionFind uf(10);

    cout << "--- Unite Operations ---" << endl;
    uf.unite(0, 1);
    uf.unite(1, 2);
    uf.unite(3, 4);
    uf.unite(5, 6);
    uf.unite(6, 7);
    uf.unite(8, 9);
    
    // グループ: {0,1,2}, {3,4}, {5,6,7}, {8,9}

    cout << "\n--- Same Check ---" << endl;
    cout << "same(0, 2): " << (uf.same(0, 2) ? "true" : "false") << endl; // true
    cout << "same(0, 3): " << (uf.same(0, 3) ? "true" : "false") << endl; // false

    cout << "\n--- Size Check ---" << endl;
    cout << "Size of group containing 6: " << uf.size(6) << endl; // 3

    cout << "\n--- Further Unite ---" << endl;
    uf.unite(2, 7); // {0,1,2}グループと{5,6,7}グループを合併
    cout << "Size of group containing 0 after merge: " << uf.size(0) << endl; // 6
    cout << "same(1, 6): " << (uf.same(1, 6) ? "true" : "false") << endl; // true

    return 0;
}