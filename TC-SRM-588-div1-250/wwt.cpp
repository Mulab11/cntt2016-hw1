#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;

int f[maxn][maxn]; //f[i][j],最后唱的是第i首歌，总共唱了j首，最短时间

class GUMIAndSongsDiv1
{
public:
	int maxSongs(vector<int> d,vector<int> t, int T)
	{
		int n = d.size();
		for(int i = 0;i < n;i ++)
			for(int j = i + 1;j < n;j ++)
				if (t[i] > t[j]) swap(d[i],d[j]),swap(t[i],t[j]); //显然假如确定了要唱哪些歌，要按t有序来唱，这样时间才短
		memset(f,60,sizeof f);
		for(int i = 0;i < n;i ++) f[i][1] = d[i];
		for(int i = 0;i < n;i ++)
			for(int k = 1;k <= n;k ++)
				for(int j = 0;j < i;j ++)
					f[i][k] = min(f[i][k],f[j][k - 1] + t[i] - t[j] + d[i]);
		int ans = 0;
		for(int i = 0;i < n;i ++)
			for(int k = 1;k <= n;k ++)
				if (f[i][k] <= T) ans = max(ans,k);
		return ans;
	}
};
