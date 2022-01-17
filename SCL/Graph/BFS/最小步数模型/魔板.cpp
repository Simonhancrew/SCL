#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

/*
    带方案记录的最短路，将st变成记录前一个状态的数组
    在更新的过程中，顺序加入ABC三个变换，能够保证解是最小字典序
    因为在队列中的解一定是按照字典序排列的
*/

char g[2][4];
unordered_map<string,int> dist;
unordered_map<string,pair<char,string>> pre;

void set(string state) {
    for(int i = 0;i < 4;i++) g[0][i] = state[i];
    for(int i = 7,j = 0;j < 4;j++,i--) g[1][j] = state[i];
}

string get(){
    string ans;
    for(int i = 0;i < 4;i++) ans += g[0][i];
    for(int i = 3;i >= 0;i--) ans += g[1][i];
    return ans;
}

string move0(string state) {
    set(state);
    for(int i = 0;i < 4;i++) swap(g[0][i],g[1][i]);
    return get();
}

string move1(string state) {
    set(state);
    char s1 = g[0][3],s2 = g[1][3];
    for(int i = 0;i < 2;i++) {
        for(int j = 3;j >= 1;j--) {
            g[i][j] = g[i][j - 1];
        }
    }
    g[0][0] = s1,g[1][0] = s2;
    return get();
}

string move2(string state) {
    set(state);
    char t = g[0][1];
    g[0][1] = g[1][1];
    g[1][1] = g[1][2];
    g[1][2] = g[0][2];
    g[0][2] = t;
    return get();
}

void bfs(string start,string end){
    if(start == end) {
        dist[end] = 0;
        return;
    }
    queue<string> q;
    q.push(start);
    dist[start] = 0;
    while(q.size()){
        auto t = q.front();
        q.pop();
        string m[3];
        m[0] = move0(t);
        m[1] = move1(t);
        m[2] = move2(t);
        for(int i = 0;i < 3;i++){
            if(!dist.count(m[i])) {
                q.push(m[i]);
                dist[m[i]] = dist[t] + 1;
                pre[m[i]] = {char(i + 'A'),t};
                if(m[i] == end) return;
            }
        }
    }
}

int main(){
    string start,end;
    for(int i = 0;i < 8;i++){
        int t;
        cin >> t;
        end += char(t + '0');
    }   
    for(int i = 0;i < 8;i++) start += char('1' + i);
    bfs(start,end);
    int cnt = dist[end];
    cout << cnt << endl;
    string ans;
    while(end != start) {
        ans += pre[end].first;
        end = pre[end].second;
    }
    reverse(ans.begin(),ans.end());
    if(cnt > 0) cout << ans << endl;
    return 0;
} 