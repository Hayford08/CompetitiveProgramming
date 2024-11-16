#include <iostream>
#include <vector>
#include <set>
using namespace std;

using point = pair<int, int>;

struct Polyminoes {
  vector<int> counts;
  vector<set<point>> poly;
  bool processed;
  int p;

  Polyminoes(int _p) : counts(_p + 1), poly({}), processed(false), p(_p) {
    counts[0] = 1;
  }

  vector<int> get_counts() {
    if (!processed) {
      set<point> polyomino;
      set<point> untried_set = {{0, 0}};
      redelmeier(polyomino, untried_set);
      processed = true;
    }
    return counts;
  }

  vector<set<point>> get_poly() {
    if (!processed) {
      set<point> polyomino;
      set<point> untried_set = {{0, 0}};
      redelmeier(polyomino, untried_set);
      processed = true;
    }
    return poly;
  }

  set<point> get_neighbors(set<point> &polyomino) {
    set<point> res;
    const int dx[4] = {0, 0, -1, 1};
    const int dy[4] = {1, -1, 0, 0};

    for (auto &[x, y] : polyomino) {
      for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (ny < 0 || (ny == 0 && nx < 0)){
          continue;
        } 
        res.insert({nx, ny});
      }
    }
    return res;
  }

  void redelmeier(set<point> &polyomino, set<point> &untried_set) {
    while (untried_set.size()) {
      auto new_cell = *untried_set.begin();
      untried_set.erase(untried_set.begin());

      set<point> new_polyomino(polyomino.begin(), polyomino.end());
      new_polyomino.insert(new_cell);
      int cnt = new_polyomino.size();
      counts[cnt]++;

      if (cnt == p) {
        poly.push_back(new_polyomino);
      }

      if (cnt < p) {
        set<point> new_untried_set(untried_set.begin(), untried_set.end());
        auto polyomino_neighbors = get_neighbors(polyomino);
        set<point> tmp = {new_cell};

        for (auto &npoint : get_neighbors(tmp)) {
          if (polyomino_neighbors.count(npoint) || polyomino.count(npoint)) {
            continue;
          }
          new_untried_set.insert(npoint);
        }
        redelmeier(new_polyomino, new_untried_set);
      }
    }
  }

  point get_dimension(set<point> &polyomino) {
    int mnx = 1e9, mxx = -1e9;
    int mny = 1e9, mxy = -1e9;

    for (auto &[x, y] : polyomino) {
      mnx = min(x, mnx);
      mxx = max(x, mxx);
      mny = min(y, mny);
      mxy = max(y, mxy);
    }
    return {mxx - mnx + 1, mxy - mny + 1};
  }
};



int main() {
  Polyminoes P(3);

  for (auto &x : P.get_counts()) {
    cout << x << " ";
  }
  cout << "\n";

  for (auto &poly : P.get_poly()) {
    cout << "{";
    for (auto &[x, y] : poly) {
      cout << "(" << x << "," << y << ") "; 
    }
    cout << "}\n";
    
  }
  cout << "\n";
}
