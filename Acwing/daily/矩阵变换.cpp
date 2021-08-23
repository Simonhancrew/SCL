
// 一道贪心的题目，最后能变成一样的行一定最初也是一样的。只要统计最初一样的就可以了。


#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int N = 110;

unordered_map<string,int> mp;

int main(){
    int n;
    cin >> n;
    int res = 0;
    for(int i = 0;i < n;i++){
        string s;
        cin >> s;
        mp[s] ++;
        res = max(res,mp[s]);
    }
    cout << res << endl;
}
