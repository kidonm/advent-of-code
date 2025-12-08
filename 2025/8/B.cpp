#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
  ll x, y, z;
};

void pp(Point p) { printf("(%lld %lld %lld) ", p.x, p.y, p.z); }

int get_root(int p, vector<int>& par) {
  int root = p;
  while (par[root] != root) {
    root = par[root];
  }
  // Path compression
  while (par[p] != root) {
    int next = par[p];
    par[p] = root;
    p = next;
  }
  return root;
}

void solve() {
  int N;
  cin >> N;

  vector<Point> v(N);
  for (int i = 0; i < N; i++) {
    cin >> v[i].x >> v[i].y >> v[i].z;
  }

  vector<tuple<int, int, ll>> d;
  d.reserve(N * (N - 1) / 2);

  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      ll dx = v[i].x - v[j].x;
      ll dy = v[i].y - v[j].y;
      ll dz = v[i].z - v[j].z;
      ll dist_sq = dx * dx + dy * dy + dz * dz;

      d.push_back({i, j, dist_sq});
    }
  }

  sort(d.begin(), d.end(),
       [](const auto& l, const auto& r) { return get<2>(l) < get<2>(r); });

  vector<int> par(N);
  iota(par.begin(), par.end(), 0);
  vector<int> size(N, 1);

  int c = N;
  for (auto& [i, j, dist_sq] : d) {
    int pi = get_root(i, par);
    int pj = get_root(j, par);

    if (pi == pj) continue;

    if (size[pi] < size[pj]) swap(pi, pj);
    par[pj] = pi;
    size[pi] += size[pj];

    if (--c == 1) {
      printf("%lld\n", v[i].x * v[j].x);
      break;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("./B.in", "r", stdin);
  auto start = chrono::high_resolution_clock::now();
  solve();
  auto end = chrono::high_resolution_clock::now();
  double time_taken =
      chrono::duration_cast<chrono::nanoseconds>(end - start).count();
  time_taken *= 1e-6;
  cout << "Time taken by program is : " << fixed << time_taken
       << setprecision(9) << " millis" << '\n';
}