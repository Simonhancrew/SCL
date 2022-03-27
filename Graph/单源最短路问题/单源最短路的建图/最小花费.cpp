#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/03/25

using namespace std;

/*
    路径是乘的情况下转换成最短路
    因为要让乘过费率之后的值到达100，且起点的价钱足够小。等价于乘法原理，要让乘出来的值尽可能的大：
        f = w1 * w1 * .... * wn
    做一个公式转化
        log(f) = log(w1) + log(w2) + ... + log(wn)
    要让log(f)尽可能的大，因为w在[0,1]之间，log(w)是负的
    于是等价于要让-log(f)尽可能的小
*/

const int N = 2e3 + 10;

int n,m;
double g[N][N],d[N];
bool st[N];
int s,t;

void dijstra() {
    d[s] = 1;
    for(int i = 0;i < n;i++) {
        int tmp = -1;
        for(int j = 1;j <= n;j++) {
            if(!st[j] && (tmp == -1 || d[j] > d[tmp])) {
                tmp = j;
            }
        }
        st[tmp] = true;
        for(int j = 1;j <= n;j++) {
            d[j] = max(d[j],d[tmp] * g[tmp][j]);
        }
    }
}

int main(){
    cin >> n >> m;
    for(int i = 0;i < m;i++) {
        int x,y,z;
        cin >> x >> y >> z;
        double dis = (100.0 - z) / 100;
        g[x][y] = g[y][x] = max(dis,g[x][y]); 
    }
    cin >> s >> t;
    dijstra();

    printf("%.8lf\n",100 / d[t]);
    return 0;
}