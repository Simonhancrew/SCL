#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

// Created by Simonhancrew on 2022/04/25

using namespace std;

/*
    蓄水池抽样，比较适用链表随机取值，只能遍历一次的情况下均等概率的取出k个元素
    1. 先考虑k = 1的选择，只要保证每个元素最终选取的概率是1 / n就满足要求
        动态的考虑，当遍历到第i个元素时，以1 / i的概率选取这个元素，1 - 1 / i的概率
        保持前元素不变。
        因为当前元素选择之后，是否变化只和后续概率相关，所以不难得到一个当前元素被选择的概率公式
        p = 1 / i * p(第i + 1个元素不被选) * ... * p(第n个元素不被选)
        = 1 / i * (1 - 1 / (i + 1)) * .... * (1 - 1 / n)
        = 1 / i * (i / 1 + i) * ... * (n - 1 / n)
        = 1 / n
    2. k更大的时候同理，每个元素选择概率时k / n，先选择前k个放入res，后续遍历i ->[k,n],在[0,i)中随机选择一个值
    如果当前值在[0,k)中时，替换res当前索引下的值,此时被替换的概率时k / i,其中i是大于k的
*/

typedef long long LL;
typedef pair<int, int> PII;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 2e6 + 10;

int n, k, target;
int a[N];

int main()
{
    fast_cin();
    cin >> n >> k >> target;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<int> res;
    for (int i = 0; i < k; i++)
        res.push_back(a[i]);

    for (int i = k; i < n; i++)
    {
        int j = rand() % (i + 1);
        if (j < k)
        {
            res[j] = a[i];
        }
    }

    for (auto &x : res)
    {
        cout << x << ' ';
    }
    cout << endl;

    return 0;
}