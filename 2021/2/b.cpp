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

  int aim = 0;
  int x = 0;
  int y = 0;

  while (cin >> dir) {
    cin >> len;

    if (dir == "forward") {
      x += len;
      y += aim * len;
    };
    if (dir == "up") aim -= len;
    if (dir == "down") aim += len;
  }

  printf("%d", x * y);
}