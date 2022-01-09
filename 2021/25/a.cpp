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
// typedef long long ll;
typedef pair<int, int> ipair;
typedef vector<int> coord;

int main() {
  vector<vector<char>> floor;

  for (string s; getline(cin, s);) {
    floor.push_back(vector<char>(s.begin(), s.end()));
  }

  int m = floor.size();
  int n = floor[0].size();
  bool changed = true;
  int rounds = 0;

  // for (auto row : floor) {
  //   for (char c : row) {
  //     cout << c;
  //   }
  //   cout << endl;
  // }
  // cout << endl;

  while (changed) {
    vector<vector<char>> prev = floor;
    changed = false;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        // printf("%d %d\n", i, j);
        if (prev[i][j] == '>') {
          if (prev[i][(j + 1) % n] == '.') {
            changed = true;
            // printf("move: (%d %d) -> (%d %d)\n", i, j, i, (j + 1) % n);
            floor[i][j] = '.';
            floor[i][(j + 1) % n] = '>';
            j++;
          }
        }
      }
    }

    prev = floor;

    for (int j = 0; j < n; j++) {
      for (int i = 0; i < m; i++) {
        // printf("%d %d\n", (i + 1) % n, j);
        if (prev[i][j] == 'v') {
          if (prev[(i + 1) % m][j] == '.') {
            changed = true;
            floor[i][j] = '.';
            floor[(i + 1) % m][j] = 'v';
            i++;
          }
        }
      }
    }
    rounds++;

    // for (auto row : floor) {
    //   for (char c : row) {
    //     cout << c;
    //   }
    //   cout << endl;
    // }
    // cout << endl;
  }

  cout << "ans:" << rounds << endl;

  return 0;
}