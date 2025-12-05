#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void solve() {
  int N, ans = 0;
  cin >> N;

  vector<string> g(N);

  for (int i = 0; i < N; i++) cin >> g[i];

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < g[0].length(); j++) {
      if (g[i][j] == '.') continue;

      vector<vector<int>> dirs = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                                  {0, 1},   {1, -1}, {1, 0},  {1, 1}};

      int neighs = 0;
      for (auto p : dirs) {
        int y = i + p[0];
        int x = j + p[1];

        if (y >= 0 && x >= 0 && y < N && x < g[0].length()) {
          if (g[y][x] == '@' || g[y][x] == '#') neighs++;
        }
      }

      if (neighs < 4) {
        g[i][j] = '#';
        ans++;
      }
    }
  }

  for (auto& s : g) {
    cout << s << '\n';
  }
  cout << '\n';

  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("./A.in", "r", stdin);
  solve();
}