#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

bool isSmall(string &s) {
  int ans = true;

  for (char c : s) {
    if (!(c >= 'a' && c <= 'z')) ans = false;
    if (!ans) break;
  }

  return ans;
}

int bt(string n, unordered_map<string, unordered_set<string>> &adj,
       unordered_map<string, int> &visited, bool twice,
       unordered_set<string> &smalls) {
  int ans;
  bool small = smalls.count(n) > 0;

  if (n == "end") return 1;

  if (small) {
    if (twice && visited[n] > 0) return 0;
    if (!twice && visited[n] > 1) return 0;

    visited[n]++;
  }
  ans = 0;

  for (string next : adj[n]) {
    if (next == "start") continue;
    ans += bt(next, adj, visited, twice || visited[n] > 1, smalls);
  }

  if (small) {
    visited[n]--;
  }

  return ans;
}

int main() {
  vector<pair<string, string>> edges;
  unordered_map<string, unordered_set<string>> adj;

  string s;
  while (getline(cin, s)) {
    string n1;
    string n2;
    int delimPos = s.find("-");

    n1 = s.substr(0, delimPos);
    n2 = s.substr(delimPos + 1);

    edges.push_back({n1, n2});
  }

  for (pair<string, string> e : edges) {
    adj.insert({e.first, unordered_set<string>()});
    adj.insert({e.second, unordered_set<string>()});
  }

  for (pair<string, string> e : edges) {
    adj[e.first].insert(e.second);
    adj[e.second].insert(e.first);
  }

  // for (auto entry : adj) {
  //   printf("%s -> ", entry.first.c_str());
  //   for (string next : entry.second) {
  //     printf("%s ", next.c_str());
  //   }
  //   printf("\n");
  // }

  unordered_map<string, int> visited;
  unordered_set<string> smalls;

  for (pair<string, string> e : edges) {
    visited.insert({e.first, 0});
    visited.insert({e.second, 0});
    if (isSmall(e.first)) smalls.insert({e.first});
    if (isSmall(e.second)) smalls.insert({e.second});
  }

  // for (auto vis : visited) {
  //   printf("(%s, %d) ", vis.first.c_str(), vis.second);
  // }
  string start = "start";

  // printf("%d\n", bt(start, adj, visited, false, smalls));
  printf("%d\n", bt("start", adj, visited, false, smalls));

  return 0;
}
