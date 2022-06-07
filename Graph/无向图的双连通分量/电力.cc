#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/06/07

using namespace std;

/*
    求割点，对每个DCC试删除这个点，看看结果是多少
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e4 + 10, M = 3e4 + 10;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N];
int root, ans;
int timestamp;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void tarjan(int u)
{
    low[u] = dfn[u] = ++timestamp;
    int cnt = 0;
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
            if (low[j] >= dfn[u])
                cnt++;
        }
        else
            low[u] = min(low[u], dfn[j]);
    }

    // 算一下当前点删除之后能分成多少连通块
    if (u != root)
        cnt++;

    ans = max(ans, cnt);
}

int main()
{
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    fast_cin();
    while (cin >> n >> m, n || m)
    {
        memset(dfn, 0, sizeof dfn);
        memset(h, -1, sizeof h);
        idx = timestamp = 0;
        while (m--)
        {
            int a, b;
            cin >> a >> b;
            add(a, b), add(b, a);
        }

        ans = 0;
        int cnt = 0;
        for (root = 0; root != n; root++)
        {
            if (!dfn[root])
            {
                cnt++;
                tarjan(root);
            }
        }

        cout << ans + cnt - 1 << endl;
    }
    return 0;
}