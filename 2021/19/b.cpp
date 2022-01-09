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

typedef vector<int> point;
typedef vector<point> scanner;

vector<vector<int>> orientations = {
    {0, 1, 1, 1, 2, 1},   {0, 1, 1, -1, 2, -1},  {0, 1, 2, 1, 1, -1},
    {0, 1, 2, -1, 1, 1},  {0, -1, 1, 1, 2, -1},  {0, -1, 1, -1, 2, 1},
    {0, -1, 2, 1, 1, 1},  {0, -1, 2, -1, 1, -1}, {1, 1, 0, 1, 2, -1},
    {1, 1, 0, -1, 2, 1},  {1, 1, 2, 1, 0, 1},    {1, 1, 2, -1, 0, -1},
    {1, -1, 0, 1, 2, 1},  {1, -1, 0, -1, 2, -1}, {1, -1, 2, 1, 0, -1},
    {1, -1, 2, -1, 0, 1}, {2, 1, 0, 1, 1, 1},    {2, 1, 0, -1, 1, -1},
    {2, 1, 1, 1, 0, -1},  {2, 1, 1, -1, 0, 1},   {2, -1, 0, 1, 1, -1},
    {2, -1, 0, -1, 1, 1}, {2, -1, 1, 1, 0, 1},   {2, -1, 1, -1, 0, -1}};

point orient(vector<int> &o, point &p) {
  return {p[o[0]] * o[1], p[o[2]] * o[3], p[o[4]] * o[5]};
}

pair<bool, point> match(set<point> &aligned, scanner &scanner, vector<int> &o) {
  for (const auto &p0 : aligned) {
    vector<point> realigned;
    for (point &p : scanner) {
      realigned.push_back(orient(o, p));
    }

    for (const auto &p1 : realigned) {
      point trans = {p0[0] - p1[0], p0[1] - p1[1], p0[2] - p1[2]};

      set<point> realigned_translated;

      for (point &p : realigned) {
        realigned_translated.insert(
            {p[0] + trans[0], p[1] + trans[1], p[2] + trans[2]});
      }

      set<point> matched;

      set_intersection(aligned.begin(), aligned.end(),
                       realigned_translated.begin(), realigned_translated.end(),
                       inserter(matched, matched.begin()));

      if (matched.size() >= 12) {
        aligned.merge(realigned_translated);
        return {true, trans};
      }
    }
  }

  return {false, {0, 0, 0}};
}

void matchAll(set<point> &aligned, unordered_map<int, point> &aligned_scanners,
              vector<scanner> &unaligned_scanners) {
  while (aligned_scanners.size() < unaligned_scanners.size()) {
    bool matched = false;
    for (int i = 0; i < unaligned_scanners.size(); i++) {
      if (aligned_scanners.count(i) > 0) continue;

      for (auto &o : orientations) {
        if (matched) continue;
        auto [found, translation] = match(aligned, unaligned_scanners[i], o);
        if (found) {
          matched = true;
          aligned_scanners.insert({i, translation});
        }
      }
    }
    assert(matched);
  }
}

int main() {
  vector<vector<vector<int>>> scanners;
  scanners.emplace_back();

  for (string s; getline(cin, s);) {
    if (s.empty()) {
      scanners.emplace_back();
      continue;
    }
    stringstream ss(s);
    vector<vector<int>> &scanner = scanners.back();

    auto &beacon = scanner.emplace_back(vector<int>(3, 0));
    ss >> beacon[0] >> beacon[1] >> beacon[2];
  }

  set<point> aligned(scanners[0].begin(), scanners[0].end());
  unordered_map<int, point> matched_scanners;
  matched_scanners.insert({0, {0, 0, 0}});

  matchAll(aligned, matched_scanners, scanners);

  int mdist = 0;

  for (const auto [sc1, t1] : matched_scanners) {
    for (const auto [sc2, t2] : matched_scanners) {
      int dist = abs(t2[0] - t1[0]) + abs(t2[1] - t1[1]) + abs(t2[2] - t1[2]);
      mdist = max(mdist, dist);
    }
  }

  cout << mdist << endl;

  return 0;
}