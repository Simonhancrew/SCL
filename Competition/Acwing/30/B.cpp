#include <iostream>
#include <cstring>
#include <algorithm>
#include <stack>

using namespace std;

const int N = 1e6 + 10;

/*
    1 左括号大于等于右括号
    2 ( == )
    括号序列的题目
*/

int main(){
    string s;
    cin >> s;
    int n = s.size();
    int res = 0,cnt = 0;
    stack<int> st;
    st.push(-1);
    for(int i = 0;i < n;i++){
        if(s[i] == '(') {
            st.push(i);
        }else{
            st.pop();
            if(st.empty()) {
                st.push(i);
            }else{
                int t = i - st.top();
                if(res < t) res = t,cnt = 1;
                else if(res == t) cnt++;
            }
        }
    }    
    if(res) cout << res << ' ' << cnt;
    else cout << 0 << ' ' << 1;
}