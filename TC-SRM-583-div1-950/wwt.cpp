#include <bits/stdc++.h>

using namespace std;

const int maxn = 25;

int a[maxn][maxn];

class RandomPaintingOnABoard
{
public:
	double expectedSteps(vector<string> prob)
	{
		int n = prob.size(),m = prob[0].length(),alls = 0;
		//assume that n > m -> m <= 12
		if (n > m)
		{
			for(int i = 0;i < n;i ++)
				for(int j = 0;j < m;j ++) a[i][j] = prob[i][j] - 48,alls += a[i][j];
		} else
		{
			swap(n,m);
			for(int i = 0;i < n;i ++)
				for(int j = 0;j < m;j ++) a[i][j] = prob[j][i] - 48,alls += a[i][j];
		}
		double ans = 0; //ans=\sum_{s} (alls/(alls - (alls - sum(s))))*(-1)^{|s|-1}
		for(int cols = 0;cols < (1 << m);cols ++) //choose columns in set cols
		{
			static double f[maxn][10 * 150]; //\sum_{s,sum(s)=j} (-1)^{|s|-1}
			memset(f,0,sizeof f);
			int outer = 0;
			for(int r = 0;r < n;r ++)
				for(int c = 0;c < m;c ++)
					if (!(cols & (1 << c))) outer += a[r][c];
			f[0][0] = (__builtin_popcount(cols) & 1) ? 1 : -1;
			for(int r = 0,cs = 0;r < n;r ++) //detemine whether to choose rth row
			{
				int extra = 0;//extra sum which needs to be substracted
				for(int j = 0;j < m;j ++)
					if (!(cols & (1 << j))) extra += a[r][j];
				for(int s = 0;s <= cs;s ++)
				{
					f[r + 1][s] += f[r][s];//not change anything
					f[r + 1][s + extra] -= f[r][s];//choose r *= -1
				}
				cs += extra;
			} 
			for(int s = 0;s <= alls;s ++)
				if (outer - s != alls)
					ans += f[n][s] * (alls / double(alls - (outer - s)));
		}
		return ans;
	}
};
