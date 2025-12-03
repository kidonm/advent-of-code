#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void solve() {
  int N;
  cin >> N;

  ll ans = 0;

  while (N--) {
    string s;
    cin >> s;

    // cout << s << '\n';

    int curmax = 0;
    for (int i = 0; i < s.length(); i++) {
      for (int j = i + 1; j < s.length(); j++) {
        int x = s[i] - 48;
        int y = s[j] - 48;

        curmax = max(x * 10 + y, curmax);
      }
    }

    ans += curmax;
  }

  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("./A.in", "r", stdin);
  solve();
}