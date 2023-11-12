#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

/*
  动态开点的两种写法，第一种是要估计点数的
  第二种直接new开点
*/

#ifdef ALLOC_ALL

// 这里写的是区间重复覆盖的最大次数,不是对每个线段做整体+

const int N = 1e6 + 10;
int cnt     = 1;

struct Node {
  // 左右儿子 + 当前要求的值 + lazy_tag
  int ls, rs, val, tag;
  int l, r;
  Node() {
    l = r = rs = ls = val = tag = 0;
  }
  Node(int l, int r) : l(l), r(r), ls(0), rs(0), val(0), tag(0) {
  }
};

Node tr[N];

void lazy_create(int u) {
  int mid = tr[u].l + tr[u].r >> 1;
  if (tr[u].ls == 0) {
    tr[u].ls       = ++cnt;
    tr[tr[u].ls].l = tr[u].l;
    tr[tr[u].ls].r = mid;
  }
  if (tr[u].rs == 0) {
    tr[u].rs       = ++cnt;
    tr[tr[u].rs].l = mid + 1;
    tr[tr[u].rs].r = tr[u].r;
  }
}

void push_down(int u) {
  if (tr[u].tag) {
    int &tag = tr[u].tag;
    tr[tr[u].ls].val += tag;
    tr[tr[u].rs].val += tag;
    tr[tr[u].ls].tag += tag;
    tr[tr[u].rs].tag += tag;
    tag = 0;
  }
}

void push_up(int u) {
  int lhs = tr[u].ls, rhs = tr[u].rs;
  tr[u].val = max(tr[lhs].val, tr[rhs].val);
}

void add(int u, int L, int R, int k) {
  if (tr[u].l >= L && tr[u].r <= R) {
    tr[u].val += k;
    tr[u].tag += k;
    return;
  }
  lazy_create(u);
  push_down(u);
  int mid = tr[u].l + tr[u].r >> 1;
  if (mid >= L)
    add(tr[u].ls, L, R, k);
  if (mid < R)
    add(tr[u].rs, L, R, k);
  push_up(u);
}

int query(int u, int L, int R) {
  if (tr[u].l >= L && tr[u].r <= R) {
    return tr[u].val;
  }
  lazy_create(u);
  push_down(u);
  int mid = tr[u].l + tr[u].r >> 1;
  int ans = 0;
  if (mid >= L)
    ans = max(ans, query(tr[u].ls, L, R));
  if (mid < R)
    ans = max(ans, query(tr[u].rs, L, R));
  return ans;
}

#endif

// 维护一个数组区间，动态区间求和，区间更改
class SegTree {
 public:
  SegTree(int kL, int kR) : l_(kL), r_(kR) {
  }

  void PushDown() {
    if (tag_ == 0 || l_ == r_) {
      return;
    }
    int mid = l_ + r_ >> 1;
    if (!lhs_) {
      lhs_ = make_unique<SegTree>(l_, mid);
    }
    if (!rhs_) {
      rhs_ = make_unique<SegTree>(mid + 1, r_);
    }
    // 更新值
    lhs_->val_ += tag_;
    rhs_->val_ += tag_;
    // 更新lazy_tag!
    rhs_->tag_ += tag_;
    lhs_->tag_ += tag_;
    tag_ = 0;
  }

  void PushUp() {
    val_ = lhs_->val_ + rhs_->val_;
  }

  void Update(int kL, int kR, int val) {
    if (kL <= l_ && kR >= r_) {
      val_ += val;
      tag_ += val;
      return;
    }
    PushDown();
    int mid = l_ + r_ >> 1;
    if (!lhs_) {
      lhs_ = make_unique<SegTree>(l_, mid);
    }
    // 有区间交集才考虑update
    if (mid >= kL) {
      lhs_->Update(kL, kR, val);
    }
    if (!rhs_) {
      rhs_ = make_unique<SegTree>(mid + 1, r_);
    }
    // 有区间交集才考虑update
    if (mid < kR) {
      rhs_->Update(kL, kR, val);
    }
    PushUp();
  }

  int Query(int kL, int kR) {
    if (kL <= l_ && kR >= r_) {
      return val_;
    }
    PushDown();
    auto ans = 0;
    int mid  = l_ + r_ >> 1;
    if (mid >= kL) {
      ans += lhs_->Query(kL, kR);
    }
    if (mid < kR) {
      ans += rhs_->Query(kL, kR);
    }
    return ans;
  }

 private:
  unique_ptr<SegTree> lhs_{}, rhs_{};
  int val_{};
  int tag_{};
  int l_{}, r_{};
};

