#include <iostream>
#include <numeric>

using namespace std;

const int N = 1e5 + 10;
int p[N];

int find(int x) {
  if (p[x] != x) p[x] = find(p[x]);
  return p[x];
}

int main() {
  int m, n;
  scanf("%d%d", &n, &m);
  iota(p + 1, p + n + 1, 1);

  while (m--) {
    char op[2];
    int a, b;
    scanf("%s%d%d", op, &a, &b);
    if (op[0] == 'M')
      p[find(a)] = find(b);
    else {
      if (find(a) == find(b))
        puts("Yes");
      else
        puts("No");
    }
  }

  return 0;
}
