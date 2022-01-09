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
  cin >> s;
  stringstream ss(s);
  vector<int> input;

  for (int i; ss >> i;) {
    input.push_back(i);
    ss.ignore();
  }
  for (int i : input) {
    printf("%d ", i);
  }
  putchar('\n');

  sort(input.begin(), input.end());
  int mid = input.size() / 2;
  int med = input[mid];

  int ans = 0;
  for (int i : input) {
    ans += abs(med - i);
  }

  printf("%d", ans);

  return 0;
}
