#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2021/10/27

using namespace std;

const int N = 60,mod = 1e9 + 7;

// 利用kmp求一个s的ne数组，要求最后形成的字符串不能包含字串s => 不能在转移过程中跳到终点。
// 考虑用状态机dp的思路求解
// dp[i][j]已经形成了前i个字符，且在子串s中的next数组的位置来到了j的字符方案数
// 第i + 1位每次转移枚举26个字母，然后转移j的状态（注意此时要用一个备份）
// 最后dp[i + 1][u]就是枚举当前这个字字母的时候转移的最终状态方程，它由最初的f[i][j]种转移过来的
// 最后的结果就是dp[i][x]的求和

int f[N][N],n,ne[N];
string s;

int main(){
    cin.sync_with_stdio(false);
    cin >> n >> s;
    int m = s.size();
    s = " " + s;
    for(int i = 2,j = 0;i <= m;i++){
        while(j && s[i] != s[j + 1]) j = ne[j];
        if(s[i] == s[j + 1]) j++;
        ne[i] = j; 
    }
    f[0][0] = 1;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            for(char k = 'a';k <= 'z';k++){
                int u = j;
                while(u && k != s[u + 1]) u = ne[u];
                if(k == s[u + 1]) u++;
                if(u < m) f[i + 1][u] = (f[i + 1][u] + f[i][j]) % mod; 
            }
        }
    }
    int res = 0;
    for(int i = 0;i < m;i++) res = (res + f[n][i]) % mod;
    cout << res << endl;
    return 0;
}