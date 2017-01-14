#include <bits/stdc++.h>

using namespace std;

const int maxn = 12,maxm = 135;

bitset<maxm> f[1 << maxn][maxm]; //达到状态f(s,r,g)表示手上有r个red,g个green是否可行，要用bitset压空间
int cr[1 << maxn],cg[1 << maxn]; //从集合s中要消耗cr[s]个red,cg[s]个green
int rc[1 << maxn],gc[1 << maxn],wc[1 << maxn]; //从集合s中分别得到rc[s]个red,gc[s]个green,wc[s]个white

class KeyDungeonDiv1
{
public:
	int maxKeys(vector <int> doorR, vector <int> doorG, vector <int> roomR, vector <int> roomG, vector <int> roomW, vector <int> keys)
	{
		int n = doorR.size();
		for(int s = 0;s < (1 << n);s ++)
		{
			rc[s] = keys[0],gc[s] = keys[1],wc[s] = keys[2];
			for(int i = 0;i < n;i ++)
				if (s & (1 << i))
				{
					rc[s] += roomR[i],gc[s] += roomG[i],wc[s] += roomW[i];
					cr[s] += doorR[i],cg[s] += doorG[i];
				}
		}
		f[0][keys[0]][keys[1]] = 1;
		for(int s = 0;s < (1 << n) - 1;s ++)
			for(int r = 0;r <= 130;r ++)
				for(int g = 0;g <= 130;g ++)
					if (f[s][r][g])
					{
						int w = rc[s] + gc[s] + wc[s] - r - g - cr[s] - cg[s]; //得到-失去=拥有
						for(int i = 0;i < n;i ++)
							if (!(s & (1 << i)))
							{
								int use_r = min(r,doorR[i]),use_g = min(g,doorG[i]); //优先用red和green
								if (w >= doorR[i] + doorG[i] - use_r - use_g) //不够时用white补
									f[s | (1 << i)][r - use_r + roomR[i]][g - use_g + roomG[i]] = 1;
							}
					}
		int ans = 0;
		for(int s = 0;s < (1 << n);s ++)
			for(int r = 0;r <= 130;r ++)
				for(int g = 0;g <= 130;g ++)
					if (f[s][r][g]) ans = max(ans,rc[s] + gc[s] + wc[s] - cr[s] - cg[s]);
		return ans;
	}
};
