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

int main() {
  string s;
  vector<vector<string>> displays;
  vector<vector<string>> outputs;

  while (getline(cin, s)) {
    // printf("%s\n", s.c_str());
    stringstream ss(s);
    string buf;
    vector<string> vBuf;
    for (int i = 0; i < 10; i++) {
      ss >> buf;
      vBuf.push_back(buf);
    }
    displays.push_back(vBuf);

    vBuf.clear();
    ss >> buf;

    for (int i = 0; i < 4; i++) {
      ss >> buf;
      vBuf.push_back(buf);
    }
    outputs.push_back(vBuf);
  }

  int ans = 0;
  for (vector<string> digits : outputs) {
    for (string s : digits) {
      // printf("%s ", s.c_str());
      int sz = s.size();
      if (sz == 2 || sz == 3 || sz == 4 || sz == 7) {
        // printf("%s ", s.c_str());
        ans++;
      }
    }
    // printf("\n");
  }
  printf("%d\n", ans);

  return 0;
}
