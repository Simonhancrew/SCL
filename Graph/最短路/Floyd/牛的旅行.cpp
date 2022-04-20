#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

// Created by Simonhancrew on 2022/04/20

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

/*
    需要新加一条边，使得最大直径最小
    1. 最后的直径 >= 各个连通块内部的直径的最大值
    因为加边之后直径只会增或者不变
    2. 加边的新连通区的最大直径需要考虑经过新加边的直径长度
    最后结果综合两者的最大值
*/

#define x first
#define y second

const int N = 160;
const double INF = 1e20;

PII p[N];
double maxd[N], d[N][N];
char g[N][N];
int n;

double cal(PII a, PII b)
{
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> p[i].x >> p[i].y;
    for (int i = 0; i < n; i++)
        cin >> g[i];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                if (g[i][j] == '1')
                    d[i][j] = cal(p[i], p[j]);
                else
                    d[i][j] = INF;
            }
        }
    }

    // floyd算一下内部的各点最短路
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    // 内部最大直径(内部取最大值)
    double inside = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (d[i][j] < INF)
                maxd[i] = max(maxd[i], d[i][j]);
        }
        inside = max(inside, maxd[i]);
    }

    // 经过新家边的最小直径
    double add = INF;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (d[i][j] >= INF)
                add = min(add, cal(p[i], p[j]) + maxd[i] + maxd[j]);
        }
    }

    // 结果取一个max
    printf("%.6lf\n", max(inside, add));

    return 0;
}