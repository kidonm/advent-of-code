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

map<int, string> opMap = {{0, "+"}, {1, "*"}, {2, "min"}, {3, "max"},
                          {5, ">"}, {6, "<"}, {7, "=="},  {4, ""}};

struct packet_expr {
  int version = -1;
  int type = -1;
  ull lit = 0;
  vector<packet_expr *> children;

  void print() { print(""); }

  void print(string offset) {
    printf("%s", offset.c_str());
    if (type != 4) {
      printf("%s\n", opMap[type].c_str());
    } else {
      printf("%llu\n", lit);
    }

    for (packet_expr *child : children) {
      child->print(offset + "  ");
    }
  }

  int header() {
    int ans = version;
    for (packet_expr *child : children) {
      ans += child->header();
    }

    return ans;
  }

  ull eval(string offset) {
    ull ans = 0;
    offset += " ";
    if (type == 1)
      ans = 1;
    else if (type == 2)
      ans = -1;
    else if (type == 3)
      ans = 0;
    else if (type == 4) {
      printf("%s%llu\n", offset.c_str(), lit);
      return lit;
    } else if (type == 5)
      ans = children[0]->eval(offset) > children[1]->eval(offset);
    else if (type == 6)
      ans = children[0]->eval(offset) < children[1]->eval(offset);
    else if (type == 7)
      ans = children[0]->eval(offset) == children[1]->eval(offset);

    for (packet_expr *expr : children) {
      if (type == 5 || type == 6 || type == 7) continue;
      ull sub = expr->eval(offset);

      if (type == 0)
        ans += sub;
      else if (type == 1)
        ans *= sub;
      else if (type == 2)
        ans = min(ans, sub);
      else if (type == 3)
        ans = max(ans, sub);
    }

    printf("%s%s (%llu)\n", offset.c_str(), opMap[type].c_str(), ans);

    return ans;
  }
};

typedef unsigned long long ull;

unordered_map<string, int> rOctmap = {
    {"000", 0}, {"001", 1}, {"010", 2}, {"011", 3},
    {"100", 4}, {"101", 5}, {"110", 6}, {"111", 7},
};

unordered_map<char, string> hexmap = {
    {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
    {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
    {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
    {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}};

int parse(int pos, string &input, packet_expr *out);

ull parseBin(string input) {
  ull ans = 0;

  // printf("%s\n", input.substr(pos, take).c_str());

  for (char c : input) {
    // printf("%d %c", ans, input[i] - 48);
    ans |= (c - 48);
    ans *= 2;
  }
  ans /= 2;
  // printf("\n");

  return ans;
}

int parseLit(int pos, string &input, string &buf) {
  // printf("parselit: %s\n", input.substr(pos).c_str());
  buf += input.substr(pos + 1, 4);
  if (input[pos] == '1') return parseLit(pos + 5, input, buf);

  return pos + 5;
}

int parseOp(int pos, string &input, packet_expr *out) {
  // printf("parse op: %s\n", input.substr(pos).c_str());
  if (input[pos] == '0') {
    pos++;
    int subLen = parseBin(input.substr(pos, 15));
    pos += 15;
    int tmp = pos;
    while (pos < tmp + subLen) {
      pos = parse(pos, input, out);
    }
  } else {
    pos++;
    int subPackets = parseBin(input.substr(pos, 11));
    pos += 11;
    for (int i = 0; i < subPackets; i++) {
      pos = parse(pos, input, out);
    }
  }
  return pos;
}

int parse(int pos, string &input, packet_expr *out) {
  // printf("parse:    %s\n", input.substr(pos).c_str());
  int version = rOctmap[input.substr(pos, 3)];
  pos += 3;
  int type = rOctmap[input.substr(pos, 3)];
  pos += 3;

  packet_expr *p = new packet_expr;

  out->children.push_back(p);

  p->version = version;
  p->type = type;

  if (type == 4) {
    string buf;
    pos = parseLit(pos, input, buf);
    p->lit = parseBin(buf);
    // printf("parsed lit %s, %llu\n", buf.c_str(), p->lit);
    // out.push_back(p);
  } else {
    // out.push_back(p);
    pos = parseOp(pos, input, p);
  }

  return pos;
}

int main() {
  string s;
  getline(cin, s);

  // string s = "C200B40A82";

  string input;
  for (char c : s) {
    string bits = hexmap[c];
    input += bits;
  }

  // printf("%s\n", input.c_str());
  packet_expr out;
  parse(0, input, &out);

  // out.children[0]->print();
  printf("%llu\n", out.children[0]->eval(""));

  // int sum = 0;
  // for (packet p : out) {
  //   sum += p.version;
  //   printf("version: %d type: %d lit: %d \n", p.version, p.type, p.lit);
  // }
  // printf("sum %d\n", sum);

  return 0;
}
