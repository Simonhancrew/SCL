#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

// Created by Simonhancrew on 2022/09/21

using namespace std;

// 类似于这种s1串和s2串的字母集一致，但是排列不等
// 要找到最小的s1交换方式，使得s1 == s2
// 等价于一个图论问题，s1和s2的每个位置的字母建立一条连接边
// 举个例子，ab,ba,则连接a->b,b->a的边
// 要让s1 == s2，一个结论就是要在一个环内拆更多的环，集体形成自环就是最终解。
// 注意可能有重复，第一个不一样的换就行了
// 因此这类问题可以考虑迭代加深 +
// 启发式，因为总的不对应数已经确定了，需要换的次数的下限确定
// 就是ceil(cnt /2),cnt是不等的位置数

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

string s1, s2;
int n;

int f(string &s1, string &s2) {
  int res = 0;
  for (int i = 0; i < n; i++) {
    if (s1[i] != s2[i])
      res++;
  }
  return (res + 1) / 2;
}

bool dfs(string &s1, string &s2, int dep) {
  if (!dep)
    return s1 == s2;
  if (f(s1, s2) > dep)
    return false;
  for (int i = 0; i < n; i++) {
    if (s1[i] != s2[i]) {
      for (int j = i + 1; j < n; j++) {
        if (s2[i] == s1[j]) {
          swap(s1[i], s1[j]);
          if (dfs(s1, s2, dep - 1)) {
            return true;
          }
          swap(s1[i], s1[j]);
        }
      }
      break;
    }
  }
  return false;
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> n;
  cin >> s1;
  cin >> s2;
  int dep = 1;
  while (!dfs(s1, s2, dep))
    dep++;
  cout << dep << '\n';
  return 0;
}