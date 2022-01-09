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

int main() {
  char c;
  vector<vector<int>> mat;

  for (string s; getline(cin, s);) {
    stringstream ss(s);
    vector<int> tmp;

    for (char c; ss >> c;) {
      tmp.push_back(c - 48);
    }

    mat.push_back(tmp);
  }

  for (int i = 0; i < mat.size(); i++) {
    for (int j = 0; j < mat[0].size(); j++) {
      if (i == 0 && j == 0)
        continue;
      else if (i == 0)
        mat[i][j] = mat[i][j] + mat[i][j - 1];
      else if (j == 0)
        mat[i][j] = mat[i][j] + mat[i - 1][j];
      else
        mat[i][j] = mat[i][j] + min(mat[i][j - 1], mat[i - 1][j]);
    }
  }

  // for (vector<int> row : mat) {
  //   for (int i : row) {
  //     printf("%d", i);
  //   }
  //   printf("\n");
  // }

  printf("%d", mat[mat.size() - 1][mat[0].size() - 1] - mat[0][0]);

  return 0;
}
