#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/05/13

using namespace std;

/*
    先找关系，单位i时间，申请的人是nums[i],实际上岗的人是x[i];
    则不难有一个基础关系
    x[i] <= nums[i]
    x[i] >= 0
    另，r[i]代表在i时刻，有r[i]人在岗
    r[i] <= x[i] + x[i - 1] + ....+ x[i - 8 + 1]
    考虑到多点会比较难做，令s[i]表示x的前缀和
    所以:
    1. s[i] - s[i - 1] >= 0;
    2. s[i] - s[i - 1] <= nums[i]
    3. i >= 8 s[i] - s[i - 8] >= r[i]
    4. i <= 7 比较特殊
    s[i] + s[24] - s[i + 16] >= r[i]
    不妨枚举所有的s[24]，因为r最大也才1000
    就可以构建一个s[i] >= s[i + 16]  + r[i] - s[24]
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 30, M = 100;

int h[N], e[M], ne[M], w[M], idx;
int dist[N], cnt[N], q[N];
bool st[N];
int r[N], nums[N];

void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void build(int tail)
{
    memset(h, -1, sizeof h);
    idx = 0;
    for (int i = 1; i <= 24; i++)
    {
        add(i - 1, i, 0);
        add(i, i - 1, -nums[i]);
    }
    for (int i = 8; i <= 24; i++)
        add(i - 8, i, r[i]);
    for (int i = 1; i <= 7; i++)
        add(i + 16, i, r[i] - tail);
    // 限制tail->s[24]
    add(0, 24, tail), add(24, 0, -tail);
}

bool spfa(int tail)
{
    build(tail);
    memset(st, 0, sizeof st);
    memset(cnt, 0, sizeof cnt);
    memset(dist, -0x3f, sizeof dist);
    dist[0] = 0;
    st[0] = true;
    q[0] = 0;
    int hh = 0, tt = 1;
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
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= 25)
                    return false;
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
    return true;
}

int main()
{
    fast_cin();
    int T;
    cin >> T;
    while (T--)
    {
        memset(nums, 0, sizeof nums);
        for (int i = 1; i <= 24; i++)
            cin >> r[i];
        int n;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            int t;
            cin >> t;
            nums[t + 1]++;
        }
        bool flag = false;
        for (int i = 0; i <= 1000; i++)
        {
            if (spfa(i))
            {
                cout << i << endl;
                flag = true;
                break;
            }
        }
        if (!flag)
            cout << "No Solution" << endl;
    }
    return 0;
}