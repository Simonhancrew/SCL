#include <vector>
using namespace std;

class Solution {
public:
    int maximumDifference(vector<int>& nums) {
        int res = -1;
        for(int i = 0;i < nums.size();i++){
            for(int j = i + 1;j < nums.size();j++){
                if(nums[j] > nums[i]) res = max(res,nums[j] - nums[i]);
            }
        }
        return res;
    }
};