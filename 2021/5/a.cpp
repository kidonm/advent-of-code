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

int sign(int i) {
  if (i > 0) return 1;
  if (i < 0) return -1;
  return 0;
}

void swap(int &a, int &b) {
  int tmp = a;
  a = b;
  b = tmp;
}

int main() {
  const int size = 1000;
  int grid[size][size];
  string s;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      grid[i][j] = 0;
    }
  }

  while (getline(cin, s)) {
    int x1, x2, y1, y2;
    stringstream ss(s);

    ss >> x1;
    ss.ignore();
    ss >> y1;
    ss.ignore();
    ss.ignore();
    ss.ignore();
    ss.ignore();
    ss >> x2;
    ss.ignore();
    ss >> y2;

    if (x1 != x2 && y1 != y2) continue;

    // printf("%d %d %d %d", x1, y1, x2, y2);

    int isX = x1 == x2;
    if (isX) {
      if (y1 > y2) swap(y1, y2);
    } else {
      if (x1 > x2) swap(x1, x2);
    }

    // printf("%d %d %d %d", x1, y1, x2, y2);

    if (isX) {
      for (; y1 <= y2; y1++) {
        grid[x1][y1] += 1;
      }
    } else {
      for (; x1 <= x2; x1++) {
        grid[x1][y1] += 1;
      }
    }
  }

  int sum = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (grid[j][i] > 1) sum++;
      // printf("%d", grid[j][i]);
    }
    // putchar('\n');
  }
  printf("%d\n", sum);

  return 0;
}
