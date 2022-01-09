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
       vector<string> &path, unordered_set<string> &visited) {
  int ans;
  bool small = isSmall(n);

  if (n == "end") {
    for (string s : path) {
      printf("%s ", s.c_str());
    }
    printf("\n");
    return 1;
  }
  if (visited.count(n) > 0) return 0;

  ans = 0;
  if (small) visited.insert(n);

  for (string next : adj[n]) {
    path.push_back(next);
    ans += bt(next, adj, path, visited);
    path.pop_back();
  }

  visited.erase(n);

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

  vector<string> path{"start"};
  unordered_set<string> visited;

  printf("%d\n", bt("start", adj, path, visited));

  return 0;
}
