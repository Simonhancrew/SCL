//一个剑指offer的题目原题做法是统计每一位01的个数之后还原这个数

#if 0
class Solution {
public:
    int findNumberAppearingOnce(vector<int>& nums) {
        int res = 0;
        for(int i = 31;i >= 0;i--){
            int cnt = 0;
            for(auto x : nums){
                if(x >> i & 1) cnt++;
            }
            if(cnt % 3 == 1) res |= 1 << i;
        }
        return res;
    }
};
#endif

// 其实还有更好的做法，其实是一个状态机的思路，具体推一下就可以了
class Solution {
 public:
  int findNumberAppearingOnce(vector<int>& nums) {
    int one = 0, two = 0;
    for (auto x : nums) {
      one = (one ^ x) & ~two;
      two = (two ^ x) & ~one;
    }
    return one;
  }
};