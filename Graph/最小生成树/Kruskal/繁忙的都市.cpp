#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/04/28

using namespace std;

/*
    等价于生成的时候最大边权最小
    满足三点要求：
        1 + 2. 一个最小生成树
        3. 满足前置要求下，当前最大的边权最小
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 310, M = 8e3 + 10;

int n, m;
int p[N];

struct Edge
{
    int u, v, w;
} e[M];

int find(int x)
{
    if (p[x] != x)
        p[x] = find(p[x]);
    return p[x];
}

int main()
{
    fast_cin();
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        p[i] = i;
    for (int i = 0; i < m; i++)
    {
        cin >> e[i].u >> e[i].v >> e[i].w;
    }

    sort(e, e + m, [](Edge &lhs, Edge &rhs)
         { return lhs.w < rhs.w; });

    int res = 0, cnt = 0;
    for (int i = 0; i < m; i++)
    {
        int u = find(e[i].u), v = find(e[i].v);
        int w = e[i].w;
        if (u != v)
        {
            p[u] = v;
            res = w;
            cnt++;
        }
    }

    cout << cnt << ' ' << res << endl;

    return 0;
}