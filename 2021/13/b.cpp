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

void print(set<pair<int, int>> &points, int m, int n) {
  vector<vector<char>> grid(m, vector<char>(n, ' '));
  int maxX = 0;
  int maxY = 0;
  for (auto p : points) {
    // printf("(%d %d)", p.first, p.second);
    grid[p.first][p.second] = '#';
    maxX = max(maxX, p.first);
    maxY = max(maxY, p.second);
  }

  printf("x: %d y: %d\n", maxX, maxY);
  for (int i = 0; i <= maxY; i++) {
    for (int j = 0; j <= maxX; j++) {
      printf("%c", grid[j][i]);
    }
    printf("\n");
  }
}

int main() {
  string s;

  set<pair<int, int>> points;
  vector<pair<char, int>> folds;

  while (getline(cin, s) && !s.empty()) {
    stringstream ss(s);
    int x;
    int y;

    ss >> x;
    ss.ignore();
    ss >> y;

    points.insert({x, y});
  }

  while (getline(cin, s)) {
    string skip = "fold along ";
    s = s.substr(skip.size());

    stringstream ss(s);

    char xy;
    int off;
    ss >> xy;
    ss.ignore();
    ss >> off;

    pair<char, int> fold = {xy, off};
    // printf("%s, %c, %d \n", s.c_str(), fold.first, fold.second);
    folds.push_back(fold);
  }

  for (pair<char, int> fold : folds) {
    char xy = fold.first;
    int off = fold.second;

    set<pair<int, int>> tmp;
    for (pair<int, int> p : points) {
      int x = p.first;
      int y = p.second;

      if (xy == 'x' && x > off) {
        x = off - (x - off);
      } else if (xy == 'y' && y > off) {
        y = off - (y - off);
      }

      tmp.insert({x, y});
    }
    points = tmp;
  }

  // print(points, 5, 100);
  print(points, 39, 6);

  return 0;
}
