#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/05/28

using namespace std;

/*
    求一个强连通然后缩点，看出入度就可以了
    等价加几条边让缩点之后的图变成强连通，看看多少个起点和多少个终点就可以了
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 110, M = N * N;

int n;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], in_stk[N], top;
int scc_cnt, id[N];
int dout[N], din[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void tarjan(int u)
{
    low[u] = dfn[u] = ++timestamp;
    stk[++top] = u, in_stk[u] = true;

    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        else if (in_stk[j])
        {
            low[u] = min(low[u], dfn[j]);
        }
    }

    if (dfn[u] == low[u])
    {
        int y;
        scc_cnt++;
        do
        {
            y = stk[top--];
            id[y] = scc_cnt;
            in_stk[y] = false;
        } while (y != u);
    }
}

int main()
{
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    fast_cin();
    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++)
    {
        int t;
        while (cin >> t, t)
        {
            add(i, t);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (!dfn[i])
        {
            tarjan(i);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = h[i]; j != -1; j = ne[j])
        {
            int a = id[i], b = id[e[j]];
            if (a != b)
            {
                din[b]++;
                dout[a]++;
            }
        }
    }

    int res1 = 0, res2 = 0;
    for (int i = 1; i <= scc_cnt; i++)
    {
        if (!din[i])
            res1++;
        if (!dout[i])
            res2++;
    }

    cout << res1 << endl;
    if (scc_cnt == 1)
        cout << 0 << endl;
    else
        cout << max(res1, res2) << endl;
    return 0;
}