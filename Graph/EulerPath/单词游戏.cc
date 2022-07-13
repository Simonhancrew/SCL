#include <cstring>
#include <iostream>

using namespace std;

/*
  建图之后是个有向图，首位完全相连，等价于一个欧拉路径。
  满足两个条件就够了，第一个是有边的点全部连通，
  第二个是满足欧拉路径，此时图中奇数度数的点要么只有起点和终点，
  要么没有，构成一个欧拉回路，做一个判断就可以。
  然后出现过的点要全部属于一个集，这个可以用并查集做
*/

int p[30];
int din[30], dout[30];
bool st[30];

int find(int x) {
  if (p[x] != x)
    p[x] = find(p[x]);
  return p[x];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    memset(din, 0, sizeof din);
    memset(dout, 0, sizeof dout);
    memset(st, 0, sizeof st);
    int n;
    cin >> n;
    for (int i = 0; i < 26; i++)
      p[i] = i;
    for (int i = 0; i < n; i++) {
      string s;
      cin >> s;
      int a = s[0] - 'a', b = s.back() - 'a';
      st[a] = st[b] = true;
      din[b]++, dout[a]++;
      p[find(a)] = find(b);
    }

    bool flag = true;
    int start = 0, tail = 0;

    for (int i = 0; i < 26; i++) {
      if (din[i] != dout[i]) {
        if (din[i] == dout[i] + 1)
          tail++;
        else if (din[i] + 1 == dout[i])
          start++;
        else {
          flag = false;
          break;
        }
      }
    }

    if (flag && !(!start && !tail || tail == 1 && start == 1))
      flag = false;

    int pa = -1;

    for (int i = 0; i < 26; i++) {
      if (st[i]) {
        if (pa == -1)
          pa = find(i);
        else if (pa != find(i)) {
          flag = false;
          break;
        }
      }
    }

    if (flag)
      cout << "Ordering is possible.\n";
    else
      cout << "The door cannot be opened.\n";
  }
}