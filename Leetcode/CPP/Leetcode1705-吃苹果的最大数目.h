class Solution {
public:
    typedef pair<int,int> PII;
    int eatenApples(vector<int>& apples, vector<int>& days) {
        auto cmp = [](PII& lhs,PII& rhs) {
            return lhs.second > rhs.second;
        };
        int n = apples.size(),ans = 0,time = 0;
        priority_queue<PII,vector<PII>,decltype(cmp)> heap(cmp);
        while(!heap.empty() || time < n){
            if(time < n && apples[time] > 0) heap.emplace(PII{apples[time],days[time] + time - 1});
            while(!heap.empty() && heap.top().second < time) heap.pop();
            if(!heap.empty()){
                auto t = heap.top();
                heap.pop();
                if(--t.first > 0 && t.second > time) heap.emplace(t);
                ++ans;
            }
            ++time;
        }
        return ans;
    }
};