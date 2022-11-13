#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

// Created by Simonhancrew on 2022/11/13

using namespace std;

// 置换环问题，找到不一致的环，交换次数就是环大小 - 1

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

int n;

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  vector<PII> arr(n);
  for(int i = 0;i < n;i++) {
    cin >> arr[i].first;
    arr[i].second = i;
  }
  sort(arr.begin(), arr.end());
  vector<int> vis(n, 0);
  int ans = 0;
  for(int i = 0;i < n;i++) {
    if(vis[i] || arr[i].second == i) continue;
    int cycle = 0, j = i;
    while(!vis[j]) {
      vis[j] = 1;
      j = arr[j].second;
      cycle++;
    }
    if(cycle > 0) {
      ans += cycle - 1;
    }
  }
  cout << ans << endl;
  return 0;
}