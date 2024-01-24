#include <iostream>
#include <stack>
#include <vector>

// Created by Simonhancrew on 2024/01/24

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

// 构造最大的山峰数组，其中要求final[i] <= arr[i]
// 峰值可以等于

vector<int> arr;
int n;

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  arr.reserve(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }
  int n = arr.size();
  stack<int> stk;
  stk.push(-1);
  LL sum = 0;
  vector<LL> pre;
  pre.reserve(n + 1);
  pre.push_back(0);
  for (int i = 0; i < n; i++) {
    while (stk.size() > 1 && arr[i] <= arr[stk.top()]) {
      int j = stk.top();
      stk.pop();
      sum -= (LL)arr[j] * (j - stk.top());
    }
    sum += (LL)arr[i] * (i - stk.top());
    stk.push(i);
    pre.push_back(sum);
  }
  sum    = 0;
  LL ans = 0;
  stk    = stack<int>{};
  stk.push(n);
  for (int i = n - 1; i >= 0; i--) {
    while (stk.size() > 1 && arr[i] <= arr[stk.top()]) {
      int j = stk.top();
      stk.pop();
      sum -= (LL)arr[j] * (stk.top() - j);
    }
    sum += (LL)arr[i] * (stk.top() - i);
    stk.push(i);
    ans = max(ans, sum + pre[i]);
  }
  cout << ans << '\n';
  return 0;
}
