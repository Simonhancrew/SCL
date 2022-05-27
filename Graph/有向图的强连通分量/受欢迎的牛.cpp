#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/05/25

using namespace std;

/*
    多少牛头是除去自己之外被所有的牛欢迎->建图的方式A认为B受欢迎，A->B
    ->缩点，成环的牛一定互相欢迎，其中强连通点缩成一团->新图中，看一下出度，出度是0的团只进不出，相当受欢迎
    ->如果这样的团的数目大于1，这两（多）个团一定不能互相喜欢（连接），和题目不符，结果是0
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e4 + 10, M = 5e4 + 10;

int n, m;
int h[N], e[M], ne[M], w[M], idx;
int dout[N];
int dfn[N], low[N], timestamp;
int stk[N], top; // 这里的栈仅仅记录是否结束回溯，和栈模拟递归不一样
bool instk[N];
int scc_cnt, id[N], sz[N]; //连通分量（团）计数，当前点属于那个连通分量，当前连通分量的大小（里面多少个点）

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u, instk[u] = true;

    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        else if (instk[j])
        {
            low[u] = min(low[u], dfn[j]);
        }
    }

    if (dfn[u] == low[u])
    {
        int y;
        scc_cnt++;
        do
        {
            y = stk[top--];
            instk[y] = false;
            id[y] = scc_cnt;
            sz[scc_cnt]++;
        } while (u != y);
    }
}

int main()
{
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    fast_cin();
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }

    for (int i = 1; i <= n; i++)
    {
        if (!dfn[i])
        {
            tarjan(i);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = h[i]; j != -1; j = ne[j])
        {
            int t = e[j];
            int a = id[i], b = id[t];
            if (a != b)
            {
                dout[a]++;
            }
        }
    }

    int zero = 0, sum = 0;
    for (int i = 1; i <= scc_cnt; i++)
    {
        if (!dout[i])
        {
            zero++;
            sum += sz[i];
            if (zero > 1)
            {
                sum = 0;
                break;
            }
        }
    }

    cout << sum << endl;

    return 0;
}