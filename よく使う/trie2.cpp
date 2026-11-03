// AtCoder reference URL: https://github.com/kazuma-zensoku/atcoder-library-kuruma/blob/main/%E3%82%88%E3%81%8F%E4%BD%BF%E3%81%86/trie2.cpp
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;
using ll = long long;

// Trieという「デカ型」の設計図
struct Trie {
    // === メンバー変数 (Trieの内部データ) ===

    // to: 遷移テーブル。Node IDから(文字, 次のNode ID)へのmapのvector。
    // vector<map<char, int>>は、静的Trieと動的Trieのハイブリッド実装。
    vector<map<char, int>> to;

    // size: 各ノードを接頭辞の終端とする文字列の数を記録する。
    // 問題に応じてここをカスタマイズする。(例: is_endフラグのvectorなど)
    vector<ll> count;

    // === メンバー関数 (Trieの振る舞い) ===

    // コンストラクタ: 「誕生の儀式」
    // オブジェクトが作られた瞬間に呼ばれる。
    Trie() {
        //最初にrootノード(ID=0)だけを作成しておく。
        to.emplace_back();
        count.emplace_back(0);
    }

    // 文字列sを追加する関数
    void add(const string& s) {
        int current_node_id = 0; // 常にroot(ID=0)からスタート
        
        // 文字列を一文字ずつたどり、道を伸ばしていく
        for (char c : s) {
            // 今いるノードから、文字cへの道が存在するかチェック
            if (to[current_node_id].count(c) == 0) {
                // 道が存在しない場合、新しいノードを作成する
                int new_node_id = to.size(); // 新しいノードのIDは、現在のノード数

                // 今いるノードの案内板に、新しい道と行き先(ID)を書き込む
                to[current_node_id][c] = new_node_id;

                // ノード置き場(vector)の末尾に、新しいノードの器を追加
                to.emplace_back(map<char, int>());
                count.emplace_back(0);
            }
            
            // 次のノードへ移動
            current_node_id = to[current_node_id][c];
        }
        // 文字列の終端にあたるノードのカウンターを増やす
        count[current_node_id]++;
    }

    // 文字列sがいくつ存在するか検索する関数
    ll search(const string& s) {
        int current_node_id = 0;
        for (char c : s) {
            // 道をたどる途中で行き止まりになったら、その文字列は存在しない
            if (to[current_node_id].count(c) == 0) {
                return 0;
            }
            current_node_id = to[current_node_id][c];
        }
        return count[current_node_id];
    }
};


int main() {
    // Trieという「デカ変数」を作成
    Trie trie;

    trie.add("apple");
    trie.add("apple");
    trie.add("apply");
    trie.add("apricot");
    trie.add("ape");

    cout << "Count of 'apple': " << trie.search("apple") << endl;     // 2
    cout << "Count of 'apply': " << trie.search("apply") << endl;     // 1
    cout << "Count of 'apollo': " << trie.search("apollo") << endl;   // 0
    
    return 0;
}