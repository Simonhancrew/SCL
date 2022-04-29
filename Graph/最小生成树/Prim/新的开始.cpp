#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/04/29

using namespace std;

/*
    直接做不是很好做，可以用到一个超级源点的建图技巧
    将0设为超级原点，其余点和超级原点连通就是自己建造发电站的花费
    其余的连边可以看作连接电网的花费
    这样就能使用最小生成树的算法做了
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 310;

int n;
int p[N][N];
int d[N];
bool st[N];

int prim()
{
    memset(d, 0x3f, sizeof d);
    d[0] = 0;
    int res = 0;
    for (int i = 0; i <= n; i++)
    {
        int t = -1;
        for (int j = 0; j <= n; j++)
        {
            if (!st[j] && (t == -1 || d[t] > d[j]))
            {
                t = j;
            }
        }
        st[t] = true;
        res += d[t];
        for (int j = 0; j <= n; j++)
            d[j] = min(d[j], p[t][j]);
    }
    return res;
}

int main()
{
    fast_cin();
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int t;
        cin >> t;
        p[i][0] = p[0][i] = t;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> p[i][j];
        }
    }

    int res = prim();

    cout << res << endl;

    return 0;
}