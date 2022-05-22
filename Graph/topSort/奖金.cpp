#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/05/22

using namespace std;

/*
    实质是一个差分约束问题，要求最小值，等价求一个最长路。
    在拓扑序的约束下拉满每条边的权值就行了
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e4 + 10, M = 2e4 + 10;

int n, m;
int h[N], e[M], ne[M], idx;
int d[N], dist[N], q[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

bool topsort()
{
    int hh = 0, tt = -1;
    for (int i = 1; i <= n; i++)
    {
        if (!d[i])
            q[++tt] = i;
    }
    while (hh <= tt)
    {
        int t = q[hh++];
        for (int i = h[t]; i != -1; i = ne[i])
        {
            if (--d[e[i]] == 0)
                q[++tt] = e[i];
        }
    }
    return tt == n - 1;
}

int main()
{
    fast_cin();
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        add(b, a);
        d[a]++;
    }
    if (!topsort())
        cout << "Poor Xed" << endl;
    else
    {
        for (int i = 1; i <= n; i++)
            dist[i] = 100;
        for (int i = 0; i < n; i++)
        {
            int t = q[i];
            for (int j = h[t]; j != -1; j = ne[j])
            {
                dist[e[j]] = max(dist[e[j]], dist[t] + 1);
            }
        }
        int res = 0;
        for (int i = 1; i <= n; i++)
            res += dist[i];
        cout << res << endl;
    }
    return 0;
}