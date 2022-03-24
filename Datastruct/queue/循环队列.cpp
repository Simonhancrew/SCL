#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/03/24

using namespace std;

typedef long long LL;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr)

const int INF = 0x3f3f3f3f,N = 1e3 + 10;

int q[N];
int hh,tt; // hh是队头，tt是队尾
int n;

// 插入操作
void push(int x) {
    q[tt++] = x;
    if(tt == N) tt = 0;
}

// 弹出操作
int pop(){
    int t = q[hh++];
    if(hh == N) hh = 0;
    return t;
}

int main(){
    fast_cin();
    cin >> n;
    // 初始循环队列
    hh = 0,tt = 0;

    for(int i = 0;i < n;i++) {
        int x;
        cin >> x;
        push(x);     
    }

    // 队列不空
    while(tt != hh) {
        int t = pop();
        cout << t << endl;
    }
    
    return 0;
}