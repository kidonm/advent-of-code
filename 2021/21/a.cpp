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

vector<int> parsePos() {
  string skip = "Player 1 starting position: ";
  string s;
  vector<int> ret;

  while (getline(cin, s)) {
    ret.push_back(s[s.size() - 1] - 49);
  }

  return ret;
}

int main() {
  vector<int> players = parsePos();
  vector<int> sums(players.size(), 0);

  // printf("%d %d\n", a, b);

  int dice = 1;
  int rolls = 0;
  int aSum = 0;
  int bSum = 0;

  bool end = false;

  // 10 % 10 => 0 => 10
  // 11 % 10 => 1 => 1
  // 20 % 10 => 0 => 10
  // 12 % 10 -> 3
  //

  while (!end) {
    for (int i = 0; i < sums.size(); i++) {
      players[i] = (players[i] + (3 * dice) + 3) % 10;
      // if (players[i] == 0) players[i] = 10;

      sums[i] += players[i] + 1;
      dice += 3;
      rolls += 3;

      printf("i=%d score=%d \t pos=%d die=%d \n", i, sums[i], players[i] + 1,
             dice);

      if (sums[i] >= 1000) {
        end = true;
        break;
      }
    }
  }

  printf("rolls=%d\n", rolls);

  for (int i = 0; i < sums.size(); i++) {
    printf("i=%d sum=%d\n", i, sums[i]);
  }

  return 0;
}