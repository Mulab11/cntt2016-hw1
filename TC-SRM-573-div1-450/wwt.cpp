#include <bits/stdc++.h>

using namespace std;

const int maxn = 2505;

typedef pair<int,int> pi;

class SkiResorts
{
public:
	int ord[55][55],cnt;
	vector<pi> lk[maxn];

	void link(int u,int v,int l)
	{
		lk[u].push_back(pi(v,l));
	}

	long long dijkstra(int s,int t)
	{
		static bool out[maxn];
		static long long d[maxn];
		for(int i = s;i <= t;i ++) out[i] = 0;
		for(int i = s;i <= t;i ++) d[i] = (1ll << 60);
		d[s] = 0;
		for(;;) //since |E| is very large while |V| is very small,it will be better to use simplest dijkstra
		{
			int u = -1;
			for(int i = s;i <= t;i ++)
				if (!out[i] && (u == -1 || d[i] < d[u])) u = i;
			if (u == -1) break;
			out[u] = 1;
			for(auto p:lk[u])
				if (d[u] + p.second < d[p.first]) d[p.first] = d[u] + p.second;
		}
		if (d[t] == (1ll << 60)) return -1;
		return d[t];
	}

	long long minCost(vector<string> r, vector <int> a)
	{
		vector<int> b;
		b = a;
		sort(b.begin(),b.end());
		b.resize(unique(b.begin(),b.end()) - b.begin());
		memset(lk,0,sizeof lk);
		cnt = 0;
		int n = r.size();
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < b.size();j ++) ord[i][j] = ++ cnt; //change one point into (i,height) 
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < n;j ++)
				if (i != j && r[i][j] == 'Y')
					for(int h1 = 0;h1 < b.size();h1 ++)
						for(int h2 = 0;h2 <= h1;h2 ++)
							link(ord[i][h1],ord[j][h2],abs(b[h2] - a[j])); //we add up the cost for j when we enter (j,h_j)
		int s = 0,t = ++ cnt;
		for(int i = 0;i < b.size();i ++) link(s,ord[0][i],abs(b[i] - a[0]));
		for(int i = 0;i < b.size();i ++) link(ord[n - 1][i],t,0);
		return dijkstra(s,t);
	}
};
