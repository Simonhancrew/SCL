#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

// Created by Simonhancrew on 2022/03/11

using namespace std;

/*
    from Leetcode-cn
    DFS能比较简单的统计节点数目的情况，只需要多家额外数组记录就行
    本体需要额外考虑子节点移除的时候上半部分还有一个子树的情况
*/

typedef long long LL;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int N = 1e5 + 10;

int par[N];
int n, cnt;
LL mx;
vector<int> sz;
vector<vector<int>> g;

void dfs(int u)
{
    sz[u] = 1;
    LL tmp = 1;
    for (auto s : g[u])
    {
        dfs(s);
        sz[u] += sz[s];
        tmp *= sz[s];
    }
    if (n - sz[u])
        tmp *= n - sz[u];

    if (tmp > mx)
    {
        cnt = 1;
        mx = tmp;
    }
    else if (tmp == mx)
    {
        cnt++;
    }
}

int main()
{
    fast_cin();
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> par[i];
    g.resize(n), sz.resize(n);
    mx = -1;
    for (int i = 1; i < n; i++)
    {
        g[par[i]].push_back(i);
    }
    dfs(0);
    cout << cnt << endl;
    return 0;
}