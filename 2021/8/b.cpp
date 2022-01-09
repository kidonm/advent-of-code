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

/*
 aaaa
b    c
b    c
 dddd
e    f
e    f
 gggg

  (0)a: 8 -> diff(7, 1))
  (1)b: 6 -> b
  (2)c: 8 -> num(8() / a
  (3)d: 7 -> deduce from (4)
  (4)e: 4 -> e
  (5)f: 9 -> f
  (6)g: 7 -> num(7) / d
*/

bool contains(string &s1, string &s2) {
  unordered_set<char> s1set(s1.begin(), s1.end());
  bool ans = true;
  for (char c : s2) {
    ans = ans && (s1set.count(c) == 1);
  }
  return ans;
}

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
      sort(buf.begin(), buf.end());
      vBuf.push_back(buf);
    }
    displays.push_back(vBuf);

    printf("here\n");

    vBuf.clear();
    ss >> buf;

    for (int i = 0; i < 4; i++) {
      ss >> buf;
      sort(buf.begin(), buf.end());
      vBuf.push_back(buf);
    }
    printf("here\n");
    // reverse(vBuf.begin(), vBuf.end());
    outputs.push_back(vBuf);
  }

  int ans = 0;

  for (int i = 0; i < displays.size(); i++) {
    vector<string> nums(10);

    for (string s : displays[i]) {
      if (s.size() == 2) nums[1] = s;
      if (s.size() == 3) nums[7] = s;
      if (s.size() == 4) nums[4] = s;
      if (s.size() == 7) nums[8] = s;
    }

    for (string s : displays[i]) {
      if (s.size() == 6) {
        if (contains(s, nums[1])) {
          if (contains(s, nums[4])) {
            nums[9] = s;
          } else {
            nums[0] = s;
          }
        } else {
          nums[6] = s;
        }
      }
    }

    for (string s : displays[i]) {
      if (s.size() == 5) {
        if (contains(s, nums[7]))
          nums[3] = s;
        else if (contains(nums[6], s))
          nums[5] = s;
        else
          nums[2] = s;
      }
    }

    unordered_map<string, int> mapping;
    for (int i = 0; i < nums.size(); i++) {
      printf("mapping %s -> %d\n", nums[i].c_str(), i);
      mapping.insert({nums[i], i});
    }

    for (string o : outputs[i]) {
      printf("%s\n", o.c_str());
    }

    ans += (mapping[outputs[i][0]] * 1000) + (mapping[outputs[i][1]] * 100) +
           (mapping[outputs[i][2]] * 10) + (mapping[outputs[i][3]]);
  }
  printf("%d", ans);

  return 0;
}
