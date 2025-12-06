#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void solve() {
  ll ans = 0;
  string line;

  vector<string> s;

  while (getline(cin, line)) {
    line += ' ';
    s.push_back(line);
  }

  int N = s.size() - 1;

  int l = 0;
  int r = 1;

  // while(1): better be safe than sorry
  for (int _x = 0; _x < 10000; _x++) {
    while (r < s[0].length() && (s.back()[r] == ' ')) r++;
    // printf("%d %d\n", l, r);
    ll tmp_segment = s.back()[l] == '*' ? 1 : 0;

    for (int i = l; i < r - 1; i++) {
      ll tmp = 0;
      for (int j = 0; j < N; j++) {
        if (s[j][i] == ' ') continue;
        tmp += s[j][i] - 48;
        tmp *= 10;
      }
      tmp /= 10;
      printf("%lld ", tmp);

      if (s.back()[l] == '*') {
        tmp_segment *= tmp;
      } else {
        tmp_segment += tmp;
      }
    }
    printf("%lld \n", tmp_segment);
    ans += tmp_segment;

    if (r == s[0].length()) break;
    l = r;
    r += 1;
  }

  // for (auto& l : s) {
  //   printf("%s\n", l.c_str());
  // }

  printf("%lld\n", ans);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("./B.in", "r", stdin);
  solve();
}