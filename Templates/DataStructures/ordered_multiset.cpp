#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename T>
struct OrderedMultiset {
  using pti = pair<T, int>;
  typedef tree<pti, null_type, less<pti>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
  // X.find_by_order(k) return kth element. 0 indexed.
  // X.order_of_key(k) returns count of elements strictly less than k.

  int id = 0;
  ordered_set st;
  OrderedMultiset() : id(0) {}

  inline void insert(T x) {
    st.insert({x, id++});
  }

  inline bool erase(T x) {
    auto it = st.lower_bound({x, 0});
    if (it == st.end() || it->first != x) {
      return false;
    }
    st.erase(it);
    return true;
  }

  inline T get(int index) {
    if (index < 0 || index >= (int)st.size()) {
      throw out_of_range("Index out of range");
    }
    return st.find_by_order(index)->first;
  }

  inline T getKth(int k) {
    return get(k - 1);
  }

  inline int count(T x) {
    return st.order_of_key({x, id}) - st.order_of_key({x, 0});
  }

  inline int countLessThan(T x) {
    return st.order_of_key({x, 0});
  }

  inline int countLessThanOrEqual(const T& x) {
    return st.order_of_key({x, id});
  }

  inline int size() {
    return st.size();
  }

  inline bool empty() {
    return st.empty();
  }
};