#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/04/27

using namespace std;

/*
    需要深入理解kruskal
    本题要求去掉不必要的边，等价于求解最小生成森林的代价
    kruskal比较好求解这类问题，不需要考虑一个完全的生成树
    遍历边权就行了，某次u，v同属一个集合的时候，表明当前
    两点在之前已经加过了，这条边属于冗余边，直接加上就ok
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 110, M = 210;

int n, m, p[N];
struct Edge
{
    int u, v, w;
} e[M];

int find(int x)
{
    if (x != p[x])
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

    int res = 0;
    for (int i = 0; i < m; i++)
    {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        u = find(u), v = find(v);
        if (u != v)
            p[u] = v;
        else
            res += w;
    }

    cout << res << endl;

    return 0;
}