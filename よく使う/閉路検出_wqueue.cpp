#include <bits/stdc++.h> 
using namespace std; 

// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/%E9%96%89%E8%B7%AF%E6%A4%9C%E5%87%BA_wqueue.cpp
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);                 

    int n;
    long long k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i < n; ++i) {
        a[i]--; // 0-indexedに調整
    }
    queue<int> path_q;           // たどったパスを格納するキュー
    int current_node = 0;        // 現在位置のノード、0からスタート
    vector<bool> visited(n, false); // 各ノードの訪問状態

    while (!visited[current_node]) {
        path_q.push(current_node);
        visited[current_node] = true;
        current_node = a[current_node]; // 次のノードへ
    }

    while (path_q.front() != current_node && k > 0) {
        path_q.pop();
        k--;
    }
    k %= path_q.size(); 
    
    while (k--) { 
        path_q.pop();
    }

    cout << path_q.front() + 1 << endl;

    return 0;
}