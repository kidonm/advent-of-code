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

struct command {
  string on;
  int x0, x1, y0, y1, z0, z1;
};

int main() {
  vector<command> commands;
  vector<int> X, Y, Z;
  string on;

  while (cin >> on) {
    commands.emplace_back();
    command &c = commands.back();

    c.on = on;
    cin >> c.x0 >> c.x1 >> c.y0 >> c.y1 >> c.z0 >> c.z1;
    c.x1++;
    c.y1++;
    c.z1++;
    X.push_back(c.x0);
    X.push_back(c.x1);
    Y.push_back(c.y0);
    Y.push_back(c.y1);
    Z.push_back(c.z0);
    Z.push_back(c.z1);
  };

  int N = int(X.size());

  sort(X.begin(), X.end());
  sort(Y.begin(), Y.end());
  sort(Z.begin(), Z.end());

  auto get_index = [&](vector<int> &cs, int c) -> int {
    return int(lower_bound(cs.begin(), cs.end(), c) - cs.begin());
  };

  vector<vector<vector<bool>>> grid(
      N, vector<vector<bool>>(N, vector<bool>(N, false)));

  for (command &c : commands) {
    int x0 = get_index(X, c.x0);
    int x1 = get_index(X, c.x1);
    int y0 = get_index(Y, c.y0);
    int y1 = get_index(Y, c.y1);
    int z0 = get_index(Z, c.z0);
    int z1 = get_index(Z, c.z1);
    int on = c.on == "on";

    for (int x = x0; x < x1; x++)
      for (int y = y0; y < y1; y++)
        for (int z = z0; z < z1; z++) grid[x][y][z] = on;
  }

  uint64_t sum = 0;

  for (int x = 0; x < N - 1; x++)
    for (int y = 0; y < N - 1; y++)
      for (int z = 0; z < N - 1; z++)
        sum += uint64_t(grid[x][y][z]) * (X[x + 1] - X[x]) * (Y[y + 1] - Y[y]) *
               (Z[z + 1] - Z[z]);

  cout << sum << endl;

  return 0;
}