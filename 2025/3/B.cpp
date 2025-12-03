#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void print_vec(vector<int>& v) {
  for (auto e : v) {
    cout << e << ' ';
  }
  cout << '\n';
}

void solve() {
  int N;
  cin >> N;

  ll ans = 0;

  while (N--) {
    int M = 12;

    string s;
    cin >> s;

    vector<int> ixs(M, 0);
    for (int i = 0; i < M; i++) {
      ixs[M - i - 1] = s.length() - i - 1;
    }

    int l = 0;
    int r = 0;
    print_vec(ixs);
    for (int i = 0; i < M; i++) {
      r = ixs[i];

      int tmp_max = r;
      for (int j = r; j >= l; j--) {
        if (s[tmp_max] <= s[j]) {
          tmp_max = j;
        }
      }

      ixs[i] = tmp_max;
      l = tmp_max + 1;

      print_vec(ixs);
    }

    ll tmp_ans = s[ixs[0]] - 48;
    for (int i = 1; i < M; i++) {
      tmp_ans *= 10;
      tmp_ans += s[ixs[i]] - 48;
    }
    cout << tmp_ans << '\n';
    ans += tmp_ans;
  }

  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("./A.in", "r", stdin);
  solve();
}