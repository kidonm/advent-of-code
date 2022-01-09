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

int n = -400;
vector<int> asteps = {8, 8, 12, n, 2, 8, n, 9, n, 3, n, n, n, n};
vector<int> bsteps = {n, n, n, 8, n, n, 11, n, 3, n, 3, 1, 10, 16};

bool simulate(vector<int> &input, vector<int> &ans) {
  int z = 0;
  int input_pos = 0;

  for (int i = 0; i < 14; i++) {
    int a_const = asteps[i];
    int b_const = bsteps[i];

    if (a_const == n) {
      assert(b_const != n);
      ans[i] = (z % 26) - b_const;
      if (!(1 <= ans[i] && ans[i] <= 9)) return false;
      z /= 26;
    } else {
      assert(a_const != n);
      z = 26 * z + a_const + input[input_pos];
      ans[i] = input[input_pos];
      input_pos++;
    }
  }

  return z == 0;
}

bool solve(int pos, vector<int> &input, vector<int> &ans) {
  if (pos == 7) {
    return simulate(input, ans);
  }

  for (int i = 9; i > 0; i--) {
    input[pos] = i;
    if (solve(pos + 1, input, ans)) return true;
  }
  return false;
}

int main() {
  vector<int> input(7, 0);
  vector<int> ans(14, 0);

  assert(asteps.size() == 14);
  assert(bsteps.size() == 14);

  cout << solve(0, input, ans) << endl;

  for (int i : ans) {
    cout << i;
  }
  cout << endl;

  return 0;
}