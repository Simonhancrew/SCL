#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/05/05

using namespace std;

/*
    建图需要具体考虑，如果全部存字符串的话空间会爆
    每次针对字符串s的左右两个字符建立一跳边，这样在整体找环的
    时候和原问题是等价的。
    之后是一个01分数规划的推导，sum(边权) / sum(边) >= mid
    则 边权 - mid * 1 >= 0,做一个二分
    实际过程中，SPFA找负环有一个经验解，当走过的点大于某一个数值的时候
    可以认为当前有环
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 700, M = 1e5 + 10;
const double eps = 1e-4;

int n;
int h[N], e[M], ne[M], w[M], idx;
bool st[N];
int q[N], cnt[N];
double dist[N];
string s;

void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

bool check(double mid)
{
    memset(dist, 0, sizeof dist);
    memset(cnt, 0, sizeof cnt);
    int hh = 0, tt = 0;
    for (int i = 0; i < 676; i++)
    {
        st[i] = true;
        q[tt++] = i;
    }
    int count = 0;
    while (hh != tt)
    {
        int t = q[hh++];
        if (hh == N)
            hh = 0;
        st[t] = false;
        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (dist[j] < dist[t] + w[i] - mid)
            {
                dist[j] = dist[t] + w[i] - mid;
                cnt[j] = cnt[t] + 1;
                if (++count >= 10000) // 一个经验解，走过的点数大于某一个值的时候可以认为是有环的
                    return true;
                if (cnt[j] >= N) // 注意这里的N(676)才是点数,n是边数
                    return true;
                if (!st[j])
                {
                    st[j] = true;
                    q[tt++] = j;
                    if (tt == N)
                        tt = 0;
                }
            }
        }
    }
    return false;
}

int main()
{
    fast_cin();
    while (cin >> n, n)
    {
        idx = 0;
        memset(h, -1, sizeof h);
        for (int i = 0; i < n; i++)
        {
            cin >> s;
            int len = s.size();
            if (len < 2)
                continue;
            int u = (s[0] - 'a') * 26 + s[1] - 'a';
            int v = (s[len - 2] - 'a') * 26 + s[len - 1] - 'a';
            add(u, v, len);
        }

        if (!check(0)) // 没环就不用费力考虑后面的01分数规划了
        {
            cout << "No solution" << endl;
            continue;
        }
        double l = 0, r = 1000;
        while (r - l > eps)
        {
            double mid = (l + r) / 2;
            if (check(mid))
                l = mid;
            else
                r = mid;
        }
        cout << l << endl;
    }
    return 0;
}