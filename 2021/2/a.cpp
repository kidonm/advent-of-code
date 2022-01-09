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
  string dir;
  int len;

  int x = 0;
  int y = 0;

  while (cin >> dir) {
    cin >> len;

    if (dir == "forward") x += len;
    if (dir == "up") y -= len;
    if (dir == "down") y += len;
  }

  printf("%d", x * y);
}