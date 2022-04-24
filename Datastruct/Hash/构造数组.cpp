#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10, P = 998244353;

/*
    哈希方式是公开的，如果哈希被卡的话就初始话时赋予一个大数
    1. 哈希记录区间
    2. 区间合并找到不确定区间总数求值
*/

using PII = pair<int, int>;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

int n;
int a[N];
PII q[N];

int main()
{
    fast_cin();
    cin >> n;
    // 卡哈希的解决方法
    unordered_map<int, int> lhs(N), rhs(N);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        rhs[a[i]] = i;
        if (!lhs.count(a[i]))
            lhs[a[i]] = i;
    }
    int idx = 0;
    for (auto &[k, v] : lhs)
    {
        int l = v, r = rhs[k];
        q[idx++] = {l, r};
    }
    sort(q, q + idx);
    int st = -1, ed = -1, cnt = 0;
    for (int i = 0; i < idx; i++)
    {
        int l = q[i].first, r = q[i].second;
        if (l < ed)
        {
            ed = max(ed, r);
        }
        else
        {
            st = l, ed = r;
            cnt++;
        }
    }
    int res = 1;
    for (int i = 0; i < cnt - 1; i++)
    {
        res = res * 2 % P;
    }
    cout << res << endl;
    return 0;
}