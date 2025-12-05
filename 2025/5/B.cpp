#include <bits/stdc++.h>

using namespace std;

using ll = unsigned long long;

void solve() {
  int N;
  ll ans = 0;

  cin >> N;

  vector<vector<ll>> v(N, {0, 0});
  for (int i = 0; i < N; i++) {
    cin >> v[i][0] >> v[i][1];
  }

  // for (auto e : v) {
  //   printf("%llu %llu\n", e[0], e[1]);
  // }

  sort(v.begin(), v.end());

  for (auto e : v) {
    printf("%llu %llu\n", e[0], e[1]);
  }

  for (int i = 1; i < v.size(); i++) {
    if (v[i][0] < v[i - 1][0] && v[i][1] > v[i - 1][1]) {
      printf("Error!\n");
      return;
    }
  }

  // 346934484731209
  // 357485433193284
  vector<vector<ll>> w;
  w.push_back(v[0]);

  for (int i = 1; i < v.size(); i++) {
    if (w.back()[1] >= v[i][0]) {
      if (w.back()[1] <= v[i][1]) {
        w.back()[1] = v[i][1];
      }
    } else {
      w.push_back(v[i]);
    }
  }

  // for (auto e : w) {
  //   printf("%llu %llu\n", e[0], e[1]);
  // }

  for (auto e : w) {
    ans = ans + e[1] - e[0] + 1;
    // if (ans < 0) printf("ERROR!");
  }

  for (auto e : w) {
    printf("%llu %llu\n", e[0], e[1]);
  }

  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("./B.in", "r", stdin);
  solve();
}