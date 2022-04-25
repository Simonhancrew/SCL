#include <iostream>
#include <algorithm>
#include <cstring>
#include <unordered_map>

// Created by Simonhancrew on 2022/04/24

using namespace std;

/*
    这里的trick就是将floyd变形，f[k][i][j]变为恰好经过k条边
    i->j的最短路
    i->x->...->y->j，此时经过的边确定的话，如何组合是无所谓的
    即具有结合律，可以考虑做一个快速幂的操作，在快速幂中做求经过x条边的
    最短路
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 210;

int k, n, m, st, ed;
int g[N][N], res[N][N];

// 看似矩阵乘法，其实是做一个类floyd算法的求解
void mul(int a[][N], int b[][N], int c[][N])
{
    static int tmp[N][N];
    memset(tmp, 0x3f, sizeof tmp);

    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                tmp[i][j] = min(tmp[i][j], b[i][k] + c[k][j]);
            }
        }
    }
    memcpy(a, tmp, sizeof tmp);
}

void print(int a[][N])
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cout << a[i][j] << ' ';
        cout << endl;
    }
}

// 经过边数确定，结合律不影响最终结果
void qmi()
{
    memset(res, 0x3f, sizeof res);
    for (int i = 1; i <= n; i++)
        res[i][i] = 0;

    while (k)
    {
        if (k & 1)
            mul(res, res, g);
        k >>= 1;
        mul(g, g, g);
        // print(res);
    }
}

int main()
{
    fast_cin();
    cin >> k >> m >> st >> ed;
    memset(g, 0x3f, sizeof g);
    // 离散化
    unordered_map<int, int> idx(N);
    idx[st] = ++n;
    idx[ed] = ++n;
    st = idx[st], ed = idx[ed];

    // 记住此时的g是经过一条边时的最短路数组
    // i->i没有通路的话时INF,不需要初始化，res才是经过0
    // 条边的最短路
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> c >> a >> b;
        if (!idx.count(a))
            idx[a] = ++n;
        if (!idx.count(b))
            idx[b] = ++n;
        a = idx[a], b = idx[b];
        g[a][b] = g[b][a] = min(g[a][b], c);
    }

    qmi();

    cout << res[st][ed] << endl;

    return 0;
}