#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

// Created by Simonhancrew on 2022/06/08

using namespace std;

/*
    放置出口，先缩点，构建点双连通分量
    针对一个双连通分量：
    1. 没有割点：这个区域内放两个出口，C[cnt][2],总方案数乘法原理，其中cnt = 1时特判
    2. 一个割点：当前区域只用放一个就够了，C[cnt][1]
    3. 更多的割点：不用放置，能通过其余分量逃出
    注意割点可能属于多个连通分量，每个割点必然有一个出口
*/

using ULL = unsigned long long;
using LL = long long;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e3 + 10, M = 2e3 + 10;

int m, n;
int e[M], ne[M], h[N], idx;
int dfn[N], low[N], timestamp;
int dcc_cnt;
int stk[N], top;
bool cut[N];
vector<int> dcc[N];
int root;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u;
    if (u == root && h[u] == -1)
    {
        dcc_cnt++;
        dcc[dcc_cnt].push_back(u);
        return;
    }

    int cnt = 0;
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
            if (dfn[u] <= low[j]) // 仅仅多了分支不一定是割点
            {
                cnt++;
                // 是根节点，但是子孙少于1，删了依然连通
                // 不是根，删了时候上下分两部分。两种情况
                if (u != root || cnt > 1)
                {
                    cut[u] = true;
                }
                ++dcc_cnt;
                int y;
                do
                {
                    y = stk[top--];
                    dcc[dcc_cnt].push_back(y);
                } while (y != j);
                dcc[dcc_cnt].push_back(u);
            }
        }
        else
        {
            low[u] = min(low[u], dfn[j]);
        }
    }
}

int main()
{
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    fast_cin();
    int t = 1;
    while (cin >> m, m)
    {
        memset(cut, 0, sizeof cut);
        memset(h, -1, sizeof h);
        memset(dfn, 0, sizeof dfn);
        for (int i = 1; i <= dcc_cnt; i++)
            dcc[i].clear();
        idx = n = top = timestamp = dcc_cnt = 0;
        while (m--)
        {
            int a, b;
            cin >> a >> b;
            n = max(n, a), n = max(n, b);
            add(a, b), add(b, a);
        }

        for (root = 1; root <= n; root++)
        {
            if (!dfn[root])
            {
                tarjan(root);
            }
        }

        int res = 0;
        ULL num = 1;
        for (int i = 1; i <= dcc_cnt; i++)
        {
            int cnt = 0;
            for (int j = 0; j < dcc[i].size(); j++)
            {
                if (cut[dcc[i][j]])
                {
                    cnt++;
                }
            }
            if (cnt == 0)
            {
                if (dcc[i].size() > 1)
                    res += 2, num *= dcc[i].size() * (dcc[i].size() - 1) / 2;
                else
                    res++;
            }
            else if (cnt == 1)
            {
                res++, num *= dcc[i].size() - 1; // 当前连通分量里面是包含一个割点的，方案要从剩下的选
            }
        }
        cout << "Case " << t++ << ": " << res << ' ' << num << endl;
    }
    return 0;
}