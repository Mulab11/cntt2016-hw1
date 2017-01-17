#include <bits/stdc++.h>

using namespace std;

class TheDevice{
	public:
		int f[60],g[60],ans;
		int minimumAdditional(vector <string> plates){
			int n = plates.size();
			int m = plates[0].size();
			for (int i = 0;i < n;i++)
				for (int j = 0;j < m;j++) 
					if (plates[i][j] == '0') f[j]++;else g[j]++;
			for (int i = 0;i < m;i++)
				ans = max(ans,max(0,2-g[i])+max(0,1-f[i]));
			return ans;
		}
};
