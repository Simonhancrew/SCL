#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/04/28

using namespace std;

/*
    先挑选必须连接的，并构建一个最小生成森林
    随后挑选可选的，构建一个最小生成树。
    kruskal非常合适
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 2010, M = 1e4 + 10;

struct Edge
{
    int u, v, w;
} e[M];

int n, m;
int p[N];

int find(int x)
{
    if (p[x] != x)
    {
        p[x] = find(p[x]);
    }
    return p[x];
}

int main()
{
    fast_cin();
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        p[i] = i;

    int cnt = 0, res = 0;
    for (int i = 0; i < m; i++)
    {
        int u, v, w, k;
        cin >> k >> u >> v >> w;
        if (k == 1)
        {
            res += w;
            p[find(u)] = find(v);
        }
        else
        {
            e[cnt++] = {u, v, w};
        }
    }

    sort(e, e + cnt, [](Edge &lhs, Edge &rhs)
         { return lhs.w < rhs.w; });

    for (int i = 0; i < cnt; i++)
    {
        // cout << e[i].u << ' ' << e[i].v << ' ' << e[i].w << endl;
        int u = find(e[i].u), v = find(e[i].v);
        int w = e[i].w;
        if (u != v)
        {
            p[u] = v;
            res += w;
        }
    }
    cout << res << endl;
    return 0;
}