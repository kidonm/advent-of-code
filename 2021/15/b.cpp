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

typedef unsigned long long ull;
typedef pair<int, int> iPair;

vector<iPair> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int mann(int i, int j, int m, int n) { return abs(m - i) + abs(n - j); }

int main() {
  char c;
  int tiles = 5;
  vector<vector<int>> mat;

  for (string s; getline(cin, s);) {
    stringstream ss(s);
    vector<int> tmp;

    for (char c; ss >> c;) {
      tmp.push_back(c - 48);
    }

    mat.push_back(tmp);
  }

  int m = mat.size();
  int n = mat[0].size();

  for (int t = 1; t < tiles; t++) {
    for (int i = 0; i < m; i++) {
      vector<int> tmp;
      for (int j = 0; j < n; j++) {
        int num = mat[i][j] + t;
        if (num > 9) num = num % 10 + 1;
        tmp.push_back(num);
      }
      mat.push_back(tmp);
    }
  }

  m = mat.size();

  for (int t = 1; t < tiles; t++) {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        int num = mat[i][j] + t;
        if (num > 9) num = num % 10 + 1;
        mat[i].push_back(num);
      }
    }
  }

  n = mat[0].size();

  priority_queue<pair<int, iPair>, vector<pair<int, iPair>>,
                 greater<pair<int, iPair>>>
      pq;
  vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
  vector<vector<int>> vis(m, vector<int>(n, 0));

  pq.push({0, {0, 0}});
  dist[0][0] = 0;

  int visited = 0;

  while (!pq.empty()) {
    iPair v = pq.top().second;
    pq.pop();
    int i = v.first;
    int j = v.second;

    visited++;

    if (i == m - 1 && j == n - 1) {
      printf("found\n");
      break;
    }

    vis[i][j] = visited;

    for (iPair delta : dirs) {
      int dx = delta.first;
      int dy = delta.second;

      // printf("%d %d \n", i + dx, j + dy);

      if (i + dx >= 0 && i + dx < m && j + dy >= 0 && j + dy < n) {
        int weight = mat[i + dx][j + dy];

        if (vis[i + dx][j + dy] > 0) continue;

        if (dist[i + dx][j + dy] > dist[i][j] + weight) {
          dist[i + dx][j + dy] = dist[i][j] + weight;
          int h = dist[i + dx][j + dy] + mann(i + dx, j + dy, m, n) / 10;
          pq.push({h, {i + dx, j + dy}});
          // pq.push({dist[i + dx][j + dy], {i + dx, j + dy}});
        }
      }
    }
  }

  // for (int i = 0; i < m; i++) {
  //   for (int j = 0; j < n; j++) {
  //     printf("%d ", dist[i][j]);
  //   }
  //   printf("\n");
  // }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      if (vis[i][j] < 10) printf(" ");
      if (vis[i][j] < 100) printf(" ");
      printf("%d ", vis[i][j]);
    }
    printf("\n");
  }

  printf("%d %d", visited, dist[m - 1][n - 1]);

  return 0;
}
