#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/04/24

using namespace std;

/*
    floyd求解最小环问题
    根据floyd的状态转移方程，在前k次中,d[i][j]代表经过[1,k - 1]的这些点中
    d[i][j]的最小值。
    在k次转移中，不难知道d[i][j] + g[j][k] + g[k][i]就有可能构成一个环,其中
    i和j都属于[1,k - 1].k和当前的i->j路径是没有交集的
    找到最小的可能环就行了
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 110;

int n, m;
int g[N][N], d[N][N];      // g是原图备份，d求解最短路
int p[N][N], path[N], cnt; // p[i][j]代表i->j的中间节点

void get_path(int x, int y)
{
    if (p[x][y] == 0)
        return;

    int k = p[x][y];
    get_path(x, k);
    path[cnt++] = k;
    get_path(k, y);
}

int main()
{
    fast_cin();
    cin >> n >> m;
    memset(g, 0x3f, sizeof g);
    for (int i = 1; i <= n; i++)
        g[i][i] = 0;

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = g[b][a] = min(g[a][b], c);
    }

    memcpy(d, g, sizeof d);
    int res = INF;
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i < k; i++)
        {
            for (int j = i + 1; j < k; j++)
            {
                if (res > (LL)d[i][j] + g[j][k] + g[k][i])
                {
                    res = d[i][j] + g[j][k] + g[k][i];
                    cnt = 0;
                    path[cnt++] = k;
                    path[cnt++] = i;
                    get_path(i, j);
                    path[cnt++] = j;
                }
            }
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (d[i][k] + d[k][j] < d[i][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
                    p[i][j] = k; // 代表i->j的中间节点
                }
            }
        }
    }

    if (res == INF)
        cout << "No solution." << endl;
    else
    {
        for (int i = 0; i < cnt; i++)
            cout << path[i] << ' ';
        cout << endl;
    }
    return 0;
}