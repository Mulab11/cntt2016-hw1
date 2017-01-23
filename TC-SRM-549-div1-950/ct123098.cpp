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

const int MAXN = 20;
const int MAXM = 2 * 100;
const int MAXK = 1 << 6;
const int INF = 0x1f1f1f1f;

class CosmicBlocks
{
	public:
	
	struct edge
	{
		int next, to, w;
	}
	e[MAXM];
	int p[MAXN], head[MAXN], l;
	
	void init()
	{
		memset(p, 0, sizeof(p));
		l = 2;
	}
	
	void addE(int x, int y, int w)
	{
		e[l].next = p[x];
		e[l].to = y;
		e[l].w = w;
		p[x] = l++;
	}
	
	void ins2(int x, int y, int w)
	{
		addE(x, y, w);
		addE(y, x, 0);
	}
	
	int num[MAXN], flow;
	bool bfs(int a, int b)
	{
		queue<int> q;
		memset(num, -1, sizeof(num));
		num[a] = 1, q.push(a);
		while(!q.empty())
		{
			int x = q.front();
			q.pop();
			for(int i = p[x]; i; i = e[i].next)
				if(e[i].w > 0 && num[e[i].to] == -1)
					num[e[i].to] = num[x] + 1, q.push(e[i].to);
		}
		return num[b] > 0;
	}
	int dfs(int a, int b, int s)
	{
		if(a == b)
		{
			flow += s;
			return s;
		}
		int ret = 0;
		for(int &i = head[a]; i; i = e[i].next)
			if(e[i].w > 0 && num[e[i].to] == num[a] + 1)
			{
				int t = dfs(e[i].to, b, min(s, e[i].w));
				e[i].w -= t;
				e[i ^ 1].w += t;
				ret += t;
				s -= t;
				if(s <= 0) break;
			}
		return ret;
	}
	void dinic(int S, int T, int totp)
	{
		flow = 0;
		while(bfs(S, T))
		{
			for(int i = 1; i <= totp; i++)
				head[i] = p[i];
			while(dfs(S, T, INF));
		}
	}
	
	int ans;
	int n, hei[MAXN], block[MAXN];
	int minW, maxW;
	vector<pair<int, int> > U;
	vector<int> con[MAXN];
	vector<pair<int, int> > cho;
	
	void workE()
	{
		
		int deg[MAXN];
		init();
		memset(deg, 0, sizeof(deg));
		int totp = 2 * n + 2, S = 2 * n + 1, T = 2 * n + 2;
		for(int i = 0; i < n; i++)
			deg[2 * i + 1] -= block[i], deg[2 * i + 2] += block[i];
//		cout << U.size() << ' ' << cho.size() << ' ' << (cho.size() > 0 ? cho[0].first : -1) << endl;
		for(int i = 0; i < cho.size(); i++)
			ins2(2 * cho[i].first + 2, 2 * cho[i].second + 1, INF - 1), deg[2 * cho[i].first + 2] -= 1, deg[2 * cho[i].second + 1] += 1;
		for(int i = 0; i < con[0].size(); i++)
			ins2(S, 2 * con[0][i] + 1, INF);
		for(int i = 0; i < n; i++)
			ins2(2 * i + 2, T, INF);
		ins2(T, S, INF);
		int SS = ++totp, TT = ++totp, lim = 0;
		for(int i = 1; i <= totp; i++)
			if(deg[i] < 0)
				ins2(i, TT, -deg[i]);
			else if(deg[i] > 0)
				ins2(SS, i, deg[i]), lim += deg[i];
		dinic(SS, TT, totp);
		if(flow != lim)
			return ;

//		for(int i = 0; i < n; i++)
//			cout << hei[i] << ' ';
//		cout << endl;
//		for(int i = 0; i < cho.size(); i++)
//			cout << cho[i].first << ' ' << cho[i].second << "  ";
//		cout << endl;
//		cout << flow << ' ' << lim << endl;
		
		static int f[MAXK];
		int maxx = 1 << n;
		f[0] = 1;
		for(int i = 1; i < maxx; i++)
		{
			f[i] = 0;
			int sta = maxx - 1;
			for(int j = 0; j < cho.size(); j++)
				if((i & (1 << cho[j].first)) && (i & (1 << cho[j].second)))
					if(sta & (1 << cho[j].first))
						sta ^= (1 << cho[j].first);
			for(int j = 0; j < n; j++)
				if((i & (1 << j)) && (sta & (1 << j)))
					f[i] += f[i ^ (1 << j)];
		}
		if(minW <= f[maxx - 1] && f[maxx - 1] <= maxW)
			ans++;
//		cout << " ---- " << endl;
	}
	
	void searchE(int x)
	{
		if(x == U.size())
		{
			workE();
			return ;
		}
		cho.push_back(U[x]);
		searchE(x + 1);
		cho.pop_back();
		searchE(x + 1);
	}
	
	void workH()
	{
		U.clear();
		static int sum[MAXN];
		for(int i = 0; i < n; i++) sum[i] = 0;
		for(int i = 0; i < n; i++) sum[hei[i]] += block[i];
		for(int i = 1; i < n; i++)
			if(sum[i - 1] < sum[i])
				return ;
			
		for(int i = 1; i < n; i++)
			for(int x = 0; x < con[i].size(); x++)
				for(int y = 0; y < con[i - 1].size(); y++)
					U.push_back(make_pair(con[i - 1][y], con[i][x]));
		searchE(0);
	}
	
	void searchH(int x)
	{
		if(x == n)
		{
			workH();
			return ;
		}
		for(int i = 0; i < n; i++)
		{
			hei[x] = i, con[i].push_back(x);
			searchH(x + 1);
			hei[x] = 0, con[i].pop_back();
		}
	}
	
	int getNumOrders(vector<int> blockTypes, int minWays, int maxWays)
	{
		ans = 0;
		
		n = blockTypes.size();
		for(int i = 0; i < n; i++)
			block[i] = blockTypes[i];
		minW = minWays, maxW = maxWays;
		
		memset(hei, 0, sizeof(hei));
		
		searchH(0);
			
		return ans;
	}
};

