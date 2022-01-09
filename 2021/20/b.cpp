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
typedef vector<int> coord;

void widen(deque<deque<char>> &img, int times, char c) {
  for (auto &row : img) {
    for (int i = 0; i < times; i++) {
      row.push_front(c);
      row.push_back(c);
    }
  }

  deque<char> r(img[0].size(), c);

  for (int i = 0; i < times; i++) {
    img.push_front(r);
    img.push_back(r);
  }
};

void print(deque<deque<char>> &img) {
  for (auto row : img) {
    for (auto col : row) {
      printf("%c", col);
    }
    printf("\n");
  }
  printf("\n");
}

int index(int i, int j, deque<deque<char>> &src, char frame) {
  int ix = 0;
  int m = src.size();
  int n = src[0].size();
  for (int di : {-1, 0, 1}) {
    for (int dj : {-1, 0, 1}) {
      int bit = 0;

      if (i + di >= 0 && i + di < m && j + dj >= 0 && j + dj < n) {
        bit = src[i + di][j + dj] == '.' ? 0 : 1;
      } else {
        bit = frame == '.' ? 0 : 1;
      }

      // printf("%d", bit);
      ix += bit;
      // ix *= 2;
      if (dj == 1 && di == 1) continue;
      ix *= 2;
    }
  }
  // ix /= 2;
  return ix;
  // dst[i][j] = code[ix];
}

int main() {
  int times = 50;
  string code;
  deque<deque<char>> img;
  getline(cin, code);

  string s;
  getline(cin, s);

  while (getline(cin, s)) {
    deque<char> tmp;
    for (char c : s) {
      tmp.push_back(c);
    }
    img.push_back(tmp);
  }

  // printf("index: %d", index(2, 2, img));
  // return 0;

  // printf("%lu %lu\n", img.size(), img[0].size());
  // return 0;

  char frame = '.';
  widen(img, 2, frame);
  for (int t = 0; t < times; t++) {
    deque<deque<char>> next(img);
    // print(img);

    for (int i = 0; i < img.size(); i++) {
      for (int j = 0; j < img[0].size(); j++) {
        next[i][j] = code[index(i, j, img, frame)];
      }
    }

    // char frame = t % 2 == 1 ? code[0] : code[code.size() - 1];
    // if (code[0] == '.') frame = '.';
    // printf("here\n");

    img = next;
    frame = img[0][0];
    // print(img);
    widen(img, 1, frame);
  }
  print(img);

  int sum = 0;
  for (int i = 0; i < img.size(); i++) {
    for (int j = 0; j < img[0].size(); j++) {
      if (img[i][j] == '#') sum++;
    }
  }

  printf("%lu %lu %d\n", img.size(), img[0].size(), sum);

  return 0;
}