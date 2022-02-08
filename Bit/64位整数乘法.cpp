#include <iostream>

using namespace std;

typedef long long LL;

LL a,b,p;

/*
    龟速乘法，把b编程二进制表示，主要为了不爆范围
        3 * 7 = 21，其中7 = （111）二进制
    可以转化为：
        3 * （2 ** 0） 
        3 * （2 ** 1）
        3 * （2 ** 2）
    做一个乘法和加法
*/

LL qadd(LL a,LL b,LL p) {
    LL res = 0;
    while(b) {
        if(b & 1) res = (res + a) % p;
        b >>= 1;
        a = (a * 2) % p;
    }
    return res;
}

int main(){
    cin >> a >> b >> p;
    cout << qadd(a,b,p) << endl;
    return 0;
}