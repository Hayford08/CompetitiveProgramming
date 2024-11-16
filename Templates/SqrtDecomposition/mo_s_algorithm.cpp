#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

constexpr int DEFAULT_SQRTN = 450; // ~sqrt(2e5)
struct Query {
  int l, r, idx, sqrtN; 
  Query() {}
  Query(int l, int r, int idx, int sqrtN = DEFAULT_SQRTN) : l(l), r(r), idx(idx), sqrtN(sqrtN) {}

  bool operator<(const Query &other) const {
    return make_pair(l / sqrtN, r) < make_pair(other.l / sqrtN, other.r);
  }
};

struct Mo {
  int cur_l, cur_r, odd_cnt;
  vector<int> mp, arr;

  Mo(const vector<int> &inp){
    // coordinate compression
    vector<int> sorted(inp);
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    this->arr = inp;
    int n = arr.size();
    for (int i = 0; i < n; i++) {
      arr[i] = lower_bound(sorted.begin(), sorted.end(), arr[i]) - sorted.begin();
    }
    int mx = sorted.size();
    mp.assign(mx, 0);
    cur_l = 0, cur_r = -1;
    odd_cnt = 0;
  }

  inline void add(int idx) {
    int x = arr[idx];
    mp[x]++;
    if (mp[x] & 1) {
      odd_cnt++;
    } else {
      odd_cnt--;
    }
  }

  inline void remove(int idx) {
    int x = arr[idx];
    mp[x]--;
    if (mp[x] & 1) {
      odd_cnt++;
    } else {
      odd_cnt--;
    }
  }
  
  inline int get_answer() {
    return odd_cnt;
  }

  /**
   * @brief Preprocess the queries and return the answers.
   *        Expected to be called only once. Expects the 
   *        ranges to be 0-indexed.
   * 
   * @param queries 
   * @return vector<int> 
   */
  inline vector<int> process(vector<Query> &queries) {
    sort(queries.begin(), queries.end());
    vector<int> ans(queries.size());

    for (const Query &q : queries) {
      int idx = q.idx, l = q.l, r = q.r;
      while (cur_l > l) {
        cur_l--;
        add(cur_l);
      }
      while (cur_r < r) {
        cur_r++;
        add(cur_r);
      }
      while (cur_l < l) {
        remove(cur_l);
        cur_l++;
      }
      while (cur_r > r) {
        remove(cur_r);
        cur_r--;
      }
      ans[idx] = get_answer();
    }
    return ans;
  }
};

