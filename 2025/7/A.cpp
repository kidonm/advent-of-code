#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void solve() {
  int N, S;
  ll ans = 0;

  cin >> N >> S;

  vector<string> v(N);
  for (int i = 0; i < N; i++) {
    cin >> v[i];
  }

  // for (auto& e : v) {
  //   cout << e << '\n';
  // }

  // vector<vector<int>> visited(N, vector<int>(v[0].size(), 0));

  queue<vector<int>> q;
  q.push({0, S});

  while (!q.empty()) {
    // for (auto& e : q) printf("(%d %d) ", e[0], e[1]);
    // printf("\n");

    auto vv = q.front();
    q.pop();

    // printf("%d %d\n", vv[0], vv[1]);

    while (v[vv[0]][vv[1]] != '^' && v[vv[0]][vv[1]] != '|') {
      v[vv[0]][vv[1]] = '|';
      if (vv[0] + 1 == (int)v.size()) break;
      vv[0]++;
    }

    if (v[vv[0]][vv[1]] != '^') continue;

    if (vv[0] + 1 != (int)v.size()) {
      if (vv[1] - 1 >= 0) q.push({vv[0], vv[1] - 1});
      if (vv[1] + 1 < v[0].size()) q.push({vv[0], vv[1] + 1});
    }
  }

  // for (auto& e : v) {
  //   cout << e << '\n';
  // }

  for (int i = 1; i < N; i++) {
    for (int j = 0; j < v[0].size(); j++) {
      if (v[i][j] == '^' && v[i - 1][j] == '|') ans++;
    }
  }

  printf("%lld\n", ans);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("./A.in", "r", stdin);
  solve();
}