#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

// Created by Simonhancrew on 2022/02/12

using namespace std;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr)

/*
    对顶堆，平衡树也可以做
*/

int n,m,p;

int main()
{
    cin >> p;
    while(p--) 
    {
        cin >> m >> n;
        cout << m << ' ' << (n + 1) / 2 << endl;
        priority_queue<int> down;
        priority_queue<int,vector<int>,greater<int>> up;
        int cnt = 0;
        for(int i = 1;i <= n;i++)
        {
            int x;
            cin >> x;
            if(down.empty() || x < down.top()) down.push(x);
            else up.push(x);
            
            if(down.size() > up.size() + 1) up.push(down.top()),down.pop();
            if(down.size() < up.size()) down.push(up.top()),up.pop();
            
            if(i & 1) 
            {
                cout << down.top() << ' ';
                if(++cnt % 10 == 0) cout << endl;
            }
        }
        if(cnt % 10) cout << endl;
    }
    return 0;
}