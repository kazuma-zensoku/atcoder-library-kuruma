// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/splaytree_index.cpp
/*
    SplayTreeSequence<T>  ---  可変長配列として使えるSplay木

    ・std::vectorのようなインデックスアクセス・挿入・削除ができる
    ・全操作がO(logN)（最悪O(N)）
    ・区間操作や順序統計にも拡張しやすい

    --- 主な使い方 ---
    SplayTreeSequence<int> st; // 空で初期化
    SplayTreeSequence<int> st2({1,2,3}); // vectorから初期化

    st.insert(k, x); // k番目にxを挿入（0-indexed）
    st.erase(k);     // k番目を削除
    int v = st.get(k); // k番目の値を取得
    int n = st.size(); // 要素数
    std::vector<int> v = st.to_vector(); // 中身をvectorで取得

    --- 注意 ---
    ・区間和（sum）・区間反転（reverse）に対応（sum: 区間和取得, reverse: 区間反転）
    ・メモリ解放は自動ではない（必要ならデストラクタでdelete）
    ・find_by_index, insert, erase, getは全て0-indexed
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <functional>

template <typename T>
struct SplayTreeSequence {
private:
    struct Node {
        T value;
        T sum; // 部分木の区間和
        Node *left = nullptr, *right = nullptr, *parent = nullptr;
        int size = 1; // 自分を含む部分木のノード数
        bool rev = false; // 区間反転フラグ
        Node(T val, Node* p = nullptr) : value(val), sum(val), parent(p) {}
    };

    Node* root = nullptr;

    // --- 基本操作 (前回とほぼ同じ) ---

    void push(Node* x) {
        if (!x) return;
        if (x->rev) {
            std::swap(x->left, x->right);
            if (x->left) x->left->rev ^= 1;
            if (x->right) x->right->rev ^= 1;
            x->rev = false;
        }
    }

    void update(Node* x) {
        if (!x) return;
        x->size = 1;
        x->sum = x->value;
        if (x->left) {
            x->size += x->left->size;
            x->sum += x->left->sum;
        }
        if (x->right) {
            x->size += x->right->size;
            x->sum += x->right->sum;
        }
    }

    void rotate(Node* x) {
        Node* p = x->parent;
        Node* g = p->parent;
        push(p); push(x);
        if (g) {
            if (g->left == p) g->left = x; else g->right = x;
        }
        x->parent = g;
        if (p->left == x) {
            p->left = x->right;
            if (x->right) x->right->parent = p;
            x->right = p;
        } else {
            p->right = x->left;
            if (x->left) x->left->parent = p;
            x->left = p;
        }
        p->parent = x;
        update(p);
        update(x);
    }

    void splay(Node* x) {
        if (!x) return;
        while (x->parent) {
            Node* p = x->parent;
            Node* g = p->parent;
            if (g) {
                if ((g->left == p) == (p->left == x)) rotate(p);
                else rotate(x);
            }
            rotate(x);
        }
        root = x;
    }

    // k番目 (0-indexed) のノードを探して返す
    Node* find_by_index(int k) {
        if (k < 0 || k >= size()) return nullptr;
        Node* curr = root;
        while (curr) {
            push(curr);
            int left_size = curr->left ? curr->left->size : 0;
            if (k < left_size) {
                curr = curr->left;
            } else if (k == left_size) {
                splay(curr);
                return curr;
            } else {
                k -= (left_size + 1);
                curr = curr->right;
            }
        }
        return nullptr; // 到達しないはず
    }

    Node* merge(Node* t1, Node* t2) {
        if (!t1) return t2;
        if (!t2) return t1;
        Node* max_node = t1;
        while (max_node->right) {
            push(max_node);
            max_node = max_node->right;
        }
        splay(max_node);
        push(max_node); push(t2);
        max_node->right = t2;
        if (t2) t2->parent = max_node;
        update(max_node);
        return max_node;
    }

    // vectorからO(N)で木を構築するヘルパー
    Node* build_from_vector(const std::vector<T>& values, int l, int r, Node* p) {
        if (l > r) return nullptr;
        int mid = l + (r - l) / 2;
        Node* curr = new Node(values[mid], p);
        curr->left = build_from_vector(values, l, mid - 1, curr);
        curr->right = build_from_vector(values, mid + 1, r, curr);
        update(curr);
        return curr;
    }
    // [l, r) の区間を [left, mid, right] に分割
    // k番目で分割: [0,k) [k,N)
    void split(Node* t, int k, Node*& left, Node*& right) {
        if (!t) { left = right = nullptr; return; }
        if (k == 0) { left = nullptr; right = t; return; }
        Node* x = find_by_index(k-1); // k-1番目を根に
        push(x);
        left = x;
        right = x->right;
        if (right) right->parent = nullptr;
        left->right = nullptr;
        update(left); update(right);
    }

    // 区間 [l, r) を [left, mid, right] に分割
    void split3(Node* t, int l, int r, Node*& left, Node*& mid, Node*& right) {
        Node *t1, *t2;
        split(t, r, t1, right);
        split(t1, l, left, mid);
    }
public:
    // 区間 [l, r) を反転
    void reverse(int l, int r) {
        if (l >= r) return;
        Node *left, *mid, *right;
        split3(root, l, r, left, mid, right);
        if (mid) mid->rev ^= 1;
        root = merge(merge(left, mid), right);
    }

    // 区間 [l, r) の和を取得
    T range_sum(int l, int r) {
        if (l >= r) return T();
        Node *left, *mid, *right;
        split3(root, l, r, left, mid, right);
        T res = mid ? mid->sum : T();
        root = merge(merge(left, mid), right);
        return res;
    }


public:
    SplayTreeSequence() = default;

    // vectorからO(N)で構築するコンストラクタ
    SplayTreeSequence(const std::vector<T>& values) {
        if (values.empty()) return;
        root = build_from_vector(values, 0, values.size() - 1, nullptr);
    }

    // --- 公開インターフェース (インデックスベース) ---

    // インデックスkに値を挿入
    void insert(int k, const T& value) {
        if (k < 0 || k > size()) {
            throw std::out_of_range("Insert index is out of range");
        }
        Node *left, *right;
        split(root, k, left, right);
        Node* new_node = new Node(value);
        root = merge(merge(left, new_node), right);
    }

    // インデックスkの要素を削除
    void erase(int k) {
        if (k < 0 || k >= size()) {
            throw std::out_of_range("Erase index is out of range");
        }
        Node *left, *mid, *right;
        split3(root, k, k+1, left, mid, right);
        delete mid;
        root = merge(left, right);
    }

    // インデックスkの要素を取得
    T get(int k) {
        Node* target = find_by_index(k);
        if (!target) {
             throw std::out_of_range("Get index is out of range");
        }
        return target->value;
    }

    // 全体の要素数
    int size() const {
        return root ? root->size : 0;
    }

    // デバッグ用に木の内容をvectorに変換
    std::vector<T> to_vector() {
        std::vector<T> result;
        std::function<void(Node*)> in_order = 
            [&](Node* n) {
            if (!n) return;
            push(n);
            in_order(n->left);
            result.push_back(n->value);
            in_order(n->right);
        };
        in_order(root);
        return result;
    }
};

void print_vector(const std::vector<int>& vec) {
    for (int x : vec) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

// --- 使用例 ---
int main() {
    std::vector<int> initial_values = {4, 7, 3, 2, 6};
    SplayTreeSequence<int> st(initial_values);

    std::cout << "Initial sequence: ";
    print_vector(st.to_vector()); // 4 7 3 2 6

    std::cout << "\n--- Query: Insert 9 at index 3 ---" << std::endl;
    st.insert(3, 9);
    std::cout << "After insert(3, 9): ";
    print_vector(st.to_vector()); // 4 7 3 9 2 6
    std::cout << "Current size: " << st.size() << std::endl; // 6

    std::cout << "\n--- Query: Erase element at index 1 ---" << std::endl;
    st.erase(1); // 7を削除
    std::cout << "After erase(1): ";
    print_vector(st.to_vector()); // 4 3 9 2 6
    std::cout << "Current size: " << st.size() << std::endl; // 5

    std::cout << "\n--- Query: Get element at index 2 ---" << std::endl;
    std::cout << "Element at index 2 is: " << st.get(2) << std::endl; // 9

    std::cout << "\n--- Query: Reverse [1, 4) ---" << std::endl;
    st.reverse(1, 4); // 3 9 2 を反転
    print_vector(st.to_vector()); // 4 2 9 3 6

    std::cout << "\n--- Query: Range sum [1, 4) ---" << std::endl;
    std::cout << "Sum of [1, 4): " << st.range_sum(1, 4) << std::endl; // 2+9+3=14

    std::cout << "\n--- Final sequence ---" << std::endl;
    print_vector(st.to_vector());
    return 0;
}