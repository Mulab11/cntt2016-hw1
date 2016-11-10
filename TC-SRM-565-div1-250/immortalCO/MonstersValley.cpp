#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

// 在前面 i 轮中中，最多花费 j 元获得的最大攻击力
ll f[60][110];

void cmax(ll &a, ll b) {a < b ? a = b : 0;}
class MonstersValley
{
public:
	int minimumPrice(vector<ll> val, vector<int> cost)
	{
		int sum = 0;
		for(int i = 0; i != (int) val.size(); ++i)
		{
			memset(f[i + 1], -63, (sum + cost[i] + 1) << 3);
			for(int j = 0; j <= sum; ++j)
			{
				cmax(f[i + 1][j + cost[i]], f[i][j] + val[i]);
				if(f[i][j] < val[i]) continue; // 必须雇佣
				cmax(f[i + 1][j], f[i][j]);
			}
			sum += cost[i];
		}
		for(int i = 0; i <= sum; ++i)
			if(f[val.size()][i] >= 0) return i;
		return -1;
	}
}	user;
