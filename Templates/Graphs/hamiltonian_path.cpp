#include <iostream>
#include <vector>

using namespace std;
const int MAXN = 20;

bool check(int adj[][MAXN], int n){
  bool dp[MAXN][1 << MAXN]={0};
  for(int i = 0; i < n; i++){
    dp[i][1 << i] = true;
  }

  for(int mask = 0; mask < (1 << n); mask++){
    for(int j = 0; j < n; j++){
      if(mask & (1 << j)){
        int pmask = mask ^ (1 << j);
        for(int k = 0; k < n; k++){
          if(mask & (1 << k) && adj[k][j] && k != j && dp[k][pmask]){
              dp[j][mask] = true;
              break;
          }
        }     
      }
    }
  }
  for(int i = 0; i < n; i++)
      if(dp[i][(1 << n) - 1])
          return true;
  return false;
}

/*
Minimum weight Hamiltonian path 
e.g. Elongated Matrix

const int MX = 18;
const int INF = 1e12;
 
vector<int> arr[MX];
int n, m;
int dp[MX][1 << MX];
int mn1[MX][MX], mn2[MX][MX];
 
int calc(int mask, int u){
  int res = dp[u][mask];
  if (res != -1){
    return res;
  }
  res = dp[u][mask] = 0;
  for (int v = 0; v < n; v++){
    if (v != u && (mask & (1 << v))){
      res = max(res, min(mn1[v][u], calc(mask ^ (1 << u), v)));
    }
  }
  return dp[u][mask] = res;
}
 
int solve(){
  cin >> n >> m;
  for (int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
      int x; 
      cin >> x;
      arr[i].push_back(x);
    }
  }
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      int mn = INF;
      for (int k = 0; k < m; k++){
        mn = min(mn, abs(arr[i][k] - arr[j][k]));
      }
      mn1[i][j] = mn;
      mn = INF;
      for (int k = 0; k < m - 1; k++){
        mn = min(mn, abs(arr[i][k] - arr[j][k + 1]));
      }
      mn2[i][j] = mn;
    }
  }
  int ans = 0;
  int lim = 1 << n;
  for (int u = 0; u < n; u++){
    memset(dp, -1, sizeof(dp));
    for (int j = 0; j < n; j++){
      dp[j][1 << j] = (j == u ? INF : 0);
    }
    for (int j = 0; j < n; j++){
      ans = max(ans, min(mn2[j][u], calc(lim - 1, j)));
    }
  }
  cout << ans << "\n";
  return 0;
}
*/