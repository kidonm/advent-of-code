#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

vector<pair<int, int>> poss = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int dfs(int i, int j, vector<vector<int>> &input, vector<vector<bool>> &visited,
        vector<pair<int, int>> &visited2) {
  int m = visited.size();
  int n = visited[0].size();
  if (!(i >= 0 && i < m && j >= 0 && j < n) || visited[i][j] ||
      input[i][j] == 9)
    return 0;

  visited[i][j] = true;
  visited2.push_back({i, j});
  int sum = 0;
  for (pair<int, int> p : poss) {
    int dx = p.first;
    int dy = p.second;

    sum += dfs(i + dx, j + dy, input, visited, visited2);
  }

  return 1 + sum;
}

int main() {
  string s;
  vector<vector<int>> input;

  while (getline(cin, s)) {
    vector<int> tmp;
    for (char c : s) {
      tmp.push_back(c - 48);
    }
    input.push_back(tmp);
  }

  int m = input.size();
  int n = input[0].size();

  vector<vector<bool>> visited(m, vector<bool>(n, false));
  vector<pair<int, int>> lows;

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      int low = true;
      for (pair<int, int> p : poss) {
        int dx = p.first;
        int dy = p.second;

        if (i + dx >= 0 && i + dx < m && j + dy >= 0 && j + dy < n) {
          // if (i == 0 && j == 1) {
          //   printf("y: %d, x: %d\n", i + dx, j + dy);
          // }
          low = low && input[i][j] < input[i + dx][j + dy];
        }
      }

      if (low) {
        lows.push_back({i, j});
      }
    }
  }

  vector<pair<int, vector<pair<int, int>>>> anss;
  for (pair<int, int> low : lows) {
    int i = low.first;
    int j = low.second;
    vector<pair<int, int>> visited2;

    int weight = dfs(i, j, input, visited, visited2);

    anss.push_back({weight, visited2});
  }

  vector<vector<int>> print(m, vector<int>(n, 0));

  sort(anss.begin(), anss.end(),
       [](const pair<int, vector<pair<int, int>>> &a,
          const pair<int, vector<pair<int, int>>> &b) -> bool {
         return a.first < b.first;
       });

  for (int i = 0; i < anss.size(); i++) {
    for (pair<int, int> p : anss[i].second) {
      print[p.first][p.second] = i;
    }
  }

  // sort(anss.begin(), anss.end());

  printf("P2\n");
  printf("%d %d\n", m, n);
  printf("%d\n", anss.size() - 1);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", print[i][j]);
    }
    printf("\n");
  }

  // printf("%d", anss[lows.size() - 1].first * anss[lows.size() - 2].first *
  //                  anss[lows.size() - 3].first);

  return 0;
}
