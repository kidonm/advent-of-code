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

struct command {
  bool on;
  ipair x;
  ipair y;
  ipair z;

  void print() {
    printf("on=%d x=(%d..%d), y=(%d %d), z=(%d %d)\n", on, x.first - 50,
           x.second - 50, y.first - 50, y.second - 50, z.first - 50,
           z.second - 50);
  }
};

int dim = 100;

vector<command> parse() {
  vector<command> out;
  for (string s; getline(cin, s);) {
    bool ignore = false;
    stringstream ss(s);
    command c;
    string op;

    ss >> op;

    vector<ipair> coords;
    for (int i = 0; i < 3; i++) {
      ipair dim;
      ss.ignore();
      ss.ignore();
      ss.ignore();
      // cout << ss.str() << endl;
      ss >> dim.first;
      ss.ignore();
      ss.ignore();
      ss >> dim.second;
      if (dim.first < -50 || dim.first > 50 || dim.second < -50 ||
          dim.second > 50) {
        ignore = true;
      }
      dim.first += 50;
      dim.second += 50;

      coords.push_back(dim);
    }

    c.on = op == "on";
    c.x = coords[0];
    c.y = coords[1];
    c.z = coords[2];

    if (!ignore) out.push_back(c);
  }
  return out;
}

int main() {
  vector<vector<vector<bool>>> reactor(
      dim + 1, vector<vector<bool>>(dim + 1, vector<bool>(dim + 1, false)));
  vector<command> input;

  input = parse();

  for (auto c : input)
    for (int i = c.x.first; i <= c.x.second; i++)
      for (int j = c.y.first; j <= c.y.second; j++)
        for (int k = c.z.first; k <= c.z.second; k++) reactor[i][j][k] = c.on;

  int sum = 0;
  for (int i = 0; i <= 100; i++)
    for (int j = 0; j <= 100; j++)
      for (int k = 0; k <= 100; k++)
        if (reactor[i][j][k]) sum++;

  printf("sum=%d\n", sum);

  return 0;
}