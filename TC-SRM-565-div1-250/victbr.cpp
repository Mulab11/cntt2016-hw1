#include <bits/stdc++.h>

using namespace std;
const int N = 60;

class MonstersValley{
	public:
		long long f[N][N<<1];
		int n;
		int minimumPrice(vector<long long> dread, vector <int> price){
			n = dread.size();
			memset(f,0xaf,sizeof(f));
			f[0][0] = 0;
			for (int i = 1;i <= n;i++){
				for (int j = 0;j <= 100-price[i-1];j++)
					f[i][j+price[i-1]] = max(f[i][j+price[i-1]],f[i-1][j]+dread[i-1]);
				for (int j = 0;j <= 100;j++)
					if (f[i-1][j] >= dread[i-1])
						f[i][j] = max(f[i][j],f[i-1][j]);					
			}
			for (int i = 0;i <= 100;i++)
				if (f[i][j] > 0) return i;
			return -1;
		}
};
