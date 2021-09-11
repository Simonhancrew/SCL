#include <iostream>
#include <vector>

/*
    数位dp的通解一般分为两步
    1 根绝感兴趣的部分，设置dp的状态和转移方程
    2 然后按数的每一个二进制位去讨论具体的情况


    比如这道题，感兴趣的部分是比n小的数得二进制表示下，没有连续1得数的个数
    dp[i][1 or 0] 表示有i位，最高位是1或0的时候，这个数有多少个
    之后我们分情况的谈论n的每一位，是1的话，可以选个更小的，可以加上dp[i][0]，有连续的1的时候就结束了
    最后能够遍历完所有的位的话，说明n本身也是合法的，要加入答案中
*/

using namespace std;

const int N = 32;

int dp[32][2];

int main(){
    int n;
    cin >> n;
    dp[1][0] = 1,dp[1][1] = 1;
    vector<int> num;
    while(n){
        num.push_back(n & 1);
        n >>= 1;
    }

    for(int i = 2;i <= num.size();i++){
        dp[i][0] = dp[i - 1][0] + dp[i - 1][1];
        dp[i][1] = dp[i - 1][0];
    }

    int res = 0;
    for(int i = num.size(),pre = 0;i;i--){
        if(num[i - 1]){
            res += dp[i][0];
            if(pre){
                cout << res << endl;
                return 0;
            }
        }
        pre = num[i - 1];
    }
    cout << res + 1 << endl;
    return 0;
}