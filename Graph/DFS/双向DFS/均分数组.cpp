#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

// Created by Simonhancrew on 2022/11/14

using namespace std;

// 首先要均分数组，sum(a) / len(a) == sum(b) / len(b)
// 成比例，因此有sum(a + b) / len(a + b) == sum(a) / len(a)
// 处理平均数均分问题的一个技巧， 将数组中的每个数减去一个avg
// 然后选择的A部分和为sum1,另外的B部分的sum2，能均分数组的话，此时应有sum1 +
// sum2 = 0 A + B是一个数组，另外的补集是一个数组
// 可以用空间换时间，预先处理数组一半中所有可能出现的sum，
// 能够均分的话，另外一半应该出现过-sum
// 此时的空集和全集需要额外考虑

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 35;

int n;
int a[N];
unordered_map<int, int> mp;

void dfs_aft(int u, int n, int sum) {
  if (u == n) {
    mp[sum]++;
    return;
  }
  dfs_aft(u + 1, n, sum);
  dfs_aft(u + 1, n, sum + a[u]);
}

bool dfs_pre(int u, int n, int sum, int cnt) {
  if (u == n) {
    if (cnt && cnt < n && mp[-sum] > 0) {
      return true;
    }
    return false;
  }
  if (dfs_pre(u + 1, n, sum, cnt))
    return true;
  if (dfs_pre(u + 1, n, sum + a[u], cnt + 1))
    return true;
  return false;
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  int sum = accumulate(a, a + n, 0);
  for (int i = 0; i < n; i++)
    a[i] = a[i] * n - sum;
  int mid = n / 2;
  dfs_aft(mid, n, 0);
  int none = 0, full = accumulate(a + mid, a + n, 0);
  // 去掉右边空集，依然出现sum为0的数组和，能均分
  mp[none]--;
  if (mp[0] > 0)
    cout << "YES";
  // 还原，去掉右边全集，左半部分全部的sum在右边出现过-sum，能够均分
  mp[none]++, mp[full]--;
  if (mp[-accumulate(a, a + mid, 0)] > 0)
    cout << "YES";
  // 额外情况，两个部分都选
  if (dfs_pre(0, mid, 0, 0)) {
    cout << "YES" << endl;
  }
  return 0;
}
