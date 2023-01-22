#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <map>

// Created by Simonhancrew on 2023/01/22

using namespace std;

// from lc 1815
// 只和mod的余数有关，先去掉整除的，然后去掉能打包整除的
// 剩下的部分需要整体考虑得到最优解，做一个记忆化搜索

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 35;

int p, n;
map<vector<int>, int> mp;
vector<int> cnt;

int dfs(int pre) {
  if (mp.count(cnt)) {
    return mp[cnt];
  }
  int ans = 0;
  for (int i = 1;i < p;i++) {
    if (cnt[i]) {
      cnt[i]--;
      ans = max(ans, (pre == 0) + dfs((pre + i) % p));
      cnt[i]++;
    }
  }
  return mp[cnt] = ans;
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> p >> n;
  int base = 0;
  cnt.resize(p);
  for (int i = 0;i < n;i++) {
    int t;
    cin >> t;
    int mod = t % p;
    if (mod == 0) {
      base++;
    } else if (cnt[p - mod] > 0) {
      cnt[p - mod]--;
      base++; 
    } else {
      cnt[mod]++;
    }
  }
  cout << base + dfs(0) << '\n';
  return 0;
}
