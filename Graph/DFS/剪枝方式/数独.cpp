#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

/*
    利用位运算优化枚举
    1. 首先枚举当前分支最少的节点
        利用mp记录每个[0,1 << N]这些数中每个数二进制中1的个数
    2. 其次，每个节点可以枚举的数可以使用二进制优化
        考虑同行，同列，同网格填了那些数，然后可以填的数就取一个&
        然后提取出可以填的状态数中的1可以采用lowbit，并开额外数组记录就能O(1)的确定
        当前可以填的数
    3. 只要找到了一个合法情况就可以直接返回
*/

const int N = 9,M = 1 << 9;

char s[100];
int mp[M],ones[M];
int row[N],col[N],cell[3][3];


int lowbit(int x)  // 返回末尾的1
{
    return x & -x;
}

int get(int x,int y) {
    return row[x] & col[y] & cell[x / 3][y / 3];
}

void draw(int x,int y,int t,bool set) {
    if(set) s[x * 9 + y] = '1' + t;
    else s[x * 9 + y] = '.';
    
    int v = 1 << t;
    if(!set) v = -v;
    
    row[x] -= v;
    col[y] -= v;
    cell[x / 3][y / 3] -= v;
}

void init(){
    for(int i = 0;i < N;i++) row[i] = col[i] = (1 << N) - 1;
    for(int i = 0;i < 3;i++) {
        for(int j = 0;j < 3;j++) {
            cell[i][j] = (1 << N) - 1;
        }
    }
}

bool dfs(int cnt) {
    if(!cnt) return true; // 全部填完了
    int x,y,st;
    int mn = 10;
    // 优先少分支，找到可以填的，且可以填数最少的节点
    for(int i = 0;i < N;i++) {
        for(int j = 0;j < N;j++) {
            if(s[i * N + j] == '.') {
                st = get(i,j);
                if(ones[st] < mn) { // 可以填的数更少
                    mn = ones[st];
                    x = i,y = j;
                }
            }
        }
    }
    st = get(x,y);  // 二进制表示的那些数可以填
    for(int i = st;i;i -= lowbit(i)) {
        int t = mp[lowbit(i)];
        draw(x,y,t,true);
        if(dfs(cnt - 1)) return true;
        draw(x,y,t,false);
    }
    
    return false;
}

int main(){
    /*
        辅助数组，s = XXXXXXXXX（9位）中，s[i] = 1表示当前数可以选
        lowbit用到后来确定哪一位为1，用mp记录
    */ 
    for(int i = 0;i < N;i++) mp[1 << i] = i;  
    for(int i = 0;i < (1 << N);i++) {
        for(int j = 0;j < N;j++) {
            ones[i] += (i >> j) & 1;
        }
    }
    while(cin >> s,s[0] != 'e') {
        init();
        int cnt = 0;
        for(int i = 0;i < 9;i++) {
            for(int j = 0;j < 9;j++) {
                if(s[i * 9 + j] != '.') {
                    int t = s[i * 9 + j] - '1';
                    draw(i,j,t,true);
                }
                else cnt++; // 当前要搜索的总位置数
            }
        }
        dfs(cnt);
        cout << s << endl;
    }
    return 0;
}