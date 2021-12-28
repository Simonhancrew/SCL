#include <unordered_map>
#include <vector>

using namespace std;

using ULL = unsigned long long;
const int p = 13331;
class Solution {
public:
    unordered_map<ULL,vector<string>> mp;
    void insert(const string& s){
        ULL h = 0;
        int n = s.size();
        for(int i = 0;i < n;i++){
            h = h * 131 + s[i];
        }
        mp[h].push_back(s);
    }

    bool find(ULL v,const string& s){
        if(mp.find(v) == mp.end()) return false;
        for(const string& ss : mp[v]){
            if(ss == s) return true;
        }
        return false;
    }


    bool check(const string &s){
        int n = s.size();
        vector<bool> f(n + 1,false);
        f[0] = 1;
        for(int i = 0;i < n;i++){
            if(!f[i]) continue;
            ULL v = 0;
            string t;
            for(int j = i + 1;j < n;j++){
                v = v * 131 + s[j - 1];
                t += s[j - 1];
                if(!f[j] && find(v,t)) f[j] = true;
            }
            v = v * 131 + s[n - 1];
            t += s[n - 1];
            if(i > 0 && find(v,t)) return true;
        }
        return false;
    }
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        for(auto &word : words) insert(word);
        vector<string> ans;
        for(auto &word : words){
            if(check(word)) ans.push_back(word);
        }
        return ans;
    }
};