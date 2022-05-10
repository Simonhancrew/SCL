#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/05/10

using namespace std;

/*
    考虑差分约束的做法,利用一个前缀和s[i]
    表示[1,i]这些数中选择了多少个
    不难知道有
    s[i] - s[i - 1] <= 1
    s[i] >= 0
    s[b] - s[a - 1] >= c
    s[i] - s[i - 1] >= 0
    超级源点0也能达到其余的边
    最终要求一个最小值，等价求最长路，所以把上式
    全部转换成>=求解
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 5e4 + 10, M = 150010;

int n;
int h[N], e[M], ne[M], w[M], idx;
int dist[N], q[N];
bool st[N];

void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void spfa()
{
    memset(dist, -0x3f, sizeof dist);
    dist[0] = 0;
    int hh = 0, tt = 1;
    q[0] = 0;
    while (hh != tt)
    {
        int t = q[hh++];
        if (hh == N)
            hh = 0;
        st[t] = false;
        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (dist[j] < dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
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
}

int main()
{
    fast_cin();
    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 1; i < N; i++)
    {
        add(i - 1, i, 0);
        add(i, i - 1, -1);
    }
    while (n--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        ++a, ++b;
        add(a - 1, b, c);
    }
    spfa();
    cout << dist[50001] << endl;
    return 0;
}