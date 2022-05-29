#include <iostream>
#include <algorithm>
#include <cstring>
#include <unordered_set>

// Created by Simonhancrew on 2022/05/29

using namespace std;

/*
    重新理解一下缩点 + 建图的问题。这里要找半连通图，求最后的点数和可能的方案数，最终通过缩点
    + 重新建图 + 找一个最长链就是答案。关于最长链，可以采用dp的解法
    f[i]代表以i结尾的方案包含的节点数量最大值，g[i]是当前取到最大值的方案数
    这里的缩点 + 建图要做一个去重，否则最终在统计dp的时候会重复计算重复的边
    去重的方法也很简单，做一个边的映射key就可以了
    缩点是先把所有强连通分量看成一个点，然后对这个强连通点重新建立周围的连接（代表不会出现以前没有连接的边）
    最后是一个拓扑图的，因为dfs的过程中，stk出栈的时候代表u上方的节点他全部都能访问到
    所以根据一个scc_cnt的逆序其实是可以得到一个拓扑图的(算法导论上讲过dfs的toposort)
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e5 + 10, M = 2e6 + 10;

int n, m, P;
int h[N], hs[N], e[M], ne[M], idx;
int low[N], dfn[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], sz[N], scc_cnt;
int f[N], g[N];

void add(int h[], int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void tarjan(int u)
{
    low[u] = dfn[u] = ++timestamp;
    stk[++top] = u, in_stk[u] = true;
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        else if (in_stk[j])
        {
            low[u] = min(low[u], dfn[j]);
        }
    }

    if (low[u] == dfn[u])
    {
        int y;
        scc_cnt++;
        do
        {
            y = stk[top--];
            in_stk[y] = false;
            id[y] = scc_cnt;
            sz[scc_cnt]++;
        } while (y != u);
    }
}

int main()
{
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    fast_cin();
    cin >> n >> m >> P;
    memset(h, -1, sizeof h);
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        add(h, a, b);
    }
    for (int i = 1; i <= n; i++)
    {
        if (!dfn[i])
        {
            tarjan(i);
        }
    }

    unordered_set<LL> mp;
    memset(hs, -1, sizeof hs);

    for (int i = 1; i <= n; i++)
    {
        for (int j = h[i]; j != -1; j = ne[j])
        {
            int a = id[i], b = id[e[j]];
            // uset没有PII的has，但可以根据数据范围自己做映射
            LL to_hash = a * 1000000ll + b;
            if (a != b && !mp.count(to_hash))
            {
                add(hs, a, b);
                mp.insert(to_hash);
            }
        }
    }

    // 求最大的点数和此时最大的方案数，做一个路径上的dp
    for (int i = scc_cnt; i; i--)
    {
        if (!f[i])
        {
            f[i] = sz[i];
            g[i] = 1;
        }
        for (int j = hs[i]; ~j; j = ne[j])
        {
            int k = e[j];
            if (f[k] < f[i] + sz[k])
            {
                f[k] = f[i] + sz[k];
                g[k] = g[i];
            }
            else if (f[k] == f[i] + sz[k])
            {
                g[k] = (g[k] + g[i]) % P;
            }
        }
    }

    int mx = 0, sum = 0;
    for (int i = 1; i <= scc_cnt; i++)
    {
        if (f[i] > mx)
        {
            mx = f[i];
            sum = g[i];
        }
        else if (f[i] == mx)
        {
            sum = (sum + g[i]) % P;
        }
    }

    cout << mx << endl;
    cout << sum << endl;

    return 0;
}