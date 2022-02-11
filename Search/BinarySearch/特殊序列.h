/*
    满足归并排序的思路，不传递关系
    取巧
*/
#if 0
class Solution {
public:
    vector<int> specialSort(int N) {
        vector<int> nums;
        for(int i=1;i<=N;++i) nums.push_back(i);
        stable_sort(nums.begin(),nums.end(),compare);
        return nums;
    }
};
#endif
/*
    二分插入的位置
*/
class Solution {
public:
    vector<int> specialSort(int N) {
        vector<int> res(1,1);
        for(int i = 2;i <= N;i++) {
            int l = 0,r = res.size() - 1;
            while(l < r) {
                int mid = l + r + 1 >> 1;
                if(compare(res[mid],i)) l = mid;
                else r = mid - 1;
            }
            res.push_back(i);
            for(int j = res.size() - 2;j > r;j--) swap(res[j],res[j + 1]);
            if(compare(i,res[r])) swap(res[r],res[r + 1]);
        }
        return res;
    }
};