#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

vector<string> split(const string &s, char delimiter) {
  vector<string> res;
  stringstream ss(s);
  string item;

  while (getline(ss, item, delimiter)) {
    if (!item.empty()) {
      res.push_back(item);
    }
  }
  return res;
}
