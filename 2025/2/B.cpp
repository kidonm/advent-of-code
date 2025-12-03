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
    // cout << l << " " << r << '\n';

    while (l <= r) {
      string s = to_string(l);

      bool same = false;
      for (int i = s.length() / 2; i >= 1; i--) {
        if (s.length() % i != 0) continue;

        bool same_ = true;
        for (int j = 0; j < i; j++) {
          int step = j;
          while (step + i < s.length()) {
            same_ = same_ && s[step] == s[step + i];
            step += i;
          }
        }
        same = same || same_;
      }

      if (same) {
        // printf("l=%llu \n", l);
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