#include <iostream>
#include <unordered_map>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;

/*
    核心思路就是公约数，假设nums[i] * nums[j]能整除k，假设nums[j]里面有
    很多和k的公因子，k去除这些公因子之后是x（要去除的尽可能多），则nums[i]必须是x的倍数
    这个x最佳选择就是gcd(nums[j],k),也就是说nums[i]是k / gcd(nums[i],k)的
    倍数。
*/

int n,k;
int a[N];

int gcd(int a,int b) {
    return b ? gcd(b,a % b) : a;
}

#if 0

/*
    只关注个数，所以看看每个数和k的最大公约数（一个桶的思想），遍历一次arr
    然后枚举这些[k,v]，看看相互匹配能否整除k，可以的话就给ans增加计数
    为了不重不漏的枚举，约定k1 <= k2
*/

int main()
{
    cin >> n >> k;
    unordered_map<int,int> mp;
    for(int i = 0;i < n;i++) cin >> a[i];
    for(int i = 0;i < n;i++){
        mp[gcd(a[i],k)]++;
    } 
    LL ans = 0;
    for(auto &[k1,v1] : mp) {
        for(auto &[k2,v2] : mp) {
            if((LL)k1 * k2 % k == 0) {
                if(k1 < k2) ans += (LL)v1 * v2;
                else if(k1 == k2) ans += (LL)v1 * (v1 - 1) / 2;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
#endif

/*
    核心思路就是公约数，假设nums[i] * nums[j]能整除k，假设nums[j]里面有
    很多和k的公因子，k去除这些公因子之后是x（要去除的尽可能多），则nums[i]必须是x的倍数
    这个x最佳选择就是gcd(nums[j],k),也就是说nums[i]是k / gcd(nums[i],k)的
    倍数。针对每个nums[j],看看有多少个nums[i],因为不重不漏的枚举，之和前面的nums[i]
    匹配.用一个哈希表边做边统计各个公因子的个数有多少就行了。

    另外lc关于c++的全局初始化：
        const int N = 1e5 + 7;
        vector<vector<int>> divi(N);
        function<int()> init = []()
        {
            for(int i = 1;i < N;i++){
                for(int j = i;j < N;j += i) {
                    divi[j].push_back(i);
                }
            }
            return 0;
        };
        int ini = init();
*/

vector<vector<int>> divi(N);

void init()
{
    for(int i = 1;i <= N;i++){
        for(int j = i;j <= N;j += i) {
            divi[j].push_back(i);
        }
    }
}

int main()
{
    cin >> n >> k;
    LL ans = 0;
    unordered_map<int,int> mp;
    for(int i = 0;i < n;i++) cin >> a[i];
    for(int i = 0;i < n;i++) {
        ans += mp[k / gcd(k,a[i])];
        for(auto &d : divi[a[i]]) {
            mp[d]++;
        }
    }
    cout << ans << endl;
    return 0;
}