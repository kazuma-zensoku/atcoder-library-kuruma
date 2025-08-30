#include <iostream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <numeric>

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

template <typename T>
class SplayTree {
private:
    struct Node {
        T value;
        Node *left = nullptr, *right = nullptr, *parent = nullptr;
        int size = 1;
        Node(T val) : value(val) {}
    };

    Node* root = nullptr;

    int size_of(Node* node) { return node ? node->size : 0; }

    void update_size(Node* node) {
        if (node) {
            node->size = 1 + size_of(node->left) + size_of(node->right);
        }
    }
    
    void rotate(Node* p, bool is_left) {
        Node* c = is_left ? p->right : p->left;
        Node* gp = p->parent;

        if (gp) {
            if (gp->left == p) gp->left = c;
            else gp->right = c;
        } else {
            root = c;
        }

        if (is_left) {
            p->right = c->left;
            if (c->left) c->left->parent = p;
            c->left = p;
        } else {
            p->left = c->right;
            if (c->right) c->right->parent = p;
            c->right = p;
        }
        c->parent = gp;
        p->parent = c;
        
        update_size(p);
        update_size(c);
    }
    
    void splay(Node* node) {
        if (!node) return;
        while (node->parent) {
            Node* p = node->parent;
            Node* gp = p->parent;
            if (!gp) {
                rotate(p, p->left != node);
            } else {
                bool p_is_left = (gp->left == p);
                bool node_is_left = (p->left == node);
                if (p_is_left == node_is_left) {
                    rotate(gp, !p_is_left);
                    rotate(p, !node_is_left);
                } else {
                    rotate(p, !node_is_left);
                    rotate(gp, !p_is_left);
                }
            }
        }
    }
    
    Node* find_by_order_internal(int k) {
        Node* curr = root;
        while (curr) {
            int left_sz = size_of(curr->left);
            if (k < left_sz) {
                curr = curr->left;
            } else if (k == left_sz) {
                splay(curr);
                return curr;
            } else {
                k = k - left_sz - 1;
                curr = curr->right;
            }
        }
        return nullptr;
    }

    std::pair<Node*, Node*> split(int k) {
        if (k <= 0) return {nullptr, root};
        if (k >= size()) return {root, nullptr};
        
        Node* right_root = find_by_order_internal(k);
        Node* left_root = right_root->left;
        
        if (left_root) left_root->parent = nullptr;
        right_root->left = nullptr;
        update_size(right_root);
        
        return {left_root, right_root};
    }

    Node* merge(Node* left, Node* right) {
        if (!left) return right;
        if (!right) return left;
        
        Node* max_left = left;
        while(max_left->right) max_left = max_left->right;
        splay(max_left);
        
        max_left->right = right;
        if (right) right->parent = max_left;
        update_size(max_left);
        return max_left;
    }
    
public:
    SplayTree() = default;

    // メモリ解放を行うデストラクタ
    ~SplayTree() {
        std::vector<Node*> nodes;
        if (root) nodes.push_back(root);
        while(!nodes.empty()){
            Node* curr = nodes.back();
            nodes.pop_back();
            if(curr->left) nodes.push_back(curr->left);
            if(curr->right) nodes.push_back(curr->right);
            delete curr;
        }
    }
    
    int size() { return size_of(root); }
    
    void insert_at(int k, T value) {
        if (k < 0 || k > size()) {
            throw std::out_of_range("Insert position is out of range.");
        }
        auto [left, right] = split(k);
        Node* new_node = new Node(value);
        root = merge(merge(left, new_node), right);
    }
    
    // ★★★ 消えていた erase_at 関数 ★★★
    void erase_at(int k) {
        if (k < 0 || k >= size()) {
            throw std::out_of_range("Erase position is out of range.");
        }
        auto [left, temp] = split(k);
        auto [mid, right] = split(1); // 分割後のtempの先頭(k番目だった要素)だけを分離
        root = merge(left, right);
        if (mid) delete mid; // 削除するノードのメモリを解放
    }

    // ★★★ 消えていた get_kth_element 関数 ★★★
    T get_kth_element(int k) {
        if (k < 0 || k >= size()) {
            throw std::out_of_range("Access position is out of range.");
        }
        Node* node = find_by_order_internal(k);
        return node->value;
    }
    
    void print_in_order(Node* node, std::vector<T>& result) {
        if (!node) return;
        print_in_order(node->left, result);
        result.push_back(node->value);
        print_in_order(node->right, result);
    }
    
    std::vector<T> get_all_elements() {
        std::vector<T> result;
        if(size() > 0) result.reserve(size());
        print_in_order(root, result);
        return result;
    }
};

// --- ライブラリの検証と使い方を知るためのmain関数 ---
int main() {
    SplayTree<int> tree;
    std::cout << "## Splay Tree ライブラリテスト ##" << std::endl;

    // --- 1. 挿入テスト ---
    std::cout << "\n--- 1. 挿入テスト ---" << std::endl;
    std::cout << "初期サイズ: " << tree.size() << std::endl; // 期待値: 0

    std::cout << "インデックス 0 に 100 を挿入..." << std::endl;
    tree.insert_at(0, 100); // 木: [100]
    
    std::cout << "インデックス 1 (末尾) に 200 を挿入..." << std::endl;
    tree.insert_at(1, 200); // 木: [100, 200]

    std::cout << "インデックス 0 (先頭) に 50 を挿入..." << std::endl;
    tree.insert_at(0, 50);  // 木: [50, 100, 200]

    std::cout << "インデックス 2 (中間) に 150 を挿入..." << std::endl;
    tree.insert_at(2, 150); // 木: [50, 100, 150, 200]

    std::cout << "現在のシーケンス: ";
    auto elements = tree.get_all_elements();
    for(int x : elements) std::cout << x << " "; // 期待値: 50 100 150 200
    std::cout << "\n現在のサイズ: " << tree.size() << std::endl; // 期待値: 4

    // --- 2. アクセステスト ---
    std::cout << "\n--- 2. アクセステスト ---" << std::endl;
    std::cout << "インデックス 0 の要素: " << tree.get_kth_element(0) << std::endl; // 期待値: 50
    std::cout << "インデックス 3 の要素: " << tree.get_kth_element(3) << std::endl; // 期待値: 200
    std::cout << "インデックス 1 の要素: " << tree.get_kth_element(1) << std::endl; // 期待値: 100

    // --- 3. 削除テスト ---
    std::cout << "\n--- 3. 削除テスト ---" << std::endl;
    std::cout << "インデックス 1 (100) の要素を削除..." << std::endl;
    tree.erase_at(1); // 木: [50, 150, 200]
    
    std::cout << "現在のシーケンス: ";
    elements = tree.get_all_elements();
    for(int x : elements) std::cout << x << " "; // 期待値: 50 150 200
    std::cout << "\n" << std::endl;

    std::cout << "インデックス 2 (末尾, 200) の要素を削除..." << std::endl;
    tree.erase_at(2); // 木: [50, 150]

    std::cout << "現在のシーケンス: ";
    elements = tree.get_all_elements();
    for(int x : elements) std::cout << x << " "; // 期待値: 50 150
    std::cout << "\n" << std::endl;

    std::cout << "インデックス 0 (先頭, 50) の要素を削除..." << std::endl;
    tree.erase_at(0); // 木: [150]
    
    std::cout << "現在のシーケンス: ";
    elements = tree.get_all_elements();
    for(int x : elements) std::cout << x << " "; // 期待値: 150
    std::cout << "\n現在のサイズ: " << tree.size() << std::endl; // 期待値: 1

    std::cout << "最後の要素を削除..." << std::endl;
    tree.erase_at(0); // 木: []
    std::cout << "最終的なサイズ: " << tree.size() << std::endl; // 期待値: 0

    // --- 4. エッジケース（異常系）テスト ---
    std::cout << "\n--- 4. エッジケース（異常系）テスト ---" << std::endl;
    try {
        std::cout << "空の木に対してインデックス0へのアクセスを試行..." << std::endl;
        tree.get_kth_element(0);
    } catch (const std::out_of_range& e) {
        std::cout << "期待通りの例外をキャッチ: " << e.what() << std::endl;
    }

    try {
        std::cout << "空の木に対してインデックス5の削除を試行..." << std::endl;
        tree.erase_at(5);
    } catch (const std::out_of_range& e) {
        std::cout << "期待通りの例外をキャッチ: " << e.what() << std::endl;
    }
    std::cout << "空の木に 999 を挿入..." << std::endl;
    tree.insert_at(0, 999);
    std::cout << "インデックス 0 の要素: " << tree.get_kth_element(0) << std::endl; // 期待値: 999

    // --- 5. 大規模（負荷）テスト ---
    std::cout << "\n--- 5. 大規模（負荷）テスト ---" << std::endl;
    {
        SplayTree<int> stress_tree;
        int n = 10000;
        std::cout << n << " 個の要素を挿入中..." << std::endl;
        for (int i = 0; i < n; ++i) {
            stress_tree.insert_at(i, i + 1); // 1, 2, ..., n を挿入
        }
        std::cout << "挿入完了. サイズ: " << stress_tree.size() << std::endl; // 期待値: 10000

        std::cout << "いくつかの要素を検証中..." << std::endl;
        bool pass = true;
        if (stress_tree.get_kth_element(0) != 1) pass = false;
        if (stress_tree.get_kth_element(n - 1) != n) pass = false;
        if (stress_tree.get_kth_element(n / 2) != (n / 2) + 1) pass = false;

        if (pass) {
            std::cout << "検証成功！" << std::endl;
        } else {
            std::cout << "検証失敗！" << std::endl;
        }

        std::cout << "全要素を削除中..." << std::endl;
        for (int i = 0; i < n; ++i) {
            stress_tree.erase_at(0); // 先頭の要素を繰り返し削除
        }
        std::cout << "削除完了. 最終的なサイズ: " << stress_tree.size() << std::endl; // 期待値: 0
    }
    
    std::cout << "\n## テスト完了 ##" << std::endl;

    return 0;
}
