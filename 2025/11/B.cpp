#include <bits/stdc++.h>

using namespace std;

using ll = long long;

map<tuple<string, bool, bool>, ll> n_vis;

ll dfs(map<string, vector<string>>& adj, map<tuple<string, bool, bool>, ll>& dp,
       string& n, bool fft, bool dac) {
  if (n == "out") {
    if (fft && dac)
      return 1;
    else
      return 0;
  }

  if (dp[{n, fft, dac}] != -1) return dp[{n, fft, dac}];

  n_vis[{n, fft, dac}]++;

  bool n_fft = n == "fft" || fft;
  bool n_dac = n == "dac" || dac;

  ll ret = 0;
  for (auto& ng : adj[n]) {
    ret += dfs(adj, dp, ng, n_fft, n_dac);
  }

  dp[{n, n_fft, n_dac}] = ret;
  return dp[{n, n_fft, n_dac}];
  // return ret;
};

void solve() {
  string l;
  map<string, vector<string>> adj;
  while (getline(cin, l)) {
    stringstream ls(l);

    string k, v;
    ls >> k;
    adj.insert({k, vector<string>()});
    while (ls >> v) adj[k].push_back(v);
  }

  map<tuple<string, bool, bool>, ll> dp;
  for (auto& [k, v] : adj)
    for (bool fft : {true, false})
      for (bool dac : {true, false}) dp.insert({{k, fft, dac}, -1});

  for (auto& [k, v] : adj)
    for (bool fft : {true, false})
      for (bool dac : {true, false}) n_vis.insert({{k, fft, dac}, 0});

  string start = "svr";
  cout << dfs(adj, dp, start, false, false) << "\n";

  // for (auto& [n, p] : dp) {
  //   // for (auto& [n, p] : n_vis) {
  //   printf("%s %d %d: %d\n", get<0>(n).c_str(), get<1>(n), get<2>(n), p);
  // }
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