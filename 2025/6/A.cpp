#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void solve() {
  int N;
  int M;
  ll ans = 0;

  cin >> N >> M;

  vector<vector<ll>> v(N, vector<ll>(M, 0));
  vector<char> o(M);

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> v[i][j];
    }
  }
  for (int i = 0; i < M; i++) {
    cin >> o[i];
  }

  for (auto& r : v) {
    for (auto c : r) {
      printf("%llu ", c);
    }
    printf("\n");
  }

  // for (auto e : o) {
  //   printf("%c ", e);
  // }
  // printf("\n");

  for (int i = 0; i < M; i++) {
    ll tmp;
    tmp = o[i] == '*' ? 1 : 0;
    for (int j = 0; j < N; j++) {
      if (o[i] == '*') {
        tmp *= v[j][i];
      } else {
        tmp += v[j][i];
      }
    }
    ans += tmp;
    printf("%llu\n", tmp);
  }

  printf("%lld\n", ans);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("./A.in", "r", stdin);
  solve();
}