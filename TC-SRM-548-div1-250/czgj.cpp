#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
class KingdomAndTrees {
    public:
    int minLevel(vector <int> heights) {
        int n = heights.size();
        vector <int> tmp;
        LL l = -1, r = 2000000000, mid, x;
        bool ok;
        while (l + 1 < r) {
            mid = (l + r) / 2;
            ok = true;
            tmp = heights;
            tmp[0] = max(1ll, tmp[0] - mid);
            for (int i = 1; i < n; ++i) {
                if (tmp[i] > tmp[i - 1]) x = max(tmp[i - 1] + 1ll, tmp[i] - mid);
                else x = min(tmp[i - 1] + 1ll, tmp[i] + mid);
                if (abs(tmp[i] - x) > mid || x <= tmp[i - 1]) {ok = false; break;}
                else tmp[i] = x;
            }
            if (ok) r = mid; else l = mid;
        }
        return r;
    }
};
