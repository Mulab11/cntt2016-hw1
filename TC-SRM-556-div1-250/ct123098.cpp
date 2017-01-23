#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <ctime>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <typeinfo>

using namespace std;

const int MAXN = 50 + 10;
const int MAXM = 1024 + 10;

class XorTravelingSalesman
{
	public:
	int n, ans;
	int val[MAXN];
	bool e[MAXN][MAXN];
	bool f[MAXN][MAXM];
	
	void dfs(int x, int s)
	{
		if(f[x][s]) return ;
		f[x][s] = true;
		ans = max(ans, s);
		for(int i = 1; i <= n; i++)
			if(e[x][i])
				dfs(i, s ^ val[i]);
	}
	
	int maxProfit(vector<int> cityValues, vector<string> roads)
	{
		ans = 0;
		memset(val, 0, sizeof(val));
		memset(f, 0, sizeof(f));
		memset(e, 0, sizeof(e));
		
		n = cityValues.size();
		for(int i = 1; i <= n; i++)
			val[i] = cityValues[i - 1];
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				e[i][j] = (roads[i - 1][j - 1] == 'Y' ? 1 : 0);
		dfs(1, val[1]);
		return ans;
	}
};

