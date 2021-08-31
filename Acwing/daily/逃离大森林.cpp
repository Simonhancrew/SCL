#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

// 这是一系列贪心捕获题目的模板，能在路线中间捕获步行者的捕获者，一定能在终点也捕获到。
// 然后根据三角形法则，捕获者的路径是否比步行者的路劲短，是的话就直接能够捕获了。

using namespace std;

const int N = 1e3 + 10;

typedef pair<int, int> PII;

int d[N][N];
char g[N][N];

int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
int r,c;


int bfs(){
    memset(d,0x3f,sizeof d);
    int sx,sy;
    for(int i = 0;i < r;i++){
        for(int j = 0;j < c;j++){
            if(g[i][j] == 'E'){
                sx = i,sy = j;
            }
        }
    }
    queue<PII> q;
    q.push({sx,sy});
    d[sx][sy] = 0;
    while(q.size()){
        auto t = q.front();
        q.pop();
        for(int i = 0;i < 4;i++){
            int x = t.first + dx[i],y = t.second + dy[i];
            if(x >= 0 && y >= 0 && x < r && y < c && g[x][y] != 'T'){
                if(d[x][y] > d[t.first][t.second] + 1){
                    d[x][y] = d[t.first][t.second] + 1;
                    q.push({x,y});
                }
            }
        }
    }
    
    for(int i = 0;i < r;++i){
        for(int j = 0;j < c;++j){
            if(g[i][j] == 'S'){
                return d[i][j];
            }
        }
    }
    return -1;
}


int main()
{
    scanf("%d%d",&r,&c);
    for(int i = 0;i < r;i++){
        scanf("%s",g[i]);
    }
    int t = bfs();
    int res = 0;
    for(int i = 0;i < r;i++){
        for(int j = 0;j < c;j++){
            if(g[i][j] > '0' && g[i][j] <= '9' && d[i][j] <= t){
                res += g[i][j] - '0';
            }
        }
    }
    printf("%d\n",res);
}