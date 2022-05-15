#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/05/15

using namespace std;

/*
    结构化类segtree，统计点数，来自leetcode周赛293 Q4
    重新理解seg tree，modify的时候入参永远是常量,修改的区间是[L,R]，往下走去查询线段树的
    每个节点需不要修改。每个节点有一个区间[l,r]。能往下走的时候一定是他的子区间在[L,R]内的时候
    即[l,mid],[mid + 1,r]在[L,R]之中。只需要判断mid和[L,R]的关系就可以了
    因此，完全包含的逻辑就比较好理解了，[l,r]完全在[L,R]内，l >= l,r <= R
    这里可以lazy tag取巧，因为修改一定要下传lazy tag
    这里只要区间sum == r - l - 1就是完全覆盖，左右也应该完全覆盖
    最后做一个pushup
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

int n;

class CountIntervals
{
    CountIntervals *lhs, *rhs;
    int l, r, sum = 0;

public:
    CountIntervals() : l(1), r(1e9), lhs(nullptr), rhs(nullptr)
    {
    }

    CountIntervals(int l, int r) : l(l), r(r), lhs(nullptr), rhs(nullptr) {}

    void fill()
    {
        sum = r - l + 1;
    }

    void add(int L, int R)
    {
        if (L <= l && r <= R)
        {
            fill();
            return;
        }
        int mid = (l + r) >> 1;
        if (lhs == nullptr)
            lhs = new CountIntervals(l, mid);
        if (rhs == nullptr)
            rhs = new CountIntervals(mid + 1, r);

        if (sum == r - l + 1)
        {
            lhs->fill();
            rhs->fill();
        }

        if (L <= mid)
            lhs->add(L, R);
        if (mid < R)
            rhs->add(L, R);
        sum = lhs->sum + rhs->sum;
    }

    int count()
    {
        return sum;
    }
};

int main()
{
    fast_cin();
    cin >> n;
    CountIntervals t;
    while (n--)
    {
        int a, b;
        cin >> a >> b;
        t.add(a, b);
    }
    cout << t.count() << endl;
    return 0;
}