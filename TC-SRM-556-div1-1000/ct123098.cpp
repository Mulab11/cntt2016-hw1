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

const int MAXN = 100;
const int MAXM = 200000 + 1000;
const int INF = 0x1f1f1f1f;

class OldBridges
{
	public:
	struct edge { int next, to, w; } e[MAXM];
	int p[MAXN], head[MAXN], l;
	void init()
	{
		memset(p, 0, sizeof(p));
		l = 2;
	}
	void addE(int a, int b, int c)
	{
		e[l].next = p[a];
		e[l].to = b;
		e[l].w = c;
		p[a] = l++;
	}
	void ins2(int a, int b, int c)
	{
		addE(a, b, c);
		addE(b, a, 0);
	}
	int n;
	int S, T, totp;
	int flow;
	queue<int> q;
	int num[MAXN];
	bool bfs(int a, int b)
	{
		memset(num, -1, sizeof(num));
		q.push(a), num[a] = 1;
		while(!q.empty())
		{
			int x = q.front();
			q.pop();
//			cout << x << endl;
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
				int x = e[i].to, tmp = dfs(x, b, min(s, e[i].w));
				e[i].w -= tmp;
				e[i ^ 1].w += tmp;
				s -= tmp;
				ret += tmp;
				if(s <= 0) break;
			}
		return ret;
	}
	void dinic()
	{
		flow = 0;
		while(bfs(S, T))
		{
			for(int i = 1; i <= totp; i++)
				head[i] = p[i];
			while(dfs(S, T, INF));
		}
	}
	
	string isPossible(vector<string> bridges, int a1, int a2, int an, int b1, int b2, int bn)
	{
		n = bridges.size();
		S = n + 1, T = n + 2, totp = n + 2;
		init();
		for(int i = 1; i <= n; i++)
			for(int j = i + 1; j <= n; j++)
				if(bridges[i - 1][j - 1] == 'O')
					addE(i, j, 2), addE(j, i, 2);
				else if(bridges[i - 1][j - 1] == 'N')
					addE(i, j, INF), addE(j, i, INF);
		ins2(S, a1 + 1, 2 * an);
		ins2(S, b1 + 1, 2 * bn);
		ins2(a2 + 1, T, 2 * an);
		ins2(b2 + 1, T, 2 * bn);
		dinic();
		if(flow != 2 * an + 2 * bn)
			return "No";
		
		init();
		for(int i = 1; i <= n; i++)
			for(int j = i + 1; j <= n; j++)
				if(bridges[i - 1][j - 1] == 'O')
					addE(i, j, 2), addE(j, i, 2);
				else if(bridges[i - 1][j - 1] == 'N')
					addE(i, j, INF), addE(j, i, INF);
		ins2(S, a1 + 1, 2 * an);
		ins2(S, b2 + 1, 2 * bn);
		ins2(a2 + 1, T, 2 * an);
		ins2(b1 + 1, T, 2 * bn);
		dinic();
		if(flow != 2 * an + 2 * bn)
			return "No";
		
		return "Yes";
	}
};

