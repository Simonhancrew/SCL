#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/05/02

using namespace std;

/*
    求解次小生成树的方法
    次小生成树和最小生成树只差一条边，首先通过kruskal求解
    一个最小生成树，随后通过这棵树初始化每个点到其余点的路径上的最大边
    和次大边。可以通过一个dfs做出路径上的最大边和严格次大边

    遍历所有没有在树中的边(u->v)，如果当前边大于u->v的最大值，则可以替换
    如果大于次大值，也可以考虑替换。
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 510, M = 1e4 + 10;

int n, m;
int p[N];
int dist1[N][N], dist2[N][N];
int h[N], e[N * 2], w[N * 2], ne[N * 2], idx; // 最小生成树最少有n - 1条边

struct edge
{
    int u, v, w;
    bool in;
} eg[M];

int find(int x)
{
    if (p[x] != x)
    {
        p[x] = find(p[x]);
    }
    return p[x];
}

void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void dfs(int u, int fa, int maxd1, int maxd2, int d1[], int d2[])
{
    d1[u] = maxd1, d2[u] = maxd2;
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (j != fa)
        {
            int td1 = maxd1, td2 = maxd2;
            if (w[i] > td1)
                td2 = td1, td1 = w[i];
            else if (w[i] < td1 && w[i] > td2) // 严格次小边
                td2 = w[i];
            dfs(j, u, td1, td2, d1, d2);
        }
    }
}

int main()
{
    fast_cin();
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++)
        p[i] = i;
    for (int i = 0; i < m; i++)
    {
        cin >> eg[i].u >> eg[i].v >> eg[i].w;
    }

    sort(eg, eg + m, [](edge &l, edge &r)
         { return l.w < r.w; });

    LL sum = 0;
    for (int i = 0; i < m; i++)
    {
        int u = eg[i].u, v = eg[i].v, w = eg[i].w;
        int pu = find(u), pv = find(v);
        if (pu != pv)
        {
            p[pu] = pv;
            sum += w;
            eg[i].in = true;
            add(u, v, w), add(v, u, w);
        }
    }

    for (int i = 1; i <= n; i++)
        dfs(i, -1, -1e9, -1e9, dist1[i], dist2[i]);
    LL res = 1e18;
    for (int i = 0; i < m; i++)
    {
        if (eg[i].in)
            continue;
        int u = eg[i].u, v = eg[i].v, w = eg[i].w;
        if (w > dist1[u][v])
            res = min(res, sum + w - dist1[u][v]);
        else if (w > dist2[u][v])
            res = min(res, (LL)sum + w - dist2[u][v]);
    }
    cout << res << endl;
    return 0;
}