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

int main() {
  string s;

  unordered_map<char, int> weights = {{')', 1}, {']', 2}, {'}', 3}, {'>', 4}};
  unordered_map<char, char> opp = {
      {'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};
  vector<long> anss;

  while (getline(cin, s)) {
    stringstream ss(s);
    vector<char> stack;
    bool notCorrupted = true;

    // printf("%s\n", s.c_str());

    for (char c; ss >> c && notCorrupted;) {
      if (c == '(' || c == '{' || c == '<' || c == '[') {
        stack.push_back(c);
      } else {
        char top = stack.back();
        if (opp[top] == c) {
          stack.pop_back();
        } else {
          // ans += weights[c];
          // printf("%s: corrupted %c %c, ans: %d\n", s.c_str(), c, opp[top],
          // ans);
          notCorrupted = false;
        }
      }
    }

    if (notCorrupted) {
      long ans = 0;
      for (int i = stack.size() - 1; i >= 0; i--) {
        ans *= 5;
        ans += weights[opp[stack[i]]];
      }
      // printf("%s: not corrupted, ans: %lu, size: %d\n", s.c_str(), ans,
      //        stack.size());
      anss.push_back(ans);
    }
  }

  sort(anss.begin(), anss.end());
  printf("%lu\n", anss[anss.size() / 2]);

  return 0;
}
