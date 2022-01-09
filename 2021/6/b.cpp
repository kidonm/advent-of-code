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

typedef long long ll;

int main() {
  int cycle = 9;
  vector<ll> sim(cycle, 0);
  string s;
  cin >> s;
  stringstream ss(s);

  for (int i; ss >> i;) {
    sim[i]++;
    ss.ignore();
  }

  for (int i = 0; i < 256; i++) {
    ll tmp = sim[0];
    sim.erase(sim.begin());
    sim.push_back(tmp);
    sim[6] += tmp;

    // for (int i : sim) {
    //   printf("%d ", i);
    // }
    // putchar('\n');
  }

  ll sum = 0;
  for (ll i : sim) {
    sum += i;
  }

  printf("sum: %llu\n", sum);

  return 0;
}
