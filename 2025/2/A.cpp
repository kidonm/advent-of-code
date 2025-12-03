#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int is_same_(int number) {
  int digit = number % 10;

  // cout << digit << '\n';
  number /= 10;
  while (number > 0) {
    // cout << number << '\n';
    if (number % 10 != digit) return false;
    number /= 10;
  }

  return true;
}

int all_digits_number(int digit, int order) {
  int ans = digit;

  order--;
  while (order--) {
    ans *= 10;
    ans += digit;
  }

  return ans;
}

void solve() {
  // cout << is_same_(3334) << '\n';
  // return;

  ll N, ans = 0;
  cin >> N;

  while (N--) {
    ll l, r;

    cin >> l >> r;
    cout << l << " " << r << '\n';

    while (l <= r) {
      string s = to_string(l);
      if (s.length() % 2 == 1) {
        l++;
        continue;
      }

      bool same = true;
      for (ll i = 0; i < s.length() / 2; i++) {
        same = same && s[i] == s[s.length() / 2 + i];
      }
      if (same) {
        // cout << l << '\n';
        ans += l;
      }
      l++;
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