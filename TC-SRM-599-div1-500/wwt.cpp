#include <bits/stdc++.h>

using namespace std;

const int maxn = 2505; //最长边不超过l/2

int Sqrt[maxn * maxn];

class FindPolygons
{
public:
	double minimumPolygon(int L)
	{
		//假如L是奇数永远不合法
		if ((L & 1) || L < 4) return -1;
		//L为偶数时，最多4条边就合法了a=1,b=(L-2)/2,L%4=0,4条边相同，L%4=2,a=(L-2)/4,b=(L+2)/4,ans=1
		//只需要判能不能是个三角形
		for(int i = 0;i < maxn * maxn;i ++) Sqrt[i] = -1;
		for(int i = 0;i < maxn;i ++) Sqrt[i * i] = i;
		static int vx[100005],vy[100005];
		int tot = 0;
		for(int c = 0;c < maxn;c ++) 
			for(int a = 0;a <= c;a ++)
				if (Sqrt[c * c - a * a] > -1)
					vx[++ tot] = a,vy[tot] = Sqrt[c * c - a * a]; //(a,b),a^2+b^2=c^2,a>=0,b>=0
		bool get = 0;
		int ans = (1 << 30);
		for(int i = 1;i <= tot;i ++)
			for(int j = i;j <= tot;j ++) //Brute force!!
			{
				if (vx[i] * vy[j] - vx[j] * vy[i] == 0) continue;
				int ax = vx[i] - vx[j],ay = vy[i] - vy[j],v = ax * ax + ay * ay;
				if (v < maxn * maxn && Sqrt[v] > -1)
				{
					int la = Sqrt[vx[i] * vx[i] + vy[i] * vy[i]],lb = Sqrt[vx[j] * vx[j] + vy[j] * vy[j]];
					int lc = Sqrt[v];
					if (la + lb + lc != L) continue;
					get = 1;
					ans = min(ans,max({la,lb,lc}) - min({la,lb,lc}));
				}
			}
		if (!get)
		{
			if (L % 4 == 0) return 0;
			return 1;
		}
		return ans;
	}
};
