#include <bits/stdc++.h>

using namespace std;

using ll = long long;

// map<tuple<string, bool, bool>, ll> n_vis;

ll dfs(map<string, vector<string>>& adj, map<string, ll>& dp, string n,
       string t) {
  if (n == t) return 1;

  if (dp[n] != -1) return dp[n];

  // n_vis[n]++;

  // bool n_fft = n == "fft" || fft;
  // bool n_dac = n == "dac" || dac;

  ll ret = 0;
  for (auto& ng : adj[n]) {
    // if (dp[{ng, n_fft, n_dac}] != -1)
    //   ret += dp[{ng, n_fft, n_dac}];
    // else
    ret += dfs(adj, dp, ng, t);
  }

  dp[n] = ret;
  return dp[n];
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

  map<string, ll> dp;
  for (auto& [k, v] : adj) dp.insert({k, -1});

  // for (auto& [k, v] : adj)
  //   for (bool fft : {true, false})
  //     for (bool dac : {true, false}) n_vis.insert({{k, fft, dac}, 0});

  ll ans = dfs(adj, dp, "svr", "fft");
  for (auto& [k, v] : adj) dp[k] = -1;
  ans *= dfs(adj, dp, "fft", "dac");
  for (auto& [k, v] : adj) dp[k] = -1;
  ans *= dfs(adj, dp, "dac", "out");

  cout << ans;

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
  time_taken /= 1e6;
  cout << "Time taken: " << fixed << time_taken << setprecision(9) << " millis"
       << '\n';
}