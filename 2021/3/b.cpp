#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int numOnes(vector<string> &vec, int ix) {
  int ans = 0;
  for (string s : vec) {
    if (s[ix] == '1') ans++;
  }

  return ans;
}

vector<string> fil(char c, int ix, vector<string> &vec) {
  vector<string> ans;
  for (string s : vec) {
    if (s[ix] == c) ans.push_back(s);
  }
  return ans;
}

int bin(string &s) {
  int coef = 1;
  int ans = 0;
  for (int i = s.size() - 1; i >= 0; i--) {
    if (s[i] == '1') ans += coef;
    // printf("%d\n", ans);
    coef *= 2;
  }
  return ans;
}

int rat(char c1, char c2, vector<string> &vec) {
  vector<string> step = vec;

  for (int i = 0; step.size() > 1 && i < step[0].size(); i++) {
    int ones = numOnes(step, i);
    char rem = ones >= step.size() - ones ? c1 : c2;
    step = fil(rem, i, step);
  }

  return bin(step[0]);
}

int main() {
  string s;

  vector<string> acc;

  while (cin >> s) {
    acc.push_back(s);
  }

  printf("%d\n", rat('1', '0', acc) * rat('0', '1', acc));

  return 0;
}