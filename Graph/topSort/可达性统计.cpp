#include <iostream>
#include <algorithm>
#include <cstring>
#include <bitset>

// Created by Simonhancrew on 2022/05/23

using namespace std;

/*
    统计DAG可达性问题，按照topo逆序看每个点的可达性
    假设f[i]是i的可达点，f[i] |= f[ne[i]];
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 3e4 + 10, M = N;

int n, m;
int h[N], e[M], ne[M], idx;
int d[N], q[N];
bitset<N> f[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void topsort()
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
}

int main()
{
    fast_cin();
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        add(a, b);
        d[b]++;
    }

    topsort();

    for (int i = n - 1; i >= 0; i--)
    {
        int j = q[i];
        f[j][j] = 1;
        for (int k = h[j]; k != -1; k = ne[k])
        {
            f[j] |= f[e[k]];
        }
    }

    for (int i = 1; i <= n; i++)
        cout << f[i].count() << endl;

    return 0;
}