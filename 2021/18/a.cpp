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

class Tree {
 public:
  int i = -1;
  Tree *parent = nullptr;
  Tree *l = nullptr;
  Tree *r = nullptr;

  Tree() : i(-1), l(nullptr), r(nullptr), parent(nullptr){};
  Tree(int _i) : i(_i){};

  void print() {
    if (i == -1 && l != nullptr && r != nullptr) {
      // printf("{%d}[", lvl);
      printf("[");
      l->print();
      printf(",");
      r->print();
      printf("]");
    } else {
      printf("%d", i);
    }
  }

  bool explode(int lvl) {
    if (i != -1) {
      return false;
    } else if (lvl > 4 && (l->i != -1 || r->i != -1)) {
      // printf("to explode %d %d\n", l->i, r->i);
      parent->distributeUp(true, l->i, this);
      // printf("to exploded r\n");
      parent->distributeUp(false, r->i, this);
      i = 0;
      // delete l;
      // delete r;
      // l = nullptr;
      // r = nullptr;
      // printf("exploded ");
      return true;
    } else {
      return l->explode(lvl + 1) || r->explode(lvl + 1);
    }
  }

  bool split() {
    if (i == -1) {
      return l->split() || r->split();
    } else if (i > 9) {
      int half = i / 2;
      l = new Tree(half);
      if (i % 2 == 0) {
        r = new Tree(half);
      } else {
        r = new Tree(half + 1);
      }
      r->parent = this;
      l->parent = this;
      i = -1;
      // printf("split    ");
      return true;
    } else {
      return false;
    }
  }

  Tree *add(Tree *r) {
    Tree *ret = new Tree();

    ret->l = this;
    ret->r = r;

    ret->l->parent = ret;
    ret->r->parent = ret;

    return ret;
  }

  int mag() {
    if (i == -1) {
      return (3 * l->mag()) + (2 * r->mag());
    } else {
      return i;
    }
  }

 private:
  void distributeDown(bool left, int num) {
    Tree *child = left ? l : r;
    if (i == -1)
      child->distributeDown(left, num);
    else {
      i += num;
    }
  }

  void distributeUp(bool left, int num, Tree *prev) {
    // printf("distribute up %d %d\n", r, parent);
    Tree *child = left ? l : r;
    if (prev == child) {
      if (parent != nullptr) {
        parent->distributeUp(left, num, this);
      }
    } else {
      child->distributeDown(!left, num);
    }
  }
};

Tree *parse(stringstream &s) {
  Tree *tree = new Tree();
  if (s.peek() == '[') {
    s.ignore();
    Tree *l = parse(s);
    s.ignore();
    Tree *r = parse(s);
    s.ignore();

    l->parent = tree;
    tree->l = l;
    r->parent = tree;
    tree->r = r;
  } else {
    int num;
    s >> num;
    tree->i = num;
  }
  return tree;
};

int main() {
  string s;
  getline(cin, s);
  // stringstream
  //     sss("[[[[5,11],[13,0]],[[8,[7,7]],[[7,9],[5,0]]]],[[2,[[0,8],[3,4]]],[[["
  //         "6,7],"
  //         "1],[7,[1,6]]]]]");
  stringstream sss(s);
  Tree *expr = parse(sss);
  // expr->print();
  // printf("\n");
  // expr->explode(1);
  // expr->print();
  // return 0;

  for (; getline(cin, s);) {
    stringstream ss(s);
    Tree *next = parse(ss);
    expr = expr->add(next);
    // printf("\nadd      ");
    // expr->print();
    // printf("\n");
    while (expr->explode(1) || expr->split()) {
      // expr->print();
      // printf("\n");
    }
    // printf("\n");
    // expr->print();
  }
  printf("%d", expr->mag());

  return 0;
}
