#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 67;

int w[N];
int n;
int sum, length;
bool st[N];

/*
    当前多少个棍子，当前拼接棍子长度，组合型枚举
*/
bool dfs(int cnt, int len, int start) {
  if (cnt * length == sum) return true;
  if (len == length) return dfs(cnt + 1, 0, 0);
  for (int i = start; i < n; i++) {
    // 可行剪枝，没用过，且长度要能拼进去
    if (st[i]) continue;
    if (len + w[i] > length) continue;

    st[i] = true;
    if (dfs(cnt, len + w[i], i + 1)) return true;
    st[i] = false;

    /*
        3 加入当前拼的棍子下，w[i]失败了，剩下的一定也拼不成
        假设能拼成的话，可以讲w[i]调换到拼接头部，和当前拼接的棍子
        swap，和之前拼不成的情况相冲突
        同理，最后一个失败了也不行
    */
    if (!len) return false;
    if (len + w[i] == length) return false;

    /*
        4 当前长度的没有拼成，剩下的和当前长度相等的也拼不成
    */
    int j = i;
    while (j < n && w[i] == w[j]) j++;
    i = j - 1;
  }
  return false;
}

int main() {
  while (cin >> n, n != 0) {
    sum = 0;
    memset(st, 0, sizeof st);
    for (int i = 0; i < n; i++) {
      cin >> w[i];
      sum += w[i];
    }
    // 1 优先遍历分支更少的
    sort(w, w + n, [](int lhs, int rhs) { return lhs > rhs; });

    // 2 可行性剪枝,单根棍子必须是总长的约数
    length = 1;
    while (true) {
      if (sum % length == 0 && dfs(0, 0, 0)) {
        cout << length << endl;
        break;
      }
      length++;
    }
  }
  return 0;
}