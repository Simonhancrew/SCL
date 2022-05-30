#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/05/30

using namespace std;

/*
    其实是一个差分约束求最小值问题->最长路问题
    用强连通分量来做的话，可以做到线性。
    判无解的方法还是找环(这里是正环)，只要在连通分量内部能找到权值大于等于1的边
    就代表无解。
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e5 + 10, M = 6e5 + 10;

int n, m;
int h[N], hs[N], e[M], ne[M], w[M], idx;
int low[N], dfn[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], sz[N], scc_cnt;
int dist[N];

void add(int h[], int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
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
    // cout << u << ' ' << low[u] << ' ' << dfn[u] << endl;
    if (low[u] == dfn[u])
    {
        scc_cnt++;
        int y;
        do
        {
            y = stk[top--];
            id[y] = scc_cnt;
            in_stk[y] = false;
            sz[scc_cnt]++;
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
        int t, a, b;
        cin >> t >> a >> b;
        if (t == 1)
            add(h, a, b, 0), add(h, b, a, 0);
        else if (t == 2)
            add(h, a, b, 1);
        else if (t == 3)
            add(h, b, a, 0);
        else if (t == 4)
            add(h, b, a, 1);
        else
            add(h, a, b, 0);
    }
    for (int i = 1; i <= n; i++)
    {
        add(h, 0, i, 1);
    }

    tarjan(0);

    bool flag = true;
    memset(hs, -1, sizeof hs);
    for (int i = 0; i <= n; i++)
    {
        for (int j = h[i]; j != -1; j = ne[j])
        {
            int a = id[i], b = id[e[j]];
            if (a == b)
            {
                if (w[j] > 0)
                {
                    flag = false;
                    break;
                }
            }
            else
                add(hs, a, b, w[j]);
        }
        if (!flag)
            break;
    }

    if (!flag)
        cout << -1 << endl;
    else
    {
        for (int i = scc_cnt; i; i--)
        {
            for (int j = hs[i]; j != -1; j = ne[j])
            {
                dist[e[j]] = max(dist[e[j]], dist[i] + w[j]);
            }
        }
        LL res = 0;
        for (int i = 1; i <= scc_cnt; i++)
            res += (LL)dist[i] * sz[i];
        cout << res << endl;
    }

    return 0;
}