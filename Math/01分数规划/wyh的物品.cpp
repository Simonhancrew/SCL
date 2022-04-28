#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/04/29

using namespace std;

/*
    经典01分数规划题目，当前物体的价值和重量是v和w
    选取k个物品，使得总体的单位价值最大
    二分可能的最终单位价值做check
    选取最大值符合一个等式：sum(v) / sum(w) >= mid
    变形一下： sum(v) - sum(w) * mid >= 0
    针对每一个物品： v - mid * w >= 0
    只要选取的k个是 >= 0 的就是合法解
    因此不难推得一个最大值的通式：
        sum(ai * wi) / sum(bi * wi) > mid
        sum(ai * wi) - sum(bi * wi) * mid > 0
        sum(wi * (ai - mid * b)) > 0
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

#define x first
#define y second

const int INF = 0x3f3f3f3f, N = 1e6 + 10;

using PDD = pair<double, double>;
const double eps = 1e-6;

PDD p[N];
double d[N];
int n, k;

bool check(double mid)
{
    for (int i = 0; i < n; i++)
    {
        d[i] = p[i].y - p[i].x * mid;
    }
    sort(d, d + n, [](double l, double r)
         { return l > r; });
    double sum = 0;
    for (int i = 0; i < k; i++)
    {
        sum += d[i];
    }
    return sum >= 0;
}

int main()
{
    fast_cin();
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> k;
        for (int i = 0; i < n; i++)
            cin >> p[i].x >> p[i].y;
        double l = 0, r = 1e6;
        while (r - l > eps)
        {
            double mid = (r + l) / 2;
            if (check(mid))
                l = mid;
            else
                r = mid;
        }
        printf("%.2f\n", l);
    }
    return 0;
}