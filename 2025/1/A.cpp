#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void solve() {
  string s;

  ll pos = 50;
  ll ans = 0;

  while (getline(cin, s)) {
    stringstream ss(s);

    char d;
    long long c;
    ss >> d >> c;

    ans += c / 100;
    c = c % 100;

    if ((d == 'L' && pos != 0 && (pos - c) <= 0) ||
        (d == 'R' && pos != 0 && (pos + c) >= 100)) {
      cout << "1 ";
      ans += 1;
    }

    if (d == 'L') {
      c = 100 - c;
    }
    ll new_pos = pos + c;
    new_pos = new_pos % 100;

    pos = new_pos;

    // if (pos == 0) ans += 1;

    cout << s << " " << pos << '\n';
  }

  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("./a.in", "r", stdin);
  solve();
}