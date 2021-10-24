#include <vector>
#include <algorithm>

using namespace std;

const int N = 1771561;
const int INF = 1000000000;

class Solution {
private:
    int f[N];
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special,
        vector<int>& needs) {

        const int n = needs.size();

        vector<int> mul(n + 1);
        mul[0] = 1;
        for (int i = 0; i < n; i++)
            mul[i + 1] = mul[i] * (needs[i] + 1);

        f[0] = 0;
        for (int s = 1; s < mul[n]; s++) {
            f[s] = INF;
            vector<int> c(n);
            for (int i = 0; i < n; i++)
                c[i] = s % mul[i + 1] / mul[i];

            for (int i = 0; i < n; i++)
                if (c[i] > 0)
                    f[s] = min(f[s], f[s - mul[i]] + price[i]);

            for (const auto &offer : special) {
                int t = s;
                for (int i = 0; i < n; i++)
                    if (c[i] >= offer[i]) {
                        t -= offer[i] * mul[i];
                    } else {
                        t = -1;
                        break;
                    }

                if (t != -1)
                    f[s] = min(f[s], f[t] + offer[n]);
            }
        }

        return f[mul[n] - 1];
    }
};