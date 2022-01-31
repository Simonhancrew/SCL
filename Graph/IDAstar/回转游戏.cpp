#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 24;

/*
      0     1
      2     3
4  5  6  7  8  9  10
      11    12 
13 14 15 16 17 18 19
      20 21 22 
      23    24
*/

// 打表记录每个操作的数组坐标
int op[8][7] = {
    {0, 2, 6, 11, 15, 20, 22},
    {1, 3, 8, 12, 17, 21, 23},
    {10, 9, 8, 7, 6, 5, 4},
    {19, 18, 17, 16, 15, 14, 13},
    {23, 21, 17, 12, 8, 3, 1},
    {22, 20, 15, 11, 6, 2, 0},
    {13, 14, 15, 16, 17, 18, 19},
    {4, 5, 6, 7, 8, 9, 10}
};

// 记录中心的8个数
int center[8] = {6,7,8,12,17,16,15,11};
int oppsite[8] = {5,4,7,6,1,0,3,2}; // 一个剪枝操作，不要和之前的一个操作对冲，避免无效
int q[N];
int path[100];
int sum[4];//记录中心一圈中最多的数个数

// 启发函数，一次移动只能改变一个数，最少需要8 - （环中最多的数）的移动次数
int f(){
    memset(sum,0,sizeof sum);
    for(int i = 0;i < 8;i++) sum[q[center[i]]]++;
    int mx = 0;
    for(int i =  1;i <= 3;i++) mx = max(mx,sum[i]);
    return 8 - mx;
}

// 移动q数组
void operate(int x){
    int t = q[op[x][0]];
    for(int i = 0;i < 6;i++) q[op[x][i]] = q[op[x][i + 1]];
    q[op[x][6]] = t;
}

bool dfs(int depth,int max_depth,int pre) {
    if(depth + f() > max_depth) return false;
    if(f() == 0) return true;

    for(int i = 0;i < 8;i++) {
        if(pre != oppsite[i]) {
            operate(i);
            path[depth] = i;
            if(dfs(depth + 1,max_depth,i)) return true;
            operate(oppsite[i]); // 回溯
        }
    }
    return false;
}


int main(){
    while(cin >> q[0],q[0]) {
        for(int i = 1;i < 24;i++) cin >> q[i];
        int depth = 0;
        while(!dfs(0,depth,-1)) depth++; // 迭代加深IDA*
        if(depth == 0) puts("No moves needed");
        else {
            for(int i = 0;i < depth;i++) cout << char('A'+ path[i]);
            cout << endl;
        }
        cout << q[6] << endl;
    }	
    return 0;
}