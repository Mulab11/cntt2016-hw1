#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;

int f[1 << 16][maxn]; //the set of shops that we have made a purchase,our current position

class TravellingPurchasingMan
{
public:
	void update(int &a,int b)
	{
		a = min(a,b);
	}

	void decode(string a,vector<int> &b)
	{
		b.clear();
		bool exi = 0;int x = 0;
		for(auto p : a)
		{
			if (p >= '0' && p <= '9')
				exi = 1,x = x * 10 + p - '0'; else
				{
					if (exi) b.push_back(x);
					exi = 0,x = 0;
				}
		}
		if (exi) b.push_back(x);
	}

	int maxStores(int n, vector<string> interestingStores,vector <string> roads)
	{
		vector<int> info[55];
		static int lk[maxn][maxn];
		memset(lk,60,sizeof lk);
		int m = interestingStores.size();
		for(int i = 0;i < m;i ++)	
			decode(interestingStores[i],info[i]);
		for(int i = 0;i < roads.size();i ++)
		{
			vector<int> cr;
			decode(roads[i],cr);
			lk[cr[1]][cr[0]] = lk[cr[0]][cr[1]] = min(lk[cr[0]][cr[1]],cr[2]);
		}	
		memset(f,60,sizeof f);
		int inf = f[0][0];
		f[0][n - 1] = 0;
		for(int s = 0;s < (1 << m);s ++)
		{
			//no purchase is made,do spfa
			static bool in[maxn];
			static int que[maxn * maxn];
			int *d = f[s],fi = 1,en = 0;
			for(int i = 0;i < n;i ++)
				if (d[i] != inf) que[++ en] = i,in[i] = 1;
			for(;fi <= en;fi ++)
			{
				int u = que[fi];
				for(int i = 0;i < n;i ++)
					if (lk[u][i] != inf && d[u] + lk[u][i] < d[i])
					{
						d[i] = d[u] + lk[u][i];
						if (!in[i]) in[i] = 1,que[++ en] = i;
					}
				in[u] = 0;
			}
			for(int i = 0;i < m;i ++) //to make a purchase
				if (f[s][i] < inf && f[s][i] <= info[i][1])
					update(f[s | (1 << i)][i],max(f[s][i],info[i][0]) + info[i][2]);
		}
		int ans = 0;
		for(int s = 1;s < (1 << m);s ++)
			for(int i = 0;i < n;i ++)
				if (f[s][i] != inf) ans = max(ans,__builtin_popcount(s));
		return ans;
	}
};
