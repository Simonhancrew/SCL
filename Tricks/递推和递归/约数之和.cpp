#include <iostream>

using namespace std;

const int P = 9901;

/*
    约数之和的公式是：
    （a[0] + a[1] + ..+ a[k]） * (b[0] + ... + b[x]) * ...
    其中a是质因子，a[x]求a的x次方
    不难发现只要做一个质因子的等比求和之后相乘就能得到答案
    关键点就在于快速求得等比之和，用一个分治的思路考虑（类似此类问题都可以考虑这种方式）
*/

int qmi(int a,int b) {
    int res = 1;
    a %= P;
    while(b){
        if(b & 1) res = (res * a) % P;
        b >>= 1;
        a = (a * a) % P;
    }
    return res;
}


/*
    等比数列求和: a[0] + a[1] + ... + a[k - 1]
    折半：  
        前半部分：a[0] + ... + a[k / 2 - 1]
        后半部分：a[k / 2] + ... + a[k - 1]
        不难发现一个乘以a[k / 2]的关系
        sum(a,k) = sum(a,k / 2) + a[k / 2] * sum(a,k / 2)
*/
int sum(int a,int k) {
    if(k == 1) return 1;
    if(k % 2 == 0) return (1 + qmi(a,k / 2)) * sum(a,k / 2) % P;
    return (sum(a,k - 1) + qmi(a,k - 1)) % P;
}


int main()
{
    int a,b;
    cin >> a >> b;
    int res = 1;
    for(int i = 2;i <= a / i;i++) {
        if(a % i == 0) {
            int s = 0;
            while(a % i == 0) {
                s++;
                a /= i;
            }
            res = (res * sum(i,b * s + 1)) % P;
        }
    }
    if(a > 1) res = (res * sum(a,b + 1)) % P;
    if(a == 0) res = 0;
    cout << res << endl;
}