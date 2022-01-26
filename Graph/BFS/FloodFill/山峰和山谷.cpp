#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

/*
    在做flood fill的时候携带边缘信息辅助判断，判断区域周长的也可以在bfs中增加判断累加
*/

#define fast_cin() ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
typedef pair<int, int> PII;
#define x first
#define y second

const int N = 1e3 + 10,M = 1e6 + 10;

int w[N][N];
int n;
PII q[M];
bool st[N][N];

void bfs(int x,int y,bool& has_higher,bool& has_lower){
    int hh = 0,tt = 0;
    q[0] = {x,y};
    st[x][y] = true;
    while(hh <= tt){
        auto t = q[hh++];
        for(int i = t.x - 1;i <= t.x + 1;i++){
            for(int j = t.y - 1;j <= t.y + 1;j++){
                if(i == t.x && j == t.y) continue;
                if(i < 0 || i >= n || j < 0 || j >= n) continue;
                if(w[i][j] != w[x][y]) {
                        if(w[i][j] < w[x][y]) has_lower = true;
                        else has_higher = true;
                }else if(!st[i][j]){
                    q[++tt] = {i,j};
                    st[i][j] = true;
                }
            }
        }
    }
}

int main(){
    fast_cin();
    cin >> n;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++) {
            cin >> w[i][j];
        }
    }
    int peak = 0,valley = 0;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            if(!st[i][j]) {
                bool has_higher = false,has_lower = false;
                bfs(i,j,has_higher,has_lower);
                if(!has_higher) ++peak; // 没有比他高的就是山峰
                if(!has_lower) ++valley; // 没有比他矮的就是山谷
            }
        }
    }    
    cout << peak << ' ' << valley << endl; 
}