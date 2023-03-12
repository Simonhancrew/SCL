#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2023/03/12

using namespace std;

// 可以看成求高度问题的进阶,求完高度之后求一个直径

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e3;

int n;
int tr[N];
int ans = 1;

using Node = int;

int dfs(Node root) {
  if (root > n) {
    return 0;
  }
  int left = dfs(root * 2);
  int right = dfs(root * 2 + 1);
  ans = max(ans, left + right + 1);
  return max(left, right) + 1;
}

void solve(Node root) {
  dfs(root);
  cout << ans - 1 << endl;
}

int main() {
  freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  for (int i = 1;i <= n;i++) {
    cin >> tr[i];
  }
  solve(tr[1]);
  return 0;
}