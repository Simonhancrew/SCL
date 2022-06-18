#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/06/14

using namespace std;

/*
    将格点和按照奇数和偶数分类（一个二分图）
    图的最多能放方块数->没有公共端点的边做多有多少个。
*/

typedef long long LL;
typedef pair<int, int> PII;
#define x first
#define y second
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 110;

bool g[N][N], st[N][N];
int n, t;
PII match[N][N];
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

bool find(int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx <= 0 || nx > n || ny <= 0 || ny > n)
            continue;
        if (g[nx][ny] || st[nx][ny])
            continue;
        auto t = match[nx][ny];
        st[nx][ny] = true; // 冲突时刻下面的find可以递归的找合法的右图点
        if (t.x == -1 || find(t.x, t.y))
        {
            match[nx][ny] = {x, y};
            return true;
        }
    }
    return false;
}

int main()
{
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    fast_cin();
    cin >> n >> t;
    while (t--)
    {
        int x, y;
        cin >> x >> y;
        g[x][y] = 1;
    }

    int res = 0;
    memset(match, -1, sizeof match);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if ((i + j) % 2 && !g[i][j])
            {
                memset(st, 0, sizeof st);
                if (find(i, j))
                    res++;
            }
        }
    }

    cout << res << endl;
    return 0;
}