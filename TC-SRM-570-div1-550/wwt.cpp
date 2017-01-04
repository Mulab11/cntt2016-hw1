#include <bits/stdc++.h>

using namespace std;

const int maxn = 36;

class CentaurCompany
{
public:
	double f[maxn][2][maxn * 2 + 5];//f[root][the status of root][the cost]:ways
	vector<int> lk[105];
	int n;

	void dfs(int now,int pre)
	{
		f[now][1][-1 + maxn] = 1,f[now][0][maxn] = 1; //in order to avoid negative number,we add maxn to the cost
		for(auto p:lk[now])
			if (p != pre)
			{
				dfs(p,now);
				static double bak[2][maxn * 2 + 5];
				memset(bak,0,sizeof bak);
				for(int c = 0;c < 2;c ++)
					for(int co = 0;co <= 2 * maxn;co ++)
						if (f[now][c][co])
							for(int nc = 0;nc < 2;nc ++)
								for(int nco = 0;nco <= 2 * maxn;nco ++)
									if (f[p][nc][nco])
									{
										int new_cost = co + nco - 2 * maxn;
										if (nc && !c) new_cost += 2;//create a new component
										bak[c][new_cost + maxn] += f[now][c][co] * f[p][nc][nco];
									}
				memcpy(f[now],bak,sizeof bak);
			}
	}

	double getvalue(vector <int> a, vector <int> b)
	{
		n = a.size() + 1;
		memset(lk,0,sizeof lk);
		for(int i = 0;i < n - 1;i ++)
			lk[a[i] - 1].push_back(b[i] - 1),lk[b[i] - 1].push_back(a[i] - 1);
		memset(f,0,sizeof f);
		dfs(0,-1);
		double ans = 0;
		for(int sta = 0;sta < 2;sta ++)
			for(int c = 0;c <= maxn * 2;c ++)
			{
				int real_c = c - maxn;
				if (sta) real_c += 2;//we can't forget the component of the root
				real_c -= 2;//the cost equal to 2 * number of components - 2 * number of nodes - 2
				ans += max(0,real_c) * f[0][sta][c];
			}
		return ans / (1ll << n - 1);//expectation
	}
};
