#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

const int N = 5e4 + 10;

int n;
vector<int> arr;

class Solution {
public:
    unordered_map<int,vector<int>> mp;
    queue<int> qa,qb;
    vector<int> da,db;
    int n;
    int extend(queue<int> &q,vector<int> &da,vector<int> &db,vector<int> const &arr) {
        int d = da[q.front()];
        /*
            一次更新一整层,total distance = dist[t] + 1 + rdist[cur];
            dist[cur] = dist[pre] + 1;
            total dist = dist[pre] + 1 + rdist[cur];
        */ 
        while(q.size() && d == da[q.front()]) {
            auto t = q.front();
            q.pop();
            for(int ne : mp[arr[t]]) {
                if(db[ne] != -1) return da[t] + 1 + db[ne];
                if(da[ne] == -1) {
                    da[ne] = da[t] + 1;
                    q.push(ne);
                }
            }
            mp.erase(arr[t]);
            if(t + 1 < n && da[t + 1] == -1) {
                if(db[t + 1] != -1) return da[t] + 1 + db[t + 1];
                da[t + 1] = da[t] + 1;
                q.push(t + 1);
            }
            if(t - 1 >= 0 && da[t-1] == -1) {
                if(db[t - 1] != -1) return da[t] + db[t - 1] + 1;
                da[t - 1] = da[t] + 1;
                q.push(t - 1);
            }
        }
        // 当前没有搜到通路就继续搜索
        return -1;
    }
    int minJumps(vector<int>& arr) {
        n = arr.size();
        if(n == 1) return 0;
        for(int i = 0;i < n;i++) {
            mp[arr[i]].push_back(i);
        }
        qa.push(0),qb.push(n - 1);
        da.resize(n,-1),db.resize(n,-1);
        da[0] = 0,db[n - 1] = 0; 
        /*
            每次搜小的队列  
            且要保证两个点是能够联通的，一个队列为空之后还没搜到结果表明
            当前是不和另一个点联通的
        */ 
        while(qa.size() && qb.size()) { 
            int t;
            if(qa.size() < qb.size()) t = extend(qa,da,db,arr);
            else t = extend(qb,db,da,arr);
            if(t != -1) return t;
        }
        return -1;
    }
};

int main(){
    cin >> n;
    arr.resize(n);
    for(int i = 0;i < n;i++) cin >> arr[i];
    Solution solve;
    cout << solve.minJumps(arr) << endl;
    return 0;
}