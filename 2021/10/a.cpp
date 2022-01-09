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

  unordered_map<char, int> weights = {
      {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
  unordered_map<char, char> opp = {
      {'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};
  int ans = 0;

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
          ans += weights[c];
          printf("%s: corrupted %c %c, ans: %d\n", s.c_str(), c, opp[top], ans);
          notCorrupted = false;
        }
      }
    }
  }

  printf("%d\n", ans);

  return 0;
}
