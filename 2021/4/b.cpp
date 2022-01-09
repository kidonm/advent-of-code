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
  vector<int> nums;
  int boardCount = 100;
  vector<vector<vector<int>>> boards(boardCount,
                                     vector<vector<int>>(5, vector<int>(5)));
  vector<vector<vector<bool>>> marks(
      boardCount, vector<vector<bool>>(5, vector<bool>(5, false)));
  unordered_set<int> boardWins;

  getline(cin, s);
  stringstream ss(s);

  for (int i; ss >> i;) {
    nums.push_back(i);
    if (ss.peek() == ',') {
      ss.ignore();
    }
  }

  int board = 0;
  int row = 0;
  int len = 0;

  // printf("here");
  for (int i = 0; i < boards.size(); i++) {
    for (int j = 0; j < 5; j++) {
      for (int k = 0; k < 5; k++) {
        int l;
        // printf("%d %d\n", i, l);
        cin >> l;
        boards[i][j][k] = l;
      }
    }
  }

  for (int num : nums) {
    for (int i = 0; i < boards.size(); i++) {
      for (int j = 0; j < 5; j++) {
        for (int k = 0; k < 5; k++) {
          if (boards[i][j][k] == num) {
            marks[i][j][k] = true;
          }
        }
      }

      auto search = boardWins.find(i);
      if (search != boardWins.end()) continue;

      for (int j = 0; j < 5; j++) {
        bool ansR = true;
        bool ansC = true;
        for (int k = 0; k < 5; k++) {
          ansR = ansR && marks[i][j][k];
          ansC = ansC && marks[i][k][j];
        }

        if (ansR || ansC) boardWins.insert(i);
        if (boardWins.size() == boardCount) {
          int sum = 0;
          for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
              sum += marks[i][j][k] ? 0 : boards[i][j][k];
            }
          }
          printf("Ans is %d", sum * num);
          return 0;
        };
      }
    }
  }

  return 0;
}