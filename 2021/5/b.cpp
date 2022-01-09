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

    int dirX = sign(x2 - x1);
    int dirY = sign(y2 - y1);

    // Ax + By = C
    // A = y2 - y1
    // B = x2 - x1
    // C = Ax1 + By1

    // (0 8) (8 0)
    // A = -8
    // B = 8

    // (9 4) (3 4)
    // A = -1
    // B = -5

    // if (isDiagonal) continue;

    // printf("%d %d %d %d\n", x1, y1, x2, y2);
    for (;
         (dirX == 1 ? x1 <= x2 : x2 <= x1) && (dirY == 1 ? y1 <= y2 : y2 <= y1);
         x1 += dirX, y1 += dirY) {
      grid[x1][y1] += 1;
    }
    // for (int i = 0; i < size; i++) {
    //   for (int j = 0; j < size; j++) {
    //     printf("%d", grid[j][i]);
    //   }
    //   putchar('\n');
    // }
    // putchar('\n');
  }

  int maxGray = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      maxGray = max(grid[j][i], maxGray);
    }
  }
  // printf("%d\n", maxGray);
  // printf("%d\n", sum);
  printf("P2\n");
  printf("%d %d\n", size, size);
  printf("%d\n", maxGray);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf("%d ", grid[j][i]);
    }
    putchar('\n');
  }

  return 0;
}
