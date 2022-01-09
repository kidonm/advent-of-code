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

typedef unsigned long long ll;

ll dfs(string &l, char targetChar, int d, int targetDepth,
       unordered_map<string, pair<char, vector<string>>> &rules,
       vector<unordered_map<string, ll>> &mem) {
  if (d == targetDepth) return 0;

  // printf("%s %d\n", l.c_str(), d);

  auto srch1 = mem[d].find(l);
  if (srch1 != mem[d].end()) {
    return srch1->second;
  }

  // printf("%d %s \n", d, l.c_str());

  auto search = rules.find(l);
  ll ans = 0;
  if (search != rules.end()) {
    if (search->second.first == targetChar) ans++;

    ans += dfs(search->second.second[0], targetChar, d + 1, targetDepth, rules,
               mem);
    ans += dfs(search->second.second[1], targetChar, d + 1, targetDepth, rules,
               mem);
  };

  mem[d].insert({l, ans});

  return ans;
};

int main() {
  string start;
  unordered_map<string, pair<char, vector<string>>> rules;
  unordered_map<char, ll> counts;
  vector<unordered_map<string, ll>> mem;
  int depth = 40;

  cin >> start;

  for (string s; getline(cin, s);) {
    if (s.empty()) continue;

    stringstream ss(s);
    string l = s.substr(0, 2);
    char r = (s.substr(6))[0];

    string s1, s2;
    s1.push_back(l[0]);
    s1.push_back(r);

    s2.push_back(r);
    s2.push_back(l[1]);

    pair<char, vector<string>> pr = {r, vector<string>{s1, s2}};

    rules.insert({l, pr});
  }

  // for (auto r : rules) {
  //   printf("%s -> %s\n", r.first.c_str(), r.second.c_str());
  // }

  // printf("here\n");

  for (int i = 0; i < depth; i++) {
    unordered_map<string, ll> tmp;
    mem.push_back(tmp);
  }

  for (char c = 'A'; c <= 'Z'; c++) {
    counts.insert({c, 0});
  }

  for (char c : start) {
    counts[c]++;
  }

  for (char c = 'A'; c <= 'Z'; c++) {
    mem = vector<unordered_map<string, ll>>(depth, unordered_map<string, ll>());

    ll count = 0;
    for (int i = 0; i < start.size() - 1; i++) {
      string begin = start.substr(i, 2);
      dfs(begin, c, 0, depth, rules, mem);
      count += mem[0][begin];
    }
    counts[c] += count;
    // printf("%llu", count);
  }

  // ll mini = coun;
  // ll maxi = INT_MIN;

  for (auto count : counts) {
    if (count.second == 0) continue;
    printf("%c %llu\n", count.first, count.second);
    // mini = min(mini, count.second);
    // maxi = max(maxi, count.second);
  }

  // printf("%llu %llu", start.size(), maxi - mini);

  return 0;
}
