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
typedef pair<int, int> ipair;

int sim(ipair p, ipair a, ipair b, int x, int y) {
  int dy = y;
  int dx = x;
  int highest = 0;

  while (p.first <= b.first && p.second >= b.second) {
    // printf("debug: dx:%d dy:%d x:%d y:%d\n", dx, dy, p.first, p.second);

    highest = max(highest, p.second + dy);

    if (p.first >= a.first && p.second <= a.second) {
      printf("vel=(%d %d) hit=(%d %d) highest=%d\n", x, y, p.first, p.second,
             highest);
      return highest;
    }

    p.first += dx;
    p.second += dy;

    dy -= 1;
    dx -= 1;
    if (dx < 0) dx = 0;
  }
  return -1;
}

int main() {
  // ipair a = {20, -5};
  // ipair b = {30, -10};
  // int xOff = 0;
  // int yOff = 10;

  ipair a = {241, -49};
  ipair b = {275, -75};
  int xOff = 0;
  int yOff = 75;

  int highest = 0;
  int sum = 0;

  for (int x = 1; x <= b.first; x++) {
    for (int y = -100; y <= 100; y++) {
      int tmp = sim({0 + xOff, 0 + yOff}, {a.first + xOff, a.second + yOff},
                    {b.first + xOff, b.second + yOff}, x, y);

      highest = max(highest, tmp - yOff);
      if (tmp != -1) sum++;
    }
  }

  printf("highest: %d sum: %d\n", highest, sum);

  return 0;
}
