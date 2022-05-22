#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/05/22

using namespace std;

/*
    LCA + 树上差分
    首先针对树边建树，并求出一个深度值。此时要把整个树拆分成2部分，拆除一条树边之后
    一定要再拆一条非树边。此时假设拆除了一条树边，且在经过这条树边的路径中，没有环的话
    则任意拆除一条非树边就可以了（有环一定是非树边带来的）。否则，如果经过这条边的路径中，可以构成
    一个环的话，在拆除一个确定的非树边就可以完成拆分。如果路径上构成多个环，则无解。
    枚举所有的环复杂度过于大，可以考虑的处理方式是给非树边和树构成的环中的每条树边
    增加一个权值1，这样在处理所有的非树边之后，树边应该有0，1，>1三种权值。
    考虑到环中的值是整体+1的，可以采用一个树上差分的思路。
    即d[a] ++,d[b]++,然后找到p = lca(a,b),d[a] -= 2
    最后dfs结果
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e5 + 10, M = 2 * N;

int n, m;
int h[N], e[M], ne[M], idx;
int depth[N], fa[N][17];
int q[N], d[N];
int ans;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void bfs()
{
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[1] = 1, q[0] = 1;
    int hh = 0, tt = 0;
    while (hh <= tt)
    {
        int t = q[hh++];
        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (depth[j] > depth[t] + 1)
            {
                depth[j] = depth[t] + 1;
                q[++tt] = j;
                fa[j][0] = t;
                for (int k = 1; k <= 16; k++)
                {
                    fa[j][k] = fa[fa[j][k - 1]][k - 1];
                }
            }
        }
    }
}

int lca(int a, int b)
{
    if (depth[a] < depth[b])
        swap(a, b);
    for (int i = 16; i >= 0; i--)
    {
        if (depth[fa[a][i]] >= depth[b])
        {
            a = fa[a][i];
        }
    }
    if (a == b)
        return a;
    for (int i = 16; i >= 0; i--)
    {
        if (fa[a][i] != fa[b][i])
        {
            a = fa[a][i];
            b = fa[b][i];
        }
    }
    return fa[a][0];
}

int dfs(int u, int pa)
{
    int res = d[u];
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (j == pa)
            continue;
        // u->j这条边的权重
        int s = dfs(j, u);
        if (s == 0)
            ans += m;
        else if (s == 1)
            ans++;

        res += s;
    }
    return res;
}

int main()
{
    fast_cin();
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }

    bfs();

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        int p = lca(a, b);
        d[a]++, d[b]++, d[p] -= 2;
    }

    dfs(1, -1);

    cout << ans << endl;

    return 0;
}