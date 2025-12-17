#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct point {
  ll x;
  ll y;
};

void solve() {
  int N;
  cin >> N;
  vector<point> v(N);
  for (int i = 0; i < N; i++) cin >> v[i].x >> v[i].y;

  ll maxa = 0;

  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      maxa = max(maxa, (abs(v[i].x - v[j].x) + 1) * (abs(v[i].y - v[j].y) + 1));
    }
  }

  cout << maxa << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("./A.in", "r", stdin);
  auto start = chrono::high_resolution_clock::now();
  solve();
  auto end = chrono::high_resolution_clock::now();
  double time_taken =
      chrono::duration_cast<chrono::nanoseconds>(end - start).count();
  time_taken *= 1e-6;
  cout << "Time taken: " << fixed << time_taken << setprecision(9) << " millis"
       << '\n';
}