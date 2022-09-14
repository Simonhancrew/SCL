#include <cstring>
#include <iostream>

using namespace std;

const int N = 6;

/*
    递推过程中发现只要固定第一行
    上一行的0能且只能被后续的行的开灯变化影响
    从上到下做一个递推，第一行的开灯情况一共有5个位置
    可以做一个二进制枚举
*/

char bg[N][N], g[N][N];

int t;
int dx[5] = {-1, 0, 1, 0, 0}, dy[5] = {0, 1, 0, -1, 0};

void turn(int x, int y) {
  for (int i = 0; i < 5; i++) {
    int nx = x + dx[i], ny = y + dy[i];
    if (nx < 0 || nx >= 5 || ny < 0 | ny >= 5) continue;
    g[nx][ny] ^= 1;
  }
}

int main() {
  cin >> t;
  while (t--) {
    for (int i = 0; i < 5; i++) cin >> bg[i];
    int res = 10;
    // 枚举第一行开灯操作
    for (int i = 0; i < (1 << 5); i++) {
      memcpy(g, bg, sizeof bg);
      int cnt = 0;
      for (int j = 0; j < 5; j++) {
        if (i >> j & 1) {
          turn(0, j);
          cnt++;
        }
      }
      // 利用上行更新下行
      for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 5; k++) {
          if (g[j][k] == '0') {
            turn(j + 1, k);
            cnt++;
          }
        }
      }
      // 判定最后一行状态是否和法
      bool flag = true;
      for (int j = 0; j < 5; j++) {
        if (g[4][j] == '0') {
          flag = false;
          break;
        }
      }
      if (flag && res > cnt) res = cnt;
    }
    if (res > 6)
      cout << -1 << endl;
    else
      cout << res << endl;
  }
  return 0;
}