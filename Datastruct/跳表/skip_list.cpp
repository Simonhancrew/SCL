#include <iostream>
#include <random>
#include <vector>
using namespace std;
/*
    一个跳表的实现。一个节点可以理解成一个矩形区域，会按照一定概率覆盖一个高度
*/
static const int kMaxLevel = 8;

struct Node {
  int val_;
  vector<Node *> next_;
  Node(int val) : val_(val), next_(kMaxLevel, nullptr) {}
};

class Skiplist {
 public:
  Node *head_;
  Skiplist() { head_ = new Node(-1); }

  vector<Node *> find(int target) {
    vector<Node *> pre(kMaxLevel, nullptr);
    auto p = head_;
    for (int i = kMaxLevel - 1; i >= 0; i--) {
      while (p->next_[i] && p->next_[i]->val_ < target) p = p->next_[i];
      pre[i] = p;
    }
    return pre;
  }

  bool search(int target) {
    auto pre = find(target);
    auto p = pre[0]->next_[0];
    return p && p->val_ == target;
  }

  void add(int num) {
    auto pre = find(num);
    auto p = new Node(num);
    for (int i = 0; i < kMaxLevel; i++) {
      p->next_[i] = pre[i]->next_[i];
      pre[i]->next_[i] = p;
      if (rand() % 2) break;
    }
  }

  bool erase(int num) {
    auto pre = find(num);
    auto p = pre[0]->next_[0];
    if (!p || p->val_ != num) return false;

    for (int i = 0; i < kMaxLevel && pre[i]->next_[i] == p; i++) {
      pre[i]->next_[i] = p->next_[i];
    }
    delete p;
    return true;
  }
};

int main() {
  Skiplist slt;
  slt.add(3);
  slt.add(5);
  slt.add(6);
  cout << slt.search(6) << endl;
  cout << slt.search(3) << endl;
  cout << slt.search(5) << endl;
  slt.erase(5);
  slt.erase(6);
  cout << slt.search(6) << endl;
  cout << slt.search(5) << endl;
}