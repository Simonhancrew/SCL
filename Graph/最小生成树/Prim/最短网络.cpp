#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/04/27

using namespace std;

/*
    很裸的一道最短路的题目，prim的核心是将集合扩展，知道覆盖每个点，所以是按照点去更新的
    记录使用邻接矩阵。首先选择不在集合中，且离当前集合最近的一个点（第一次不用更新，集合初始）
    随后将这个点导入集合，更新最小生成权，随后看看当前新边能否更新
    其他节点到当前集合的最小距离
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 110;

int n;
int g[N][N], d[N];
bool st[N];

int prim()
{
    memset(d, 0x3f, sizeof d);
    d[1] = 0; // 可以不初始化值，因为i == 0的时候不更新res，写法可以等价
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        int t = -1;
        for (int j = 1; j <= n; j++)
        {
            if (!st[j] && (t == -1 || d[t] > d[j]))
                t = j;
        }
        st[t] = true;
        if (i && d[t] == INF)
            return INF;
        if (i)
            res += d[t];
        for (int j = 1; j <= n; j++)
            d[j] = min(d[j], g[t][j]);
    }
    return res;
}

int main()
{
    fast_cin();
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> g[i][j];
        }
    }
    cout << prim() << endl;
    return 0;
}