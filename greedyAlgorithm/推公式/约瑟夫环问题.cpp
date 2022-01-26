// 一个简单的递推问题，注意要重新对齐坐标
class Solution {
public:
    int lastRemaining(int n, int m){
        if(n == 1) return 0;
        return (lastRemaining(n - 1,m) + m) % n;
    }
};