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

typedef unsigned long long ull;

int main() {
  string start;
  unordered_map<string, string> rules;

  cin >> start;

  for (string s; getline(cin, s);) {
    if (s.empty()) continue;

    stringstream ss(s);
    string l = s.substr(0, 2);
    string r = s.substr(6);

    rules.insert({l, r});
  }

  // for (auto r : rules) {
  //   printf("%s -> %s\n", r.first.c_str(), r.second.c_str());
  // }

  for (int i = 0; i < 10; i++) {
    string buff;
    string tmp;
    buff += start[0];
    tmp += start[0];

    for (int i = 1; i < start.size(); i++) {
      buff.push_back(start[i]);

      auto search = rules.find(buff);

      // printf("%s %s found: %d\n", tmp.c_str(), buff.c_str(),
      //        !(search == rules.end()));

      if (search != rules.end()) {
        tmp += search->second;
      }

      tmp += start[i];
      buff = buff.substr(1);
    }
    start = tmp;
  }
  // printf("%s\n", start.c_str());

  map<char, ull> gr;
  for (char c : start) {
    gr.insert({c, 0});
  }

  ull mini = INT_MAX;
  ull maxi = INT_MIN;

  for (char c : start) {
    gr[c]++;
  }

  for (auto g : gr) {
    // printf("(%c, %d) ", g.first, g.second);
    mini = min(mini, g.second);
    maxi = max(maxi, g.second);
  }

  printf("%llu %llu", start.size(), maxi - mini);

  return 0;
}
