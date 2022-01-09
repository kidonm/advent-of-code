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
    "..#.#.#.#.#..",  //////////////////////////////////////////////////////////////
    "..#.#.#.#.#..",  //////////////////////////////////////////////////////////////
    "..#########.."  //////////////////////////////////////////////////////////////
};

unordered_map<char, int> apodRooms = {{'A', 3}, {'B', 5}, {'C', 7}, {'D', 9}};
unordered_map<int, string> targetRooms = {
    {3, "AAAA"}, {5, "BBBB"}, {7, "CCCC"}, {9, "DDDD"}};
unordered_map<char, int> apodCost = {
    {'A', 1}, {'B', 10}, {'C', 100}, {'D', 1000}};

void print(vector<apod> &apods) {
  auto out = burrow;
  bool valid = true;
  for (auto apod : apods) {
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

bool isend(const vector<apod> &apods) {
  // final position
  for (auto &apod : apods) {
    auto [kind, _1, room, _2] = apod;
    if (apodRooms[kind] == room) continue;
    return false;
  }

  return true;
}

string roomDescription(state &s, int curr_room) {
  auto &[_1, apods] = s;
  string desc = "EEEE";

  for (auto &apod : apods) {
    auto &[kind, _1, room, roomposition] = apod;

    if (room == curr_room) {
      desc[roomposition] = kind;
    }
  }

  return desc;
}

bool canGo(state &s, int a, int curr_pos, int target_pos) {
  auto &[_1, apods] = s;

  assert(curr_pos > 0);

  for (int i = 0; i < apods.size(); i++) {
    if (i == a) continue;
    auto &[_5, intermediate_pos, _6, _7] = apods[i];
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

void goHallway(state &s, vector<state> &next, int a) {
  auto &[_1, apods] = s;
  auto &[curr_kind, curr_hallway, curr_room, curr_roomposition] = apods[a];
  // int target_room = apodRooms[curr_kind];
  string rdesc = roomDescription(s, curr_room);

  assert(curr_hallway == -1);
  assert(curr_room > 0);
  assert(curr_roomposition >= 0);

  // cout << rdesc[0] << ";";

  if (rdesc == targetRooms[curr_room])  // Locked in a room
    return;

  string tmps = targetRooms[curr_room];
  tmps[0] = 'E';
  if (rdesc == tmps) return;

  if (curr_roomposition == 0) {  // Needs to go out
    for (int hall : hallway) {
      if (canGo(s, a, curr_room, hall)) {
        int cost = apodCost[curr_kind] * (1 + abs(hall - curr_room));
        auto tmp = apods;
        tmp[a] = {curr_kind, hall, -1, -1};
        next.push_back({cost, tmp});
      }
    }
  } else if (curr_roomposition == 1 && rdesc.substr(0, 1) == "E") {
    for (int hall : hallway) {
      if (canGo(s, a, curr_room, hall)) {
        int cost = apodCost[curr_kind] * (2 + abs(hall - curr_room));
        auto tmp = apods;
        tmp[a] = {curr_kind, hall, -1, -1};
        next.push_back({cost, tmp});
      }
    }
  } else if (curr_roomposition == 2 && rdesc.substr(0, 2) == "EE") {
    for (int hall : hallway) {
      if (canGo(s, a, curr_room, hall)) {
        int cost = apodCost[curr_kind] * (3 + abs(hall - curr_room));
        auto tmp = apods;
        tmp[a] = {curr_kind, hall, -1, -1};
        next.push_back({cost, tmp});
      }
    }
  } else if (curr_roomposition == 3 && rdesc.substr(0, 3) == "EEE") {
    for (int hall : hallway) {
      if (canGo(s, a, curr_room, hall)) {
        int cost = apodCost[curr_kind] * (4 + abs(hall - curr_room));
        auto tmp = apods;
        tmp[a] = {curr_kind, hall, -1, -1};
        next.push_back({cost, tmp});
      }
    }
  }

  return;
}

void goRoom(state &s, vector<state> &next, int a) {
  auto &[_1, apods] = s;
  auto &[curr_kind, curr_hallway, curr_room, curr_roomposition] = apods[a];
  assert(curr_hallway > 0);
  assert(curr_room == -1);
  assert(curr_roomposition == -1);

  int target_room = apodRooms[curr_kind];
  string rdesc = roomDescription(s, target_room);
  // printf("Go room curr=%d target=%d(%s)\n", curr_hallway, target_room,
  //        rdesc.c_str());

  // printf("Can GO: %c %d", curr_kind, target_room);
  string tmps = "EEEE";
  // tmps.push_back(curr_kind);

  if (rdesc == tmps && canGo(s, a, curr_hallway, target_room)) {
    int cost = apodCost[curr_kind] * (4 + abs(curr_hallway - target_room));
    auto tmp = apods;
    tmp[a] = {curr_kind, -1, target_room, 3};
    next.push_back({cost, tmp});
  } else {
    tmps[3] = curr_kind;

    if (rdesc == tmps && canGo(s, a, curr_hallway, target_room)) {
      int cost = apodCost[curr_kind] * (3 + abs(curr_hallway - target_room));
      auto tmp = apods;
      tmp[a] = {curr_kind, -1, target_room, 2};
      next.push_back({cost, tmp});
    } else {
      tmps[2] = curr_kind;

      if (rdesc == tmps && canGo(s, a, curr_hallway, target_room)) {
        int cost = apodCost[curr_kind] * (2 + abs(curr_hallway - target_room));
        auto tmp = apods;
        tmp[a] = {curr_kind, -1, target_room, 1};
        next.push_back({cost, tmp});
      } else {
        tmps[1] = curr_kind;

        if (rdesc == tmps && canGo(s, a, curr_hallway, target_room)) {
          int cost =
              apodCost[curr_kind] * (1 + abs(curr_hallway - target_room));
          auto tmp = apods;
          tmp[a] = {curr_kind, -1, target_room, 0};
          next.push_back({cost, tmp});
        }
      }
    }
  }
  return;
}

vector<state> nextStates(state &s) {
  vector<state> out;
  auto &[_1, apods] = s;

  for (int i = 0; i < apods.size(); i++) {
    auto &[kind, hallwaypos, room, roompos] = apods[i];

    vector<state> next;
    if (hallwaypos == -1)
      goHallway(s, out, i);
    else {
      goRoom(s, out, i);
    }
  }

  return out;
}

int h(const vector<apod> &apods) {
  int sum = 0;
  for (const auto &a : apods) {
    const auto &[kind, hallway, room, roompos] = a;
    int targetRoom = apodRooms[kind];

    if (hallway == -1) {  // in room
      sum += abs(room - targetRoom);
    } else {
      sum += abs(hallway - targetRoom);
    }
  }
  return sum;
}

int main() {
  vector<tuple<char, int, int, int>> st0 = {
      {'A', -1, 3, 0}, {'A', -1, 3, 1}, {'A', -1, 3, 2}, {'A', -1, 3, 3},
      {'B', -1, 5, 0}, {'B', -1, 5, 1}, {'B', -1, 5, 2}, {'B', -1, 5, 3},
      {'D', -1, 7, 0}, {'D', -1, 7, 1}, {'C', -1, 7, 2}, {'C', -1, 7, 3},
      {'C', -1, 9, 0}, {'D', -1, 9, 1}, {'D', -1, 9, 2}, {'D', -1, 9, 3},
  };

  // vector<tuple<char, int, int, int>> st0 = {
  //     {'B', -1, 3, 0}, {'D', -1, 3, 1}, {'D', -1, 3, 2}, {'A', -1, 3, 3},
  //     {'C', -1, 5, 0}, {'C', -1, 5, 1}, {'B', -1, 5, 2}, {'D', -1, 5, 3},
  //     {'B', -1, 7, 0}, {'B', -1, 7, 1}, {'A', -1, 7, 2}, {'C', -1, 7, 3},
  //     {'D', -1, 9, 0}, {'A', -1, 9, 1}, {'C', -1, 9, 2}, {'A', -1, 9, 3},
  // };

  // vector<tuple<char, int, int, int>> st = {
  //     {'D', -1, 3, 0}, {'D', -1, 3, 1}, {'D', -1, 3, 2}, {'D', -1, 3, 3},
  //     {'A', -1, 5, 0}, {'C', -1, 5, 1}, {'B', -1, 5, 2}, {'C', -1, 5, 3},
  //     {'C', -1, 7, 0}, {'B', -1, 7, 1}, {'A', -1, 7, 2}, {'B', -1, 7, 3},
  //     {'A', -1, 9, 0}, {'A', -1, 9, 1}, {'C', -1, 9, 2}, {'B', -1, 9, 3},
  // };

  priority_queue<state, vector<state>, greater<state>> pq;
  map<vector<apod>, int> dist;
  // map<vector<apod>, vector<apod>> parent = {{st, st}};

  pq.push({0, st0});

  while (!pq.empty()) {
    auto st = pq.top();
    auto &[_cost, apods] = st;
    int cost = dist[apods];
    // printf("cost: %d\n", cost);
    // print(apods);

    if (isend(apods)) {
      printf("cost=%d, states=%lu", cost, dist.size());
      return 0;
    }

    pq.pop();

    for (auto &next_state : nextStates(st)) {
      auto &[next_cost, next_amphs] = next_state;
      dist.try_emplace(next_amphs, 1e9);
      int curr_cost = dist[next_amphs];

      if (curr_cost > cost + next_cost) {
        dist[next_amphs] = cost + next_cost;
        // parent.try_emplace(next_amphs, apods);
        // parent[next_amphs] = apods;
        int fscore = dist[next_amphs] + h(next_amphs);
        pq.push({fscore, next_amphs});
      }
    }
  }

  // vector<apod> min_apods = st;
  // int min_cost = 1e9;

  // for (auto &[apods, cost] : dist) {
  //   if (isend(apods) && cost < min_cost) {
  //     min_cost = cost;
  //     // min_apods = apods;
  //   }
  // }

  // cout << "min:" << min_cost << endl;

  // vector<apod> next = min_apods;
  // while (next != parent[next]) {
  //   print(next);
  //   next = parent[next];
  // }

  return 0;
}