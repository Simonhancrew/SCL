#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int n;
    vector<unordered_map<int, int>> f;
    vector<int> price;
    vector<vector<int>> special;

    int dp(int x, int y) {
        if (f[x].count(y)) return f[x][y];
        if (!x) {
            f[x][y] = 0;
            for (int i = 0; i < n; i ++ ) {
                int c = y >> i * 4 & 15;
                f[x][y] += c * price[i];
            }
            return f[x][y];
        }
        f[x][y] = dp(x - 1, y);
        int state = 0;
        auto s = special[x - 1];
        for (int i = n - 1; i >= 0; i -- ) {
            int c = y >> i * 4 & 15;
            if (c < s[i]) {
                state = -1;
                break;
            }
            state = state * 16 + c - s[i];
        }
        if (state != -1)
            f[x][y] = min(f[x][y], dp(x, state) + s.back());
        return f[x][y];
    }

    int shoppingOffers(vector<int>& _price, vector<vector<int>>& _special, vector<int>& needs) {
        price = _price, special = _special;
        n = price.size();
        f = vector<unordered_map<int, int>>(special.size() + 1, unordered_map<int, int>());
        int state = 0;
        for (int i = needs.size() - 1; i >= 0; i -- )
            state = state * 16 + needs[i];
        return dp(special.size(), state);
    }
};