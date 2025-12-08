#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using point = vector<float>;

int dfs(map<point, set<point>>& adj, set<point>& vis, const point& e) {
  if (vis.count(e) > 0) return 1;
  vis.insert(e);
  // printf("(%.0f %.0f %.0f) ", e[0], e[1], e[2]);
  int ans = 1;

  for (auto& n : adj[e]) {
    if (vis.count(n) > 0) continue;
    ans += dfs(adj, vis, n);
  }

  return ans;
}

void solve() {
  int N, Q;
  cin >> N >> Q;

  vector<point> v(N, point(3, 0));
  for (int i = 0; i < N; i++) {
    cin >> v[i][0] >> v[i][1] >> v[i][2];
  }

  map<point, map<point, float>> w;
  for (auto& v1 : v) w.insert({v1, {}});

  for (auto& e1 : v) {
    for (auto& e2 : v) {
      if (e1 == e2) continue;
      if (w[e2].count(e1) > 0) continue;

      float d = sqrt(pow(e1[0] - e2[0], 2) + pow(e1[1] - e2[1], 2) +
                     pow(e1[2] - e2[2], 2));
      w[e1][e2] = d;
    }
  }

  // for (auto e : w) {
  //   printf("(%.0f %.0f %.0f): ", e.first[0], e.first[1], e.first[2]);
  //   for (auto f : e.second) {
  //     printf("(%.0f %.0f %.0f)[%.2f] ", f.first[0], f.first[1], f.first[2],
  //            f.second);
  //   }
  //   printf("\n");
  // }

  vector<tuple<point, point, float>> q;

  // assert(w.size() > 0);
  for (auto& e : w) {
    // assert(e.second.size() > 0);
    for (auto& f : e.second) {
      // printf("(%.0f %.0f %.0f)->(%.0f %.0f %.0f)[%0.0f]\n", a[0], a[1], a[2],
      //        b[0], b[1], b[2], w);
      q.push_back({e.first, f.first, f.second});
    }
  }

  sort(q.begin(), q.end(),
       [](const auto& l, const auto& r) { return get<2>(l) < get<2>(r); });

  map<point, set<point>> adj;
  for (auto& v1 : v) adj.insert({v1, {}});

  assert(q.size() >= Q);
  for (int i = 0; i < Q; i++) {
    // printf("%d ", i);
    auto [a, b, w] = q[i];
    // printf("(%.0f %.0f %.0f)->(%.0f %.0f %.0f)[%0.0f]\n", a[0], a[1], a[2],
    //  b[0], b[1], b[2], w);

    adj[a].insert(b);
    adj[b].insert(a);
  }

  set<point> visited;
  vector<int> anss;

  for (auto& e : adj) {
    anss.push_back(dfs(adj, visited, e.first));
  }
  sort(anss.rbegin(), anss.rend());

  cout << anss[0] * anss[1] * anss[2] << '\n';
  // cout << q.size() << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("./A.in", "r", stdin);
  solve();
}