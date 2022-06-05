#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/05/30

using namespace std;

/*
    等价转换成加多少边才能让图双连通=>先缩点成树，看看有多少叶子节点
    给叶子节点加边就可以了，假设有cnt个叶子节点的话，需要的加边就是(cnt + 1) / 2做一个上取整
    这里可以总结一下给有向图和无向图转成强连通的加边值：
    1. 有向图就是max(p,q)，p和q分别是入度和出度是1的点
    2. 无向图的加边就是(cnt + 1) / 2,cnt可以用缩点之后入度是1的求
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 5e3 + 10, M = 2e4 + 10;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
int id[N], dcc_cnt;
bool is_bridge[M];
int d[N]; //记录一个入度

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void tarjan(int u, int from)
{
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u;

    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j, i);
            low[u] = min(low[u], low[j]);
            // 无论如何儿子都走不到爹，这就是座桥，正反向都要标记
            if (dfn[u] < low[j])
            {
                // 0,1（idx）是一对边，正方向，都标记一下。
                is_bridge[i] = is_bridge[i ^ 1] = true;
            }
        }
        // 不是反向边的话
        else if (i != (from ^ 1))
        {
            low[u] = min(low[u], dfn[j]);
        }
    }

    if (dfn[u] == low[u])
    {
        int y;
        ++dcc_cnt;
        do
        {
            y = stk[top--];
            id[y] = dcc_cnt;
        } while (y != u);
    }
}

int main()
{
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    fast_cin();
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }

    tarjan(1, -1);

    for (int i = 0; i < idx; i++)
    {
        if (is_bridge[i])
        {
            int shrink = id[e[i]];
            d[shrink]++;
        }
    }

    int cnt = 0;
    for (int i = 1; i <= dcc_cnt; i++)
    {
        if (d[i] == 1)
            cnt++;
    }

    cout << (cnt + 1) / 2 << endl;

    return 0;
}