#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll dfs(vector<string>& v, vector<vector<ll>>& dp, int y, int x) {
  ll ans = 0;
  while (v[y][x] != '^') {
    v[y][x] = '|';
    if (y + 1 == (int)v.size()) break;
    y++;
  }

  if (v[y][x] == '^') {
    if (dp[y][x] != -1) {
      return dp[y][x];
    }
  } else
    return 1;

  if (x - 1 >= 0) ans += dfs(v, dp, y, x - 1);
  if (x + 1 < (int)v[0].size()) ans += dfs(v, dp, y, x + 1);

  dp[y][x] = ans;

  return ans;
}

void solve() {
  int N, X;
  ll ans = 0;

  cin >> N >> X;

  vector<string> v(N);
  for (int i = 0; i < N; i++) {
    cin >> v[i];
  }

  vector<vector<ll>> dp(N, vector<ll>(v[0].size(), -1));

  ans = dfs(v, dp, 0, X);

  for (auto& s : v) {
    cout << s << '\n';
  }

  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("./A.in", "r", stdin);
  solve();
}