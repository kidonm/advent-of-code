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
typedef tuple<char, int, int, int> apod;
typedef tuple<int, vector<apod>> state;

vector<int> hallway = {1, 2, 4, 6, 8, 10, 11};

vector<string> burrow = {
    "#############",  //////////////////////////////////////////////////////////////
    "#...........#",  //////////////////////////////////////////////////////////////
    "###.#.#.#.###",  //////////////////////////////////////////////////////////////
    "..#.#.#.#.#..",  //////////////////////////////////////////////////////////////
    "..#########.."  //////////////////////////////////////////////////////////////
};

unordered_map<char, int> apodRooms = {{'A', 3}, {'B', 5}, {'C', 7}, {'D', 9}};
unordered_map<int, string> targetRooms = {
    {3, "AA"}, {5, "BB"}, {7, "CC"}, {9, "DD"}};
unordered_map<char, int> apodCost = {
    {'A', 1}, {'B', 10}, {'C', 100}, {'D', 1000}};

void print(state &s) {
  auto out = burrow;
  bool valid = true;
  for (auto apod : get<1>(s)) {
    auto [kind, hallway, room, roompos] = apod;
    if (hallway != -1) {
      if (out[1][hallway] != '.') valid = false;
      out[1][hallway] = kind;
    } else {
      if (out[2 + roompos][room] != '.') valid = false;
      out[2 + roompos][room] = kind;
    }
  }

  for (string row : out) {
    cout << row << endl;
  }
  cout << endl;

  assert(valid);
}

bool end(state &s) {
  auto [_, apods] = s;

  // final position
  for (auto apod : apods) {
    auto [kind, _1, room, _2] = apod;
    if (apodRooms[kind] == room) continue;
    return false;
  }

  return true;
}

string roomDescription(state &s, int curr_room) {
  auto [_1, apods] = s;
  string desc = "EE";

  for (auto apod : apods) {
    auto [kind, _1, room, roomposition] = apod;

    if (room == curr_room) {
      desc[roomposition] = kind;
    }
  }

  return desc;
}

bool canGo(state &s, int a, int curr_pos, int target_pos) {
  auto [_1, apods] = s;

  assert(curr_pos > 0);

  for (int i = 0; i < apods.size(); i++) {
    if (i == a) continue;
    auto [_5, intermediate_pos, _6, _7] = apods[i];
    if (intermediate_pos == -1) continue;
    if (curr_pos < target_pos) {
      if (curr_pos <= intermediate_pos && intermediate_pos <= target_pos)
        return false;
    } else {
      if (target_pos <= intermediate_pos && intermediate_pos <= curr_pos)
        return false;
    }
  }
  return true;
}

vector<state> goHallway(state &s, int a) {
  vector<state> out;

  auto [_1, apods] = s;
  auto [curr_kind, curr_hallway, curr_room, curr_roomposition] = apods[a];
  // int target_room = apodRooms[curr_kind];
  string rdesc = roomDescription(s, curr_room);

  assert(curr_hallway == -1);
  assert(curr_room > 0);
  assert(curr_roomposition >= 0);

  // cout << rdesc[0] << ";";

  if (rdesc == targetRooms[curr_room])  // Locked in a room
    return vector<state>();

  string tmps = targetRooms[curr_room];
  tmps[0] = 'E';
  if (rdesc == tmps) return vector<state>();

  if (curr_roomposition == 0) {  // Needs to go out
    for (int hall : hallway) {
      if (canGo(s, a, curr_room, hall)) {
        int cost = apodCost[curr_kind] * (1 + abs(hall - curr_room));
        auto tmp = apods;
        tmp[a] = {curr_kind, hall, -1, -1};
        out.push_back({cost, tmp});
      }
    }
  }

  if (curr_roomposition == 1 && rdesc[0] == 'E') {
    // cout << "GO out" << endl;
    for (int hall : hallway) {
      if (canGo(s, a, curr_room, hall)) {
        int cost = apodCost[curr_kind] * (2 + abs(hall - curr_room));
        auto tmp = apods;
        tmp[a] = {curr_kind, hall, -1, -1};
        out.push_back({cost, tmp});
      }
    }
  }

  return out;
}

vector<state> goRoom(state &s, int a) {
  vector<state> out;
  auto [_1, apods] = s;
  auto [curr_kind, curr_hallway, curr_room, curr_roomposition] = apods[a];
  assert(curr_hallway > 0);
  assert(curr_room == -1);
  assert(curr_roomposition == -1);

  int target_room = apodRooms[curr_kind];
  string rdesc = roomDescription(s, target_room);
  // printf("Go room curr=%d target=%d(%s)\n", curr_hallway, target_room,
  //        rdesc.c_str());

  if (canGo(s, a, curr_hallway, target_room)) {
    // printf("Can GO: %c %d", curr_kind, target_room);
    string tmps = "E";
    tmps.push_back(curr_kind);
    if (rdesc == tmps) {
      int cost = apodCost[curr_kind] * (1 + abs(curr_hallway - target_room));
      auto tmp = apods;
      tmp[a] = {curr_kind, -1, target_room, 0};
      out.push_back({cost, tmp});
    } else if (rdesc == "EE") {
      int cost = apodCost[curr_kind] * (2 + abs(curr_hallway - target_room));
      auto tmp = apods;
      tmp[a] = {curr_kind, -1, target_room, 1};
      out.push_back({cost, tmp});
    }
  }

  return out;
}

vector<state> nextStates(state &s) {
  vector<state> out;
  auto [_1, apods] = s;

  for (int i = 0; i < apods.size(); i++) {
    auto [kind, hallwaypos, room, roompos] = apods[i];

    vector<state> next;
    if (hallwaypos == -1)
      next = goHallway(s, i);
    else
      next = goRoom(s, i);

    out.insert(out.end(), next.begin(), next.end());
  }

  return out;
}

int main() {
  vector<tuple<char, int, int, int>> end_state = {
      {'A', -1, 3, 0}, {'A', -1, 3, 1}, {'B', -1, 5, 0}, {'B', -1, 5, 1},
      {'C', -1, 7, 0}, {'C', -1, 7, 1}, {'D', -1, 9, 0}, {'D', -1, 9, 1},
  };
  // vector<tuple<char, int, int, int>> st = {
  //     {'B', -1, 3, 0}, {'A', -1, 3, 1}, {'A', -1, 5, 0}, {'B', -1, 5, 1},
  //     {'D', -1, 7, 0}, {'C', -1, 7, 1}, {'C', -1, 9, 0}, {'D', -1, 9, 1},
  // };
  // vector<tuple<char, int, int, int>> st = {
  //     {'A', -1, 3, 0}, {'A', -1, 3, 1}, {'D', -1, 5, 0}, {'B', -1, 5, 1},
  //     {'B', -1, 7, 0}, {'C', -1, 7, 1}, {'C', -1, 9, 0}, {'D', -1, 9, 1},
  // };
  // vector<tuple<char, int, int, int>> st = {
  //     {'A', -1, 3, 0}, {'A', -1, 3, 1}, {'B', -1, 5, 0}, {'B', -1, 5, 1},
  //     {'D', -1, 7, 0}, {'D', -1, 7, 1}, {'C', -1, 9, 0}, {'C', -1, 9, 1},
  // };
  vector<tuple<char, int, int, int>> st = {
      {'D', -1, 3, 0}, {'D', -1, 3, 1}, {'A', -1, 5, 0}, {'C', -1, 5, 1},
      {'C', -1, 7, 0}, {'B', -1, 7, 1}, {'A', -1, 9, 0}, {'B', -1, 9, 1},
  };
  // vector<tuple<char, int, int, int>> st = {
  //     {'B', -1, 3, 0}, {'A', -1, 3, 1}, {'C', -1, 5, 0}, {'D', -1, 5, 1},
  //     {'B', -1, 7, 0}, {'C', -1, 7, 1}, {'D', -1, 9, 0}, {'A', -1, 9, 1},
  // };

  priority_queue<state, vector<state>, greater<state>> pq;
  set<vector<apod>> visited;
  map<vector<apod>, int> dist;

  pq.push({0, st});

  int minst = 1e9;

  while (!pq.empty()) {
    auto st = pq.top();
    auto [cost, apods] = st;
    // printf("cost: %d\n", cost);
    // print(st);
    if (end(st)) {
      minst = min(minst, cost);
      // cout << "found" << endl;
    }
    visited.insert(apods);

    pq.pop();

    for (auto next_state : nextStates(st)) {
      auto [next_cost, next_amphs] = next_state;
      if (visited.count(next_amphs) > 0) continue;

      dist.try_emplace(next_amphs, 1e9);
      int curr_cost = dist[next_amphs];

      if (curr_cost > cost + next_cost) {
        dist[next_amphs] = cost + next_cost;
        pq.push({dist[next_amphs], next_amphs});
      }
    }
  }

  cout << "min:" << minst << endl;

  return 0;
}