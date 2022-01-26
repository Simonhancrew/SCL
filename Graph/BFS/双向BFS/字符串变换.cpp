#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

const int N = 7;

/*
    BFS针对最短路模型的一个优化手段
    从两边都开始搜索，优先搜队列小的那个
    单次扩充队列某一层的时候，如果在另外一个方向搜索的过程中搜索到了这个节点的话
    就说明确定了一个路径
    值得注意的一点就是代码过程中应该在extend中一次完成一层的更新，就是在更新da的时候，保证此时db中最顶点部分都是同一层的
*/

string A,B;
int n;
string a[N],b[N];
unordered_map<string,int> da,db;

int extend(queue<string>& q,unordered_map<string,int> &da,unordered_map<string,int> &db,string a[],string b[]){
    int d = da[q.front()];
    int ans = 11;
    while(q.size() && da[q.front()] == d){
        auto t = q.front();
        q.pop();
        for(int i = 0;i < n;i++) {
            for(int j = 0;j < t.size();j++) {
                if(t.substr(j,a[i].size()) == a[i]) {
                    string r = t.substr(0,j) + b[i] + t.substr(j + a[i].size());
                    if(db.count(r)) ans = min(ans,da[t] + 1 + db[r]); 
                    if(da.count(r)) continue;
                    da[r] = da[t] + 1;
                    q.push(r);
                }
            }
        }
    }
    return ans;
}

int bfs(){
    if(A == B) return 0;
    queue<string> qa,qb;
    qa.push(A);
    qb.push(B);
    da[A] = 0,db[B] = 0;
    int step = 0;
    while(qa.size() && qb.size()) {
        int t;
        if(qa.size() < qb.size()) t = extend(qa,da,db,a,b);
        else t = extend(qb,db,da,b,a);
        
        if(t <= 10) return t;
        if(++step == 10) return -1; 
    }
    return -1;
}

int main(){
    cin >> A >> B;
    while(cin >> a[n] >> b[n]) n++;
    int t = bfs();
    if(t == -1) cout << "NO ANSWER!"  << endl;
    else cout << t <<endl;
    return 0;
}