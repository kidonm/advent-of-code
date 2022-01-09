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
  vector<int> sim(8, 0);
  string s;
  cin >> s;
  stringstream ss(s);

  for (int i; ss >> i;) {
    sim[i]++;
    ss.ignore();
  }

  for (int i = 0; i < 80; i++) {
    int tmp = sim[0];
    sim.erase(sim.begin());
    sim.push_back(tmp);
    sim[6] += tmp;

    for (int i : sim) {
      printf("%d ", i);
    }
    putchar('\n');
  }

  int sum = 0;
  for (int i : sim) {
    sum += i;
  }

  printf("sum: %d\n", sum);

  return 0;
}
