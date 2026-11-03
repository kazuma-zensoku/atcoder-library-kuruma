// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/splaytree_value.cpp
/*
    SplayTreeValue<T>  ---  値順（BST順）で管理するSplay木

    ・std::set/std::multisetのような値順アクセス・挿入・削除ができる
    ・全操作O(logN)（最悪O(N)）
    ・find, lower_bound, upper_bound, erase, insert, size, to_vector など
    ・値の重複可否はis_multisetで切り替え可能

    --- 主な使い方 ---
    SplayTreeValue<int> st; // 空で初期化
    st.insert(5);
    st.insert(2);
    st.insert(8);
    st.erase(2); // 値2を削除
    bool found = st.find(5); // 5が存在するか
    int n = st.size();
    std::vector<int> v = st.to_vector(); // 昇順vector

    --- 注意 ---
    ・区間和や区間反転などは未実装（必要ならNode構造体とupdate/splayを拡張）
    ・k番目取得（0-indexed）は get_kth(k) で可能
    ・erase, find, lower_bound, upper_boundは値順
    ・is_multiset=trueで重複可
    // k番目(0-indexed)のノードを返す
    Node* find_by_index(int k) {
        Node* curr = root;
        while (curr) {
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
        return nullptr;
    }
    // k番目(0-indexed)の値を取得
    T get_kth(int k) {
        Node* n = this->find_by_index(k);
        if (!n) throw std::out_of_range("get_kth: index out of range");
        return n->value;
    }
*/

#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>

// is_multiset=trueでmultiset, falseでset

template <typename T, bool is_multiset=false>
struct SplayTreeValue {
private:
    struct Node {
        T value;
        Node *left = nullptr, *right = nullptr, *parent = nullptr;
        int size = 1;
        Node(T val, Node* p = nullptr) : value(val), parent(p) {}
    };
    Node* root = nullptr;

    void update(Node* x) {
        if (!x) return;
        x->size = 1;
        if (x->left) x->size += x->left->size;
        if (x->right) x->size += x->right->size;
    }
    void rotate(Node* x) {
        Node* p = x->parent;
        Node* g = p->parent;
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
    Node* find_node(const T& value) {
        Node* curr = root;
        while (curr) {
            if (value < curr->value) curr = curr->left;
            else if (curr->value < value) curr = curr->right;
            else return curr;
        }
        return nullptr;
    }
    Node* lower_bound_node(const T& value) {
        Node* curr = root;
        Node* res = nullptr;
        while (curr) {
            if (!(curr->value < value)) {
                res = curr;
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return res;
    }
    Node* upper_bound_node(const T& value) {
        Node* curr = root;
        Node* res = nullptr;
        while (curr) {
            if (value < curr->value) {
                res = curr;
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return res;
    }
    void insert_node(const T& value) {
        if (!root) {
            root = new Node(value);
            return;
        }
        Node* curr = root;
        Node* p = nullptr;
        while (curr) {
            p = curr;
            if (value < curr->value) curr = curr->left;
            else if (curr->value < value) curr = curr->right;
            else if constexpr (is_multiset) curr = curr->right;
            else {
                splay(curr);
                return; // set: 既に存在
            }
        }
        Node* new_node = new Node(value, p);
        if (value < p->value) p->left = new_node;
        else p->right = new_node;
        splay(new_node);
    }
    void erase_node(const T& value) {
        Node* node = find_node(value);
        if (!node) return;
        splay(node);
        Node* l = node->left;
        Node* r = node->right;
        if (l) l->parent = nullptr;
        if (r) r->parent = nullptr;
        delete node;
        root = merge(l, r);
    }
    Node* merge(Node* t1, Node* t2) {
        if (!t1) return t2;
        if (!t2) return t1;
        Node* max_node = t1;
        while (max_node->right) max_node = max_node->right;
        splay(max_node);
        max_node->right = t2;
        if (t2) t2->parent = max_node;
        update(max_node);
        return max_node;
    }
    void in_order(Node* n, std::vector<T>& res) {
        if (!n) return;
        in_order(n->left, res);
        res.push_back(n->value);
        in_order(n->right, res);
    }

    // k番目(0-indexed)のノードを返す
    Node* find_by_index(int k) {
        Node* curr = root;
        while (curr) {
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
        return nullptr;
    }
public:
    SplayTreeValue() = default;
    void insert(const T& value) { insert_node(value); }
    void erase(const T& value) { erase_node(value); }
    bool find(const T& value) {
        Node* n = find_node(value);
        if (n) splay(n);
        return n != nullptr;
    }
    int size() const { return root ? root->size : 0; }
    T lower_bound(const T& value) {
        Node* n = lower_bound_node(value);
        if (!n) throw std::out_of_range("lower_bound not found");
        splay(n);
        return n->value;
    }
    T upper_bound(const T& value) {
        Node* n = upper_bound_node(value);
        if (!n) throw std::out_of_range("upper_bound not found");
        splay(n);
        return n->value;
    }
    std::vector<T> to_vector() {
        std::vector<T> res;
        in_order(root, res);
        return res;
    }

    // --- 追加API ---
    // k番目(0-indexed)の値を取得
    T get_kth(int k) {
        Node* n = find_by_index(k);
        if (!n) throw std::out_of_range("get_kth: index out of range");
        return n->value;
    }
};

void print_vector(const std::vector<int>& vec) {
    for (int x : vec) std::cout << x << " ";
    std::cout << std::endl;
}

int main() {
    SplayTreeValue<int> st;
    st.insert(5);
    st.insert(2);
    st.insert(8);
    st.insert(5);
    std::cout << "After insertions: ";
    print_vector(st.to_vector()); // 2 5 5 8
    st.erase(5);
    std::cout << "After erase(5): ";
    print_vector(st.to_vector()); // 2 5 8
    std::cout << "Find 8: " << st.find(8) << std::endl; // 1
    std::cout << "Find 10: " << st.find(10) << std::endl; // 0
    std::cout << "Lower bound 6: " << st.lower_bound(6) << std::endl; // 8
    std::cout << "Upper bound 5: " << st.upper_bound(5) << std::endl; // 8
    std::cout << "Size: " << st.size() << std::endl;
    std::cout << "k=0: " << st.get_kth(0) << std::endl;
    std::cout << "k=1: " << st.get_kth(1) << std::endl;
    std::cout << "k=2: " << st.get_kth(2) << std::endl;
    return 0;
}
