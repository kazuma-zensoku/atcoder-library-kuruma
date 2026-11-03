// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/unionfindMinLeader.cpp
#include <vector>
#include <numeric>      // std::iota のため
#include <algorithm>    // std::swap, std::sort (groupsでソートする場合など)
#include <map>          // groups の実装を簡単にするため

struct UnionFindMinLeader {
    std::vector<int> parent; // 親ノード。自身が代表元の場合、parent[i] = i。
    std::vector<int> sz;     // 各代表元が持つ集合のサイズ（オプションだが便利）

    // コンストラクタ
    UnionFindMinLeader(int n = 1) {
        init(n);
    }

    // 初期化
    void init(int n = 1) {
        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0); // parent[i] = i で初期化
        sz.assign(n, 1); // 各要素は初めサイズ1の集合
    }

    // 代表元（リーダー）を返す（経路圧縮付き）
    int root(int x) {
        if (parent[x] == x) {
            return x;
        }
        // 経路圧縮: xの親を根に直接つなぎ直す
        return parent[x] = root(parent[x]);
    }

    // 2つの要素が同じ集合に属するかどうか
    bool issame(int x, int y) {
        return root(x) == root(y);
    }

    // 2つの要素が属する集合を統合する
    // 新しい代表元は、元の2つの代表元のうちインデックスが小さい方になる
    bool merge(int x, int y) {
        int root_x = root(x);
        int root_y = root(y);

        if (root_x == root_y) {
            return false; // 既に同じ集合
        }

        // root_x が常にインデックスが小さい代表元になるようにする
        if (root_x > root_y) {
            std::swap(root_x, root_y);
        }

        // root_y を root_x の子にする (root_x が新しい代表元)
        parent[root_y] = root_x;
        sz[root_x] += sz[root_y]; // サイズを更新
        // sz[root_y] の値はもはや代表元ではないので意味を持たないが、クリアしなくても動作に支障はない

        return true;
    }

    // 指定した要素が属する集合のサイズを返す
    int size(int x) {
        return sz[root(x)];
    }

    // 全ての連結成分（グループ）をリストのリストとして返す
    // 例: {{0, 2}, {1, 3, 4}}
    std::vector<std::vector<int>> groups() {
        int n = parent.size();
        std::map<int, std::vector<int>> leader_to_members_map;

        // 各要素について、その代表元を見つけてマップに追加
        for (int i = 0; i < n; ++i) {
            leader_to_members_map[root(i)].push_back(i);
        }

        // マップから結果のリストを作成
        std::vector<std::vector<int>> result_groups;
        for (auto const& pair : leader_to_members_map) {
            result_groups.push_back(pair.second);
        }

        return result_groups;
    }
};