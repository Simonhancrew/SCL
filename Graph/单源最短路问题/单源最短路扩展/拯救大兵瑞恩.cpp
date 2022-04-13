#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <deque>

// Created by Simonhancrew on 2022/04/13

using namespace std;

/*
    图论建图拆点
    先不考虑钥匙的问题，无墙则建立一条无向边。就是一个很简单的边权恒定最短路
    加入钥匙之后，存在找钥匙之后再返回的情况，为了方便描述当前带钥匙的状态
    可以参考dp的思路（其实dp就是在一个有向无环图上做最短路）

    可以考虑一个建图的方式多一位state标志，代表当前拥有钥匙的情况。

    此时的距离就是d[idx][state],代表到idx位置，拥有钥匙状态是state下

    针对有门的位置建立一个带权标志的双向边，随后在做最短路的过程中，到达带钥匙位置
    的时候距离的更新可以看作是一个0的路

    到达当前位置的最短路。对于当前idx位置有钥匙的话，上一个位置到当前位置的转移
        state = pre | key
        d[idx][state] = min(d[idx][state],d[idx][pre])
    此时等价于走了一条边权为0的边

    针对当前位置遍历周边可以走的位置，只要可达就可以将（此时走一条边权为1的边）
        d[idx][state] = min(d[idx][state],d[idx][pre] + 1)
    不难联想到一个双端队列BFS，实质就是一个dij(堆)
*/

typedef long long LL;
typedef pair<int, int> PII;

#define x first
#define y second

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 11, M = 400, P = 1 << 10;
int n, m, p;
int h[N * N], e[M], ne[M], w[M], idx;
int dist[N * N][P];
int key[N * N], g[N][N];
bool st[N * N][P];
set<PII> edges;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

// 建图，不在edge标记的门中就是通路，标记0
void build()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int d = 0; d < 4; d++)
            {
                int x = i + dx[d], y = j + dy[d];
                if (x < 1 || x > n || y < 1 || y > m)
                    continue;
                int a = g[i][j], b = g[x][y];
                if (edges.count({a, b}))
                    continue;
                add(a, b, 0);
            }
        }
    }
}

// 双端队列BFS，等价一个堆优化dij
int bfs()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1][0] = 0;
    deque<PII> q;
    q.push_back({1, 0});
    while (q.size())
    {
        auto t = q.front();
        q.pop_front();

        if (st[t.x][t.y])
            continue;
        st[t.x][t.y] = true;

        if (t.x == n * m)
            return dist[t.x][t.y];

        // 当前位置有钥匙，将位置 + 状态更新，此时的边权是0
        if (key[t.x])
        {
            int state = t.y | key[t.x];
            if (dist[t.x][state] > dist[t.x][t.y])
            {
                dist[t.x][state] = dist[t.x][t.y];
                q.push_front({t.x, state});
            }
        }

        // 更新当前点连接边的点的距离（状态不变，点变），此时边权1
        for (int i = h[t.x]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (w[i] && ((t.y >> (w[i] - 1)) & 1) == 0)
                continue;
            if (dist[j][t.y] > dist[t.x][t.y] + 1)
            {
                dist[j][t.y] = dist[t.x][t.y] + 1;
                q.push_back({j, t.y});
            }
        }
    }

    return -1;
}

int main()
{
    fast_cin();
    int k;
    cin >> n >> m >> p >> k;

    // 将点的2D变1D
    for (int i = 1, t = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            g[i][j] = t++;
        }
    }

    // 不是真边权，一个标记，是门还是通路
    memset(h, -1, sizeof h);
    while (k--)
    {
        int a, b, c, d, e;
        cin >> a >> b >> c >> d >> e;
        int lhs = g[a][b], rhs = g[c][d];
        edges.insert({lhs, rhs}), edges.insert({rhs, lhs});
        if (e)
            add(lhs, rhs, e), add(rhs, lhs, e);
    }

    build();

    int s;
    cin >> s;
    // 利用二进制每个位置的key
    while (s--)
    {
        int x, y, q;
        cin >> x >> y >> q;
        int idx = g[x][y];
        key[idx] |= 1 << (q - 1);
    }

    cout << bfs() << endl;

    return 0;
}