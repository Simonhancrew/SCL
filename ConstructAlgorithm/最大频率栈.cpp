#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>

using namespace std;

// 开不同频率的栈，如果当前频率的栈空了
// 最大频率需要-1

class FreqStack {
public:
    FreqStack() {

    }
    
    void push(int val) {
        freq[val]++;
        rec[freq[val]].push_back(val);
        mx = max(freq[val], mx);
    }
    
    int pop() {
        int res = rec[mx].back();
        rec[mx].pop_back();
        freq[res]--;
        if (rec[mx].empty()) mx--;
        return res;
    }

    unordered_map<int, int> freq;
    unordered_map<int, vector<int>> rec;
    int mx = 0;
};


