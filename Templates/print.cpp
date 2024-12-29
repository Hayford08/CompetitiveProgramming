#include <iostream>
using namespace std;

template <typename T>
inline void pout(const T& value) {
  std::cout << value << "\n";
}

template <typename T1, typename T2>
inline void print(const std::pair<T1, T2>& p) {
  std::cout << p.first << " " << p.second << "\n";
}

template<class T>
inline void print(vector<T> &v){
  for (auto &x : v){
    cout << x << " ";
  }
  cout << "\n";
}

template <typename T1, typename T2>
inline void print(const std::vector<std::pair<T1, T2>>& vec) {
  for (const auto& p : vec) {
    pout(p);
  }
  std::cout << "\n";
}