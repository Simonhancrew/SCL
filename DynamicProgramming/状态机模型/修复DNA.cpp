#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/03/02

using namespace std;

/*
    和设计密码的思路比较像，不过是在trie图上做转移
    f[i][j]是当前字符串走到i位置，trie图中走到第j位置时
    最少的修改次数。就不要跳到标记位置，注意在后缀的部分也要有标记
*/

typedef long long LL;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int N = 1e3 + 10, INF = 0x3f3f3f3f;

int n, m;
int tr[N][4], ne[N], idx;
int q[N];
int des[N];
char s[N];
int f[N][N]; // 前i个字母，走到了当前ac自动机中j的位置状况下的最小修改次数

int get(char c)
{
    if (c == 'A')
        return 0;
    if (c == 'G')
        return 1;
    if (c == 'C')
        return 2;
    return 3;
}

void insert()
{
    int p = 0;
    for (int i = 0; s[i]; i++)
    {
        int t = get(s[i]);
        if (!tr[p][t])
            tr[p][t] = ++idx;
        p = tr[p][t];
    }
    des[p] = 1;
}
/*
    BFS构建trie图
*/
void build()
{
    int hh = 0, tt = -1;
    for (int i = 0; i < 4; i++)
    {
        if (tr[0][i])
            q[++tt] = tr[0][i];
    }
    while (hh <= tt)
    {
        int t = q[hh++];
        for (int i = 0; i < 4; i++)
        {
            int p = tr[t][i];
            if (!p)
                tr[t][i] = tr[ne[t]][i];
            else
            {
                ne[p] = tr[ne[t]][i];
                q[++tt] = p;
                des[p] |= des[ne[p]];
            }
        }
    }
}

int main()
{
    fast_cin();
    int t = 1;
    while (cin >> n, n)
    {
        memset(tr, 0, sizeof tr);
        memset(ne, 0, sizeof ne);
        memset(des, 0, sizeof des);
        idx = 0;

        for (int i = 0; i < n; i++)
        {
            cin >> s;
            insert();
        }
        build();

        cin >> (s + 1);
        m = strlen(s + 1);
        memset(f, 0x3f, sizeof f);
        f[0][0] = 0;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j <= idx; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    int t = get(s[i + 1]) != k;
                    int p = tr[j][k];
                    if (!des[p])
                    {
                        f[i + 1][p] = min(f[i + 1][p], f[i][j] + t);
                    }
                }
            }
        }

        int res = INF;
        for (int i = 0; i <= idx; i++)
            res = min(res, f[m][i]);

        if (res == INF)
            res = -1;

        cout << "Case " << t++ << ": " << res << endl;
    }
    return 0;
}