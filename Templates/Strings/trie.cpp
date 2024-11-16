#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/* FOR LOWERCASE STRINGS
struct Trie {
    int SZ = 26;
    bool is_word;
    Trie* children[26];

    Trie(): is_word(false) {
        for (int i = 0; i < SZ; i++){
            children[i] = nullptr;
        }
    }

    void insert(string &word){
        Trie* curr = this;
        for (char c : word){
            int pos = c - 'a';
            if (!curr->children[pos]) {
                curr->children[pos] = new Trie();
            }
            curr = curr->children[pos];
        }
        curr->is_word = true;
    }

    void insert(vector<string> &words){
        for (auto &word : words) {
            Trie* curr = this;
            for (char c : word){
                int pos = c - 'a';
                if (!curr->children[pos]) {
                    curr->children[pos] = new Trie();
                }
                curr = curr->children[pos];
            }
            curr->is_word = true;
        }
    }

    bool search(string &word){
        Trie* curr = this;
        for (char c : word){
            int pos = c - 'a';
            if (!curr->children[pos]){
                return false;
            }
            curr = curr->children[pos];
        }
        return curr->is_word;
    }

    void delete_node(Trie* node){
        if (!node){
            return;
        }
        for (int i = 0; i < SZ; i++){
            delete_node(node->children[i]);
        }
        delete node;
    }

    ~Trie() {
        delete_node(this);
    }
};

*/

class TrieNode {
public:
    unordered_map<int, TrieNode*> children;
    int cnt;

    TrieNode() : cnt(0) {}
};

class Trie {
private:
    TrieNode* root;

    void clearTrie(TrieNode* node) {
        if (!node){
            return;
        }
        for (auto it : node->children) {
            clearTrie(it.second);
        }
        delete node;
    }

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        clearTrie(root);
    }
    const int A = 26;
    void insert(const string& s) {
        TrieNode* curr = root;
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            int p = (s[i] - 'a') * A + (s[n - i - 1] - 'a');
            if (curr->children.find(p) == curr->children.end()) {
                curr->children[p] = new TrieNode();
            }
            curr = curr->children[p];
        }
        curr->cnt += 1;
    }

    int get_count(const string& s) {
        TrieNode* curr = root;
        int n = s.size();
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int p = (s[i] - 'a') * A + (s[n - i - 1] - 'a');
            if (curr->children.find(p) == curr->children.end()) {
                break;
            }
            curr = curr->children[p];
            ans += curr->cnt;
        }
        return ans;
    }
};