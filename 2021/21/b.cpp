#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef long long ull;
typedef pair<int, int> ipair;
typedef vector<int> coord;

vector<vector<int>> dies = {
    {1, 1, 1}, {1, 1, 2}, {1, 1, 3}, {1, 2, 1}, {1, 2, 2}, {1, 2, 3}, {1, 3, 1},
    {1, 3, 2}, {1, 3, 3}, {2, 1, 1}, {2, 1, 2}, {2, 1, 3}, {2, 2, 1}, {2, 2, 2},
    {2, 2, 3}, {2, 3, 1}, {2, 3, 2}, {2, 3, 3}, {3, 1, 1}, {3, 1, 2}, {3, 1, 3},
    {3, 2, 1}, {3, 2, 2}, {3, 2, 3}, {3, 3, 1}, {3, 3, 2}, {3, 3, 3},
};

int target = 21;

pair<int, int> move(int i, int j, int k, int pos, int sum) {
  int newpos = (pos + i + j + k) % 10;
  int newsum = sum + newpos + 1;
  return {newpos, newsum};
}

vector<ull> dfs(int player, int a, int sa, int b, int sb,
                vector<vector<vector<vector<vector<vector<ull>>>>>> &dp) {
  if (dp[player][a][sa][b][sb].size() > 0) return dp[player][a][sa][b][sb];

  if (sa >= target)
    return {1, 0};
  else if (sb >= target)
    return {0, 1};

  vector<ull> wins = {0, 0};

  for (auto &roll : dies) {
    vector<ull> newwins;
    if (player == 0) {
      auto next = move(roll[0], roll[1], roll[2], a, sa);
      newwins = dfs(1, next.first, next.second, b, sb, dp);
    } else {
      auto next = move(roll[0], roll[1], roll[2], b, sb);
      newwins = dfs(0, a, sa, next.first, next.second, dp);
    }
    wins[0] += newwins[0];
    wins[1] += newwins[1];
  }

  dp[player][a][sa][b][sb] = wins;

  return wins;
}

int main() {
  int a = 3;
  int b = 6;
  int sumA = 0;
  int sumB = 0;

  vector<vector<vector<vector<vector<vector<ull>>>>>> dp(
      2,  ////////////////////////////////////////////////////////////////////////////////
      vector<vector<vector<vector<vector<ull>>>>>(
          11,  ///////////////////////////////////////////////////////////////////////////
          vector<vector<vector<vector<ull>>>>(
              35,  ///////////////////////////////////////////////////////////////////////////
              vector<vector<vector<ull>>>(
                  11,  ///////////////////////////////////////////////////////////////////////////
                  vector<vector<ull>>(
                      35)  /////////////////////////////////////////////////////////
                  ))));

  vector<ull> ans = dfs(0, a, sumA, b, sumB, dp);

  printf("ans: %llu %llu\n", ans[0], ans[1]);

  return 0;
}