class DetectSquares {
public:
    map<int,map<int,int>> mp;
    DetectSquares() {

    }
    
    void add(vector<int> point) {
        int x = point[0],y = point[1];
        mp[x][y]++;
    }
    
    int get(int x,int y){
        if(not mp.count(x)) return 0;
        if(not mp[x].count(y)) return 0;
        return mp[x][y];
    }
    // map枚举第2，3，4个点就可以了
    int count(vector<int> point) {
        int x = point[0],y = point[1];
        int res = 0;
        for(auto [y1,c] : mp[x]){
            if(y1 != y){
                res += c * get(x + abs(y1 - y),y1) * get(x + abs(y1 - y),y);
                res += c * get(x - abs(y1 - y),y1) * get(x - abs(y1 - y),y); 
            }
        }
        return res;
    }
};