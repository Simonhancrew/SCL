#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e3 + 10;

int a[N],dp[N],q[N],n;

// 分成两个问题，
// 第一个，最长不升子序列长度
// 第二个，配备多少系统，等价于之前那个LIS的贪心做法，把当前的数接在多个序列中第一个满足条件的末尾

int main(){
    while(cin >> a[n]) n++;
    int res = 0,cnt = 0;
    for(int i = 0;i < n;i++){
        dp[i] = 1;
        for(int j = 0;j < i;j++){
            if(a[j] >= a[i]) dp[i] = max(dp[i],dp[j] + 1);
        }
        res = max(res,dp[i]);
        int k = 0;
        while(k < cnt && q[k] < a[i]) k++;
        if(k == cnt) q[cnt++] = a[i];
        else q[k] = a[i]; 
    }
    cout << res << endl;
    cout << cnt << endl;
    return 0;
}