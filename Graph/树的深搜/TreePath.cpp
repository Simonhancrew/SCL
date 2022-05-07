#include <iostream>
#include <cstring>

using namespace std;
using LL = long long;

#define fast_cin()               \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0)

/*
    不考虑点分治的做法，因为只考虑距离是偶数的边，可以采用一个染色的思路
    根节点为黑色，跟root想连接的被染成白色，后续和白色连接的被染成黑色
    偶数距离的节点在染色之后颜色是相同的，随后做一个组合数选择即可
*/

const int N = 1e5 + 10, M = 2 * N;

int n, x, y;
int h[N], ne[M], e[M], idx;
LL f[2];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u, int fa, int dep)
{
    f[dep]++;
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (j == fa)
            continue;
        dfs(j, u, dep ^ 1);
    }
}

int main()
{
    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 1; i < n; i++)
    {
        cin >> x >> y;
        add(x, y), add(y, x);
    }
    dfs(1, -1, 1);
    cout << f[0] * (f[0] - 1) / 2 + f[1] * (f[1] - 1) / 2 << endl;
}