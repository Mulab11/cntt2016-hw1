#include <bits/stdc++.h>

using namespace std;

const int xy[4][2] = {{-1,1},{-1,-1},{1,-1},{1,1}};

class HyperKnight
{
public:
	long long f[1 << 8],g[1 << 8];

	long long countCells(int a, int b, int numRows, int numColumns, int k)
	{
		memset(f,0,sizeof f),memset(g,0,sizeof g);
		//g[s]表示至少s集合这些方向能走的点数，f[s]表示只有s这些方向能走的。
		for(int i = 0;i < (1 << 8);i ++)
		{
			int mix = 0,miy = 0,mxx = numRows,mxy = numColumns;
			//找到可行的x和y的范围
			for(int j = 0;j < 4;j ++)
				if (i & (1 << j))
				{
					if (xy[j][0] == -1) mix = max(mix,a); else mxx = min(mxx,numRows - a);
					if (xy[j][1] == -1) miy = max(miy,b); else mxy = min(mxy,numColumns - b);
				}
			for(int j = 0;j < 4;j ++)
				if (i & (1 << (j + 4)))
				{
					if (xy[j][0] == -1) mix = max(mix,b); else mxx = min(mxx,numRows - b);
					if (xy[j][1] == -1) miy = max(miy,a); else mxy = min(mxy,numColumns - a);
				}
			//可行范围必然为一个矩形
			if (mxx > mix && mxy > miy)
				g[i] = (mxx - mix) * 1ll * (mxy - miy);
		}
		//容斥
		for(int i = 0;i < (1 << 8);i ++)
			for(int j = i;j < (1 << 8);j ++) //容斥
				if ((i & j) == i)
				{
					int sig = __builtin_popcount(j) - __builtin_popcount(i);
					if (sig & 1) f[i] -= g[j]; else f[i] += g[j];
				}
		long long ans = 0;
		for(int i = 0;i < (1 << 8);i ++)
			if (__builtin_popcount(i) == k) ans += f[i]; //合法数
		return ans;
	}
};
