#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

// Created by Simonhancrew on 2022/05/03

using namespace std;

/*
    很裸的一道求负环的题目
    直接spfa做就行，值得注意的是用的方法是判断走过的边有多少条
    来判断有没有负环，这会比判断点入队次数稍快一点
    假设有一个长度为n的负环，此时入队n次的判断需要走过这个负环n次
    但是根据走过的路径长度是否>=n时的判断只需要遍历负环1次
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 510, M = 5210;

int n, m1, m2, t;
int cnt[N], dist[N];
bool st[N];
int h[N], e[M], ne[M], w[M], idx;
int q[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

bool spfa()
{
    memset(st, 0, sizeof st);
    memset(dist, 0, sizeof dist);
    memset(cnt, 0, sizeof cnt);
    int hh = 0, tt = 0;
    for (int i = 1; i <= n; i++)
    {
        q[tt++] = i;
        st[i] = true;
    }

    while (hh != tt)
    {
        int t = q[hh++];
        if (hh == N)
            hh = 0;
        st[t] = false; // 和dij的逻辑不一样，出队不能确定最小，只是不用松弛了
        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
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
    fast_cin();
    cin >> t;
    while (t--)
    {
        cin >> n >> m1 >> m2;
        idx = 0;
        memset(h, -1, sizeof h);
        while (m1--)
        {
            int a, b, c;
            cin >> a >> b >> c;
            add(a, b, c), add(b, a, c);
        }
        while (m2--)
        {
            int a, b, c;
            cin >> a >> b >> c;
            add(a, b, -c);
        }

        if (spfa())
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}