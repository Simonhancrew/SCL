#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/06/22

using namespace std;

/*
    最小点覆盖 == 最大匹配数（二分图）
    机器是0的时候，针对所有的任务，如果存在0状态，则可以忽略当前任务。直接安排
    否则，ai和bi一定大于0。此时任务被执行可以抽象成连接了一条ai到bi的边，要么左边，要么右边被选
    结果就是求一个最小点覆盖
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 110;

int n, m, k;
int match[N];
bool st[N], g[N][N];

bool find(int x)
{
    for (int i = 1; i < m; i++)
    {
        if (!st[i] && g[x][i])
        {
            st[i] = true;
            if (match[i] == 0 || find(match[i]))
            {
                match[i] = x;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    fast_cin();
    while (cin >> n, n)
    {
        memset(match, 0, sizeof match);
        memset(g, 0, sizeof g);
        cin >> m >> k;
        while (k--)
        {
            int t, a, b;
            cin >> t >> a >> b;
            if (!a || !b)
                continue;
            g[a][b] = true;
        }
        int res = 0;
        for (int i = 1; i < n; i++)
        {
            memset(st, 0, sizeof st);
            if (find(i))
                ++res;
        }
        cout << res << endl;
    }
    return 0;
}