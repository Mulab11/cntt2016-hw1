#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MaxN = 60;
int d[MaxN];
bool e[MaxN][MaxN];

class PenguinSledding
{
public:
    ll countDesigns(int n, vector<int> ex, vector<int> ey)
    {
        int m = ex.size();
        for(int i = 0; i != m; ++i)
            ++d[ex[i]], ++d[ey[i]],
            e[ex[i]][ey[i]] = e[ey[i]][ex[i]] = 1;
        // 最后的图一定是一个点出发的菊花或三元环
        // 没有任何边的情况多计算了 n - 1 次
        // 只有一条边的情况多计算了 m 次
        ll ans = - (n - 1 + m);
        for(int i = 1; i <= n; ++i)
            for(int j = i + 1; j <= n; ++j)
                for(int k = j + 1; k <= n; ++k)
                    if(e[i][j] && e[j][k] && e[k][i])
                        ++ans;
        for(int i = 1; i <= n; ++i) ans += 1ll << d[i];
        return ans;
    }
}	user;
