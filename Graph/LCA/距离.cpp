#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

// Created by Simonhancrew on 2022/05/18

using namespace std;

/*
    求解书中两节点之间的最短距离，涉及到一个LCA的应用公式
    d(u,v) = d(u,root) + d(v,root) - 2 * d(anc,root)，其中anc = LCA(u,v)
    这里考虑一个离线tarjan求LCA的方法，将DFS搜索的节点分类，未搜索过的节点状态是0，正在搜索，没有完全结束的是1
    已经搜索结束回溯的是2。
    在某次DFS中，查询边的另一个结点也恰好访问过了，则直接更新查询边的 LCA 结果。
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e4 + 10;

int n, m;
int h[N], e[2 * N], ne[2 * N], w[2 * N], idx;
int dist[N], st[N], p[N];
int res[N * 2];
vector<PII> query[N];

void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

int find(int x)
{
    if (p[x] != x)
        p[x] = find(p[x]);
    return p[x];
}

void dfs(int u, int fa)
{
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (j == fa)
            continue;
        dist[j] = dist[u] + w[i];
        dfs(j, u);
    }
}

void tarjan(int u)
{
    st[u] = 1; // 正在搜索
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!st[j]) // 没搜过才继续
        {
            tarjan(j);
            p[j] = u; // 节点到根
        }
    }
    for (auto item : query[u])
    {
        int v = item.first, id = item.second; // u<->v,查询id
        if (st[v] == 2)
        {
            int anc = find(v);
            res[id] = dist[u] + dist[v] - 2 * dist[anc];
        }
    }
    st[u] = 2;
}

int main()
{
    fast_cin();
    cin >> n >> m;

    memset(h, -1, sizeof h);
    for (int i = 1; i < n; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }

    dfs(1, -1);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        if (a != b)
        {
            query[a].push_back({b, i});
            query[b].push_back({a, i});
        }
    }

    for (int i = 1; i <= n; i++)
        p[i] = i;
    tarjan(1);
    for (int i = 0; i < m; i++)
        cout << res[i] << endl;

    return 0;
}