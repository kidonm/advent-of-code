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

int msb(int len, vector<int> &vec, bool neg) {
  int gamma = 0;
  int coef = 1;
  for (int i = vec.size() - 1; i >= 0; i--) {
    int bit;
    if (neg) {
      bit = vec[i] <= len / 2 ? 1 : 0;
    } else {
      bit = vec[i] > len / 2 ? 1 : 0;
    }
    gamma = gamma + (bit * coef);
    coef *= 2;
  }

  printf("gamma %d\n", gamma);

  return gamma;
}

int main() {
  string s;

  vector<int> acc(12, 0);
  int len = 0;

  while (cin >> s) {
    for (int i = 0; i < s.size(); i++) {
      char c = s[i];

      if (c == '1') acc[i] += 1;
    }
    len++;
  }

  printf("%d", msb(len, acc, false) * msb(len, acc, true));

  return 0;
}