#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void solve() {
  int N, Q, ans = 0;
  cin >> N >> Q;

  vector<vector<ll>> v(N, {0, 0});
  for (int i = 0; i < N; i++) {
    cin >> v[i][0] >> v[i][1];
  }

  for (int i = 0; i < Q; i++) {
    ll q;
    cin >> q;

    for (int j = 0; j < N; j++) {
      if (v[j][0] <= q && q <= v[j][1]) {
        printf("%llu - %llu %llu\n", q, v[j][0], v[j][1]);
        ans++;
        break;
      }
    }
  }

  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("./A.in", "r", stdin);
  solve();
}