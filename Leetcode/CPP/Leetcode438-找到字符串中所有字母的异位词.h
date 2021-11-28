#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findAnagrams(const string &s,const string &p) {
        unordered_map<char, int> cnt;
        size_t n = s.size(),m = p.size();
        for (auto c: p) cnt[c] ++ ;
        vector<int> res;
        size_t tot = cnt.size();
        for(int i = 0,j = 0,sa = 0;j < n;j++){
            if(cnt.count(s[j])) {
                cnt[s[j]]--;
                if(cnt[s[j]] == 0) sa++;
            }
            if(j - i + 1 == m){
                if(sa == tot) res.push_back(i);
                if(cnt.count(s[i])){
                    if(cnt[s[i]] == 0) sa--;
                    cnt[s[i]]++;
                }
                i++;
            }

        }
        return res;
    }
};
