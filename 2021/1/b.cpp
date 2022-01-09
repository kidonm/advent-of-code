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

int main() {
  int n;
  int cnt = 0;

  int a, b, c;

  cin >> a;
  cin >> b;
  cin >> c;

  while (cin >> n) {
    int prev = a + b + c;
    a = b;
    b = c;
    c = n;
    int curr = a + b + c;
    // printf("%d\n", curr);

    if (curr > prev) {
      cnt++;
    }
  }

  printf("%d", cnt);

  return 0;
}