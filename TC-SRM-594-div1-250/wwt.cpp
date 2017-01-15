#include <bits/stdc++.h>

using namespace std;

class AstronomicalRecords
{
public:
	int f[55][55];

	int minimalPlanets(vector<int> A,vector<int> B)
	{
		int ans = (1 << 30),n = A.size(),m = B.size();
		for(int i = 0;i < A.size();i ++)
			for(int j = 0;j < B.size();j ++) //let A[i] and B[j] refer to the same planet
			{	
				memset(f,0,sizeof f);
				for(int x = 0;x <= n;x ++)
					for(int y = 0;y <= m;y ++)
					{
						if (x < n && y < m && A[x] * 1ll * B[j] == A[i] * 1ll * B[y]) //A[x]/A[i]=B[j]/B[y]
							f[x + 1][y + 1] = max(f[x][y] + 1,f[x + 1][y + 1]);
						if (x < n) f[x + 1][y] = max(f[x + 1][y],f[x][y]);
						if (y < m) f[x][y + 1] = max(f[x][y + 1],f[x][y]);
					}
				ans = min(ans,n + m - f[n][m]); //find the longest common subsequence,which we can reduce the number of planets
			}
		return ans;
	}
};
