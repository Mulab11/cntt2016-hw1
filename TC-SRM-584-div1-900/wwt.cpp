#include <bits/stdc++.h>

using namespace std;

const int maxn = 150;

vector< pair<int,int> > lk[maxn];

class FoxTheLinguist
{
public:
	bool update(int &a,int b)
	{
		if (b < a) {a = b;return 1;}
		return 0;
	}

	void push_edge(int u,int v,int c)
	{
		lk[u].push_back(make_pair(v,c));
	}

	void decode(vector<string> b)
	{
		string a = "";
		for(auto p : b) a = a + p;
		for(int i = 0;i < a.length();i += 12)
		{
			int u = (a[i] - 'A') * 10 + a[i + 1] - '0';
			int v = (a[i + 4] - 'A') * 10 + a[i + 5] - '0';
			int c = (a[i + 7] - '0') * 1000 + (a[i + 8] - '0') * 100 + 
				  (a[i + 9] - '0') * 10 + (a[i + 10] - '0');
			push_edge(v,u,c); //reverse
		}
	}

	int minimalHours(int n,vector<string> courseInfo)
	{
		//notice,the graph has been reversed.
		for(int i = 0;i < n;i ++) push_edge(i * 10,n * 10,0);//make an artificial point
		for(int i = 0;i < n;i ++)
			for(int j = 9;j;j --) push_edge(i * 10 + j - 1,i * 10 + j,0); //no cost from (i,j)->(i,j-1)
		decode(courseInfo);
		static int f[1 << 10][maxn];
		memset(f,60,sizeof f);
		int inf = f[0][0];
		for(int i = 0;i < n;i ++) f[(1 << i)][i * 10 + 9] = 0;
		for(int mask = 0;mask < (1 << n);mask ++)
		{
			for(int smask = mask;smask;smask = (mask & (smask - 1)))
				for(int i = 0;i <= n * 10;i ++)
					update(f[mask][i],f[smask][i] + f[mask ^ smask][i]);
			static int que[maxn * maxn];
			static bool in[maxn];
			memset(in,0,sizeof in);
			int *d = f[mask],en = 0,fi = 1;
			for(int i = 0;i <= n * 10;i ++)
				if (d[i] != inf) in[i] = 1,que[++ en] = i;
			for(;fi <= en;fi ++)
			{
				int u = que[fi];
				for(auto p : lk[u])
					if (update(d[p.first],d[u] + p.second))
						if (!in[p.first]) in[p.first] = 1,que[++ en] = p.first;
				in[u] = 0;
			}
		}
		int ans = f[(1 << n) - 1][n * 10]; //we must make the artificial point be the root
		return ans == inf ? -1 : ans;
	}
};
