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
1,2,3

X   -> (0)1,2,3 -> (x)1,-3,2 -> (xx)1,-2,-3 -> (xxx)1,3,-2
Y   ->             (y)-3,2,1 -> (yy)-1,2,-3 -> (yyy)3,2,-1
Z   ->             (z)-2,1,3 -> (zz)-1,-2,3 -> (zzz)2,-1,3
XY  -> .                        (xy)-2,-3,1
*/

// 1,2,3 -> 1,-3,2 -> -2,-3,1
// 1,2,3 -> -3,2,1 ->

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

bool match(set<point> &aligned, scanner &scanner, vector<int> &o) {
  //   printf("tried: x=%d y=%d sx=%d sy=%d\n", o.axisX, o.axisY, o.signX,
  //   o.signY);
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

      //   for (const auto &p : realigned) {
      //     printf("(%d %d %d)", p[0], p[1], p[2]);
      //   }

      set<point> matched;

      set_intersection(aligned.begin(), aligned.end(),
                       realigned_translated.begin(), realigned_translated.end(),
                       inserter(matched, matched.begin()));

      // if (matched.size() > 8) {
      //   cout << matched.size() << endl;
      // }

      if (matched.size() >= 12) {
        printf("matched beacons: %lu - %d %d %d\n", matched.size(), trans[0],
               trans[1], trans[2]);
        // for (const auto &p : matched) {
        //   printf("%d,%d,%d\n", p[0], p[1], p[2]);
        // }

        aligned.merge(realigned_translated);
        return true;
      }
    }
  }

  return false;
}

void matchAll(set<point> &aligned, set<int> &aligned_scanners,
              vector<scanner> &unaligned_scanners) {
  while (aligned_scanners.size() < unaligned_scanners.size()) {
    bool matched = false;
    for (int i = 0; i < unaligned_scanners.size(); i++) {
      if (aligned_scanners.count(i) > 0) continue;

      for (auto &o : orientations) {
        if (matched) continue;
        if (match(aligned, unaligned_scanners[i], o)) {
          matched = true;
          for (const auto &m : aligned_scanners) {
            cout << m << " ";
          }
          printf("\nbeacons=%lu scanners=%lu/%lu\n", aligned.size(),
                 aligned_scanners.size(), unaligned_scanners.size());
          aligned_scanners.insert(i);
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

  //   point p = {1, 2, 3};

  //   for (auto &o : orientations) {
  //     point p2 = orient(o, p);
  //     printf("(%d, %d, %d)\n", p2[0], p2[1], p2[2]);
  //     // printf("(%d, %d, %d, %d, %d, %d)\n", axisX, signX, axisY, signY,
  //     axisZ,
  //     //    signZ);
  //   }
  //   exit(1);

  // cout << scanners.size() << " " << scanners.back().back().back() <<
  // endl;

  //   for (const auto &scanner : scanners) {
  //     for (const auto &point : scanner) {
  //       printf("%d %d %d\n", point[0], point[1], point[2]);
  //     }
  //     cout << endl;
  //   }

  //   return 0;

  set<point> aligned(scanners[0].begin(), scanners[0].end());
  set<int> matched_scanners = {0};

  matchAll(aligned, matched_scanners, scanners);

  cout << aligned.size() << endl;

  //   for (const auto &p : aligned) {
  //     printf("%d,%d,%d\n", p[0], p[1], p[2]);
  //   }

  return 0;
}