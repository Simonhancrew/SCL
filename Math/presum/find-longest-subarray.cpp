#include <algorithm>
#include <cstring>
#include <iostream>
#include <unordered_map>

// Created by Simonhancrew on 2023/03/11

using namespace std;

// 数组种只有两种字符, 这个时候求子数组内两数相等就可以通过
// 前缀和处理, 化为+1和-1, 此时只要f[i + 1] - f[j] == 0就是一个合法的子数组
// 要下标最小的话多记录一个当前前缀和第一次出现的地址

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e5 + 10;

int n;
char str[N];

// 20
// A 1 B C D 2 3 4 E 5 F G 6 7 H I J K L M 

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  int presum = 0, mx = 0, start = 0;
  for (int i = 0;i < n;i++) cin >> str[i];
  unordered_map<int, int> mp;
  mp[0] = -1;
  for (int i = 0;i < n;i++) {
    if (isalpha(str[i])) {
      presum++;
    } else {
      presum--;
    }
    if (mp.count(presum)) {
      int cur = i - mp[presum];
      if (cur > mx) {
        mx = cur;
        start = mp[presum] + 1;
      }
    } else {
      mp[presum] = i;
    }
  }
  if (mx == 0) {
    cout << "[]" << endl;
    return 0;
  }
  for (int i = 0;i < mx;i++) {
    cout << str[i + start] << ' ';
  }
  return 0;
}