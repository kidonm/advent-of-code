#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct point {
  ll x, y;
};

int get_index(vector<ll>& cs, ll c) {
  return int(lower_bound(cs.begin(), cs.end(), c) - cs.begin());
};

void dfs(vector<vector<char>>& g, int x, int y, int N) {
  if (g[x][y] == '#') return;

  // printf("%d %d\n", x, y);
  // for (int i = 0; i < N; i++) {
  //   for (int j = 0; j < N; j++) {
  //     printf("%c", g[i][j]);
  //   }
  //   printf("\n");
  // }

  g[x][y] = '#';

  dfs(g, x + 1, y, N);
  dfs(g, x - 1, y, N);
  dfs(g, x, y + 1, N);
  dfs(g, x, y - 1, N);
}

void solve() {
  int N;
  cin >> N;
  vector<point> v(N);
  vector<ll> x(N), y(N);

  for (int i = 0; i < N; i++) {
    cin >> v[i].x >> v[i].y;
    x[i] = v[i].x;
    y[i] = v[i].y;
  }

  sort(x.begin(), x.end());
  sort(y.begin(), y.end());

  // compressed space
  vector<vector<char>> grid(N, vector<char>(N, '.'));

  // fill edges
  for (int i = 1; i <= N; i++) {
    int x1 = get_index(x, v[i - 1].x);
    int y1 = get_index(y, v[i - 1].y);

    // % => last to first
    int x2 = get_index(x, v[i % N].x);
    int y2 = get_index(y, v[i % N].y);

    if (x2 == x1) {
      if (y2 < y1) swap(y2, y1);
      for (int j = y1; j <= y2; j++) grid[x1][j] = '#';
    } else {
      if (x2 < x1) swap(x2, x1);
      for (int j = x1; j <= x2; j++) grid[j][y1] = '#';
    }
  }

  // fill area. Point is just a guess
  dfs(grid, N / 2, N / 2 - 1, N);

  // for (int i = 0; i < N; i++) {
  //   for (int j = 0; j < N; j++) {
  //     printf("%c", grid[i][j]);
  //   }
  //   printf("\n");
  // }

  ll ans = 0;
  for (int i = 0; i < N; i++) {
    for (int j = i; j < N; j++) {
      point p = v[i];
      point q = v[j];

      // Unless candidate too small or is crossing any '.'
      if (ans <= (abs(p.x - q.x) + 1) * (abs(p.y - q.y) + 1)) {
        // Candidate rectangle.
        int xa = get_index(x, p.x);
        int xb = get_index(x, q.x);
        if (xa > xb) swap(xa, xb);

        int ya = get_index(y, p.y);
        int yb = get_index(y, q.y);
        if (ya > yb) swap(ya, yb);

        bool test = true;
        for (int ii = xa; ii <= xb && test; ii++) {
          test = test && grid[ii][ya] == '#';
          test = test && grid[ii][yb] == '#';
        }
        for (int ii = ya; ii <= yb && test; ii++) {
          test = test && grid[xa][ii] == '#';
          test = test && grid[xb][ii] == '#';
        }
        if (test) {
          ans = (abs(p.x - q.x) + 1) * (abs(p.y - q.y) + 1);
          // printf("(%lld %lld) (%lld %lld):%lld\n", p.x, p.y, q.x, q.y, ans);
        }
      }
    }
  }

  printf("%lld\n", ans);
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
  cout << "Time taken: " << fixed << time_taken
       << setprecision(9) << " millis" << '\n';
}