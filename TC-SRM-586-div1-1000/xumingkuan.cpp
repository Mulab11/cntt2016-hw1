#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <cassert>
using namespace std;
const int oo = 1010101010, MAXN = 27;
class StringWeight
{
private:
	int f[2][MAXN][MAXN];//f[i & 1][j][k]: strings 0~i, j chosen letters, only k of which are allowed to appear afterwards, min weight
public:
	int getMinimum(vector<int> L)
	{
		memset(f[1], 63, sizeof(f[1]));
		f[1][0][0] = 0;
		int prevminj = 0;//min j where f[~i & 1][j][k] < oo
		for(int i = 0; i < L.size(); i++)
		{
			memset(f[i & 1], 63, sizeof(f[i & 1]));
			int now, nowminj = max(min(26, L[i]), prevminj); 
			for(int j1 = prevminj; j1 <= 26; j1++)
				for(int k1 = 0; k1 <= j1; k1++)
					if((now = f[~i & 1][j1][k1]) < oo)
						for(int j2 = max(j1 + max(0, min(26, L[i]) - k1), nowminj); j2 <= min(26, j1 + L[i]); j2++)
							for(int k2 = 0; k2 <= j2 - j1 + k1; k2++)
							{
								const int tmp1 = min(k2, j2 - j1);//first appearance
								const int tmp2 = k2 - tmp1;//neither last nor first appearance
								const int tmp3 = k1 - tmp2;//last appearance
								f[i & 1][j2][k2] = min(f[i & 1][j2][k2], now + tmp3 * (tmp3 + 1) / 2 + tmp1 * (tmp1 - 1) / 2 + tmp2 * L[i] + (!tmp2) * max(0, L[i] - 26));
							}
			/*for(int j = nowminj; j <= 26; j++) //for debug
				for(int k = 0; k <= j; k++)
					if(f[i & 1][j][k] < oo)
						printf("f[%d][%d][%d] = %d\n", i, j, k, f[i & 1][j][k]);*/
			prevminj = nowminj;
		}
		int ans = oo;
		for(int j = prevminj; j <= 26; j++)
			ans = min(ans, f[~L.size() & 1][j][0]);
		return ans;
	}
};

