#include <algorithm>
using namespace std;
class KeyDungeonDiv1
{
public:
	int n, f[1 << 12][131];
	int maxKeys(vector<int> cr, vector<int> cg, vector<int> gr, vector<int> gg, vector<int> gw, vector<int> keys)
	{
		n = cr.size();
		for(int i = 0; i < 1 << n; i++)
		{
			for(int j = 0; j <= 130; j++)
				f[i][j] = -1;
		}
		f[0][keys[0]] = keys[2];
		int ans = 0;
		for(int i = 0; i < 1 << n; i++)
		{
			for(int j = 0; j <= 130; j++) //开过的门的集合为i，当前有j个红色钥匙时的最大白色钥匙数 
			{
				if(f[i][j] < 0)
					continue;
				int sum = keys[0] + keys[1] + keys[2];
				for(int k = 0; k < n; k++)
				{
					if(i >> k & 1)
						sum += gr[k] + gg[k] + gw[k] - cr[k] - cg[k];
				}
				ans = max(ans, sum); //钥匙总数是确定的 
				for(int k = 0; k < n; k++)
				{
					int r = j, w = f[i][j], g = sum - r - w;
					if(!(i >> k & 1) && r + w >= cr[k] && g + w >= cg[k] && r + g + w >= cr[k] + cg[k]) //可以开第k扇门 
					{
						w -= max(cr[k] - r, 0) + max(cg[k] - g, 0);
						r -= min(r, cr[k]);
						g -= min(g, cg[k]);
						r += gr[k], g += gg[k], w += gw[k];
						f[i | 1 << k][r] = max(f[i | 1 << k][r], w); //更新状态 
					}
				}
			}
		}
		return ans;
	}
};