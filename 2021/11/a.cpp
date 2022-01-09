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

void print(vector<vector<int>> &input, int m, int n) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d", input[i][j]);
    }
    printf("\n");
  }
}

vector<pair<int, int>> dirs = {{0, 1}, {1, 0},  {0, -1}, {-1, 0},
                               {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

int flash(int i, int j, vector<vector<int>> &input, int m, int n) {
  int ans;

  if (input[i][j] == 0) {
    ans = 0;
  } else if (input[i][j] > 9) {
    input[i][j] = 0;
    int sum = 0;

    for (pair<int, int> dir : dirs) {
      int dy = dir.first;
      int dx = dir.second;

      if (i + dy >= 0 && i + dy < m && j + dx >= 0 && j + dx < n) {
        sum += flash(i + dy, j + dx, input, m, n);
      }
    }

    ans = 1 + sum;
  } else {
    input[i][j]++;
    if (input[i][j] > 9) {
      ans = flash(i, j, input, m, n);
    } else {
      ans = 0;
    }
  }

  return ans;
}

int main() {
  string s;
  int ans = 0;

  vector<vector<int>> input;

  while (getline(cin, s)) {
    stringstream ss(s);
    vector<int> tmp;
    for (char c; ss >> c;) {
      int i = c - 48;
      tmp.push_back(i);
    }
    input.push_back(tmp);
  }

  int m = input.size();
  int n = input[0].size();

  for (int g = 0; g < 100; g++) {
    printf("g: %d ans: %d\n", g, ans);
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        input[i][j]++;
      }
    }

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (input[i][j] > 9) ans += flash(i, j, input, m, n);
      }
    }

    // print(input, m, n);
  }

  printf("%d\n", ans);

  return 0;
}
