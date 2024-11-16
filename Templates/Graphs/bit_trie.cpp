#include <iostream>
#include <vector>

using namespace std;

struct Trie{
    static constexpr int MX = 1 << 20;
    Trie* children[2] = {};

    void insert(int num) {
        Trie *curr = this;
        for (int b = MX; b > 0; b >>= 1) {
            int bit = (num & b) > 0;
            if (curr->children[bit] == nullptr){
                curr->children[bit] = new Trie();
            }
            curr = curr->children[bit];
        }
    }

    bool remove(int num, int b = MX) {
        if (b == 0){
            return true;
        }
        int bit = (num & b) > 0;
        if (children[bit] != nullptr && children[bit]->remove(num, b >> 1)) {
            delete children[bit];
            children[bit] = nullptr;
        }
        return children[0] == children[1];
    }

    int query(int num) {
        int res = 0;
        Trie *curr = this;
        for (int b = MX; b > 0; b >>= 1) {
            int bit = (num & b) > 0;
            if (curr->children[bit ^ 1] != nullptr) {
                res |= b;
                curr = curr->children[!bit];
            }
            else {
                curr = curr->children[bit];
            }
        }
        return res;
    }
};


class Solution {
public:
    int maximumStrongPairXor(vector<int>& nums) {
        Trie trie;
        sort(nums.begin(), nums.end());
        int ans = 0;
        for (int n = nums.size(), l = 0, r = 0; r < n; r++){
            trie.insert(nums[r]);
            while (nums[l] * 2 < nums[r]){
                trie.remove(nums[l++]);
            }
            ans = max(ans, trie.query(nums[r]));
        }
        return ans;
    }
};