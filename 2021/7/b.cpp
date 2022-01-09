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

int sums(vector<int> &vec, int target) {
  int sum = 0;
  for (int i : vec) {
    int n = abs(target - i);
    int delta = n * (n + 1) / 2;
    // printf("delta: %d \n", delta);
    sum += delta;
  }
  return sum;
}

int main() {
  string s;
  cin >> s;
  stringstream ss(s);
  vector<int> input;

  for (int i; ss >> i;) {
    input.push_back(i);
    ss.ignore();
  }
  // for (int i : input) {
  //   printf("%d ", i);
  // }
  // putchar('\n');

  sort(input.begin(), input.end());

  int prev = INT_MIN;
  int minim = INT_MAX;
  int minPos = 0;

  for (int i = 0; i < 2000; i++) {
    int target = i;
    if (target == prev) {
      continue;
    }
    // printf("target %d\n", target);
    int cost = sums(input, target);

    printf("%d \n", cost);

    if (minim > cost) {
      minim = cost;
      minPos = target;
    }
    // minim = min(minim, cost);
    prev = target;
    // printf("\n");
  }

  printf("Cost: %d, Pos: %d\n", minim, minPos);

  return 0;
}
