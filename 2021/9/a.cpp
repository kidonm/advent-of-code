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
  int ans = 0;

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
        // printf("%d %d\n", i, j);
        ans += input[i][j] + 1;
      }
    }
  }

  printf("%d", ans);

  return 0;
}
