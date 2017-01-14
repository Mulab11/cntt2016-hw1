#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;

int f[maxn][maxn * 2];

class TurnOnLamps
{
public:
	int minimize(vector <int> roads, string initState, string isImportant)
	{
		int n = roads.size() + 1;
		memset(f,60,sizeof f);
		int inf = f[0][0];
		//regard an outer point with value 1,inner point with value -1,f[i][j] means the minimum cost for subtree i with sum of value equal to j-n
		//we only consider the cost when a point is with value 1
		for(int i = 0;i < n;i ++) f[i][n - 1] = f[i][n] = 0,f[i][n + 1] = 1;
		for(int i = n - 1;i;i --)
		{
			int fa = roads[i - 1];
			static int bak[maxn * 2];
			memcpy(bak,f[fa],sizeof bak);
			memset(f[fa],60,sizeof f[fa]);
			for(int j = 0;j <= 2 * n;j ++)
				if (isImportant[i - 1] == '0' || ((initState[i - 1] == '1') ^ (abs(j - n) & 1))) //be legal to edge i - 1
					if (f[i][j] != inf)
					for(int k = 0;k <= 2 * n;k ++)
						if (bak[k] != inf)
						f[fa][j + k - n] = min(f[fa][j + k - n],f[i][j] + bak[k]); //merge with father's information
		}
		return f[0][n];
	}	
};
