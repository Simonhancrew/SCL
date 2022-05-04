#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/05/04

using namespace std;

/*
    01分数规划 + 求正环，01分数规划用二分做就可以了
    sum(f) / sum(t) >= mid
    sum(f) - mid * sum(t) >= 0
    把点的权值按照上述公式加权到边上，等价于在原图上求是否存在一个正环
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1010, M = 5010;
const double eps = 1e-4;

int q[N], cnt[N], f[N];
int h[N], e[M], ne[M], w[M], idx;
bool st[N];
double dist[N];
int n, m;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

bool check(double mid)
{
    // memset(st,0,sizeof st);
    memset(cnt, 0, sizeof cnt);
    // memset(dist,0,sizeof dist);

    int hh = 0, tt = 0;
    for (int i = 1; i <= n; i++)
    {
        st[i] = true;
        q[tt++] = i;
    }

    while (hh != tt)
    {
        int t = q[hh++];
        if (hh == N)
            hh = 0;
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            // 求一个正环
            if (dist[j] < dist[t] + f[t] - mid * w[i])
            {
                dist[j] = dist[t] + f[t] - mid * w[i];
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= n)
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
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++)
        cin >> f[i];
    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }

    double l = 0, r = 1e3 + 10;
    while (r - l > eps)
    {
        double mid = (l + r) / 2;
        if (check(mid))
            l = mid;
        else
            r = mid;
    }

    printf("%.2lf\n", l);
    return 0;
}