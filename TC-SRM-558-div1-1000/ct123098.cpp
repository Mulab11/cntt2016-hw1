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

const int MAXN = 10000 + 100;
const int MAXM = 2 * 100000 + 100;
const int INF = 0x1f1f1f1f;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};


class SurroundingGame
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
	int S, T, totp;
	int flow;
	queue<int> q;
	int num[MAXN];
	bool bfs(int a, int b)
	{
		memset(num, -1, sizeof(num));
		num[a] = 1;
		q.push(a);
		while(!q.empty())
		{
		    int x = q.front();
		    q.pop();
		    for(int i = p[x]; i; i = e[i].next)
		        if(e[i].w > 0 && num[e[i].to] == -1)
		            num[e[i].to] = num[x] + 1, q.push(e[i].to);
		}
		return num[b] > -1;
	}
	int dfs(int a, int b, int s)
	{
		if(a == b)
		{
		    flow += s; return s;
		}
		int ret = 0;
		for(int &i = head[a]; i; i = e[i].next)
		    if(e[i].w > 0 && num[e[i].to] == num[a] + 1)
		    {
		        int t = dfs(e[i].to, b, min(s, e[i].w));
		        e[i].w -= t;
		        e[i ^ 1].w += t;
		        ret += t;
		        s -=  t;
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
	int n, m;
	int a[50][50], c[50][50];

	int getId(int x, int y)
	{
		return (x - 1) * m + (y - 1) + 1;
	}

	int getNumber(char x)
	{
		if('0' <= x && x <= '9')
			return x - '0';
		if('a' <= x && x <= 'z')
			return x - 'a' + 10;
		if('A' <= x && x <= 'Z')
			return x - 'A' + 36;
		return 0;
	}

	int maxScore(vector<string> cost, vector<string> benefit)
	{
		init();
		
		n = cost.size();
		m = cost[0].size();
		
		for(int i = 1; i <= n; i++)
		    for(int j = 1; j <= m; j++)
		        c[i][j] = getNumber(cost[i - 1][j - 1]);
		for(int i = 1; i <= n; i++)
		    for(int j = 1; j <= m; j++)
		        a[i][j] = getNumber(benefit[i - 1][j - 1]);
		S = 1;
		totp = T = 1 + 2 * n * m + 1;
		for(int i = 1; i <= n; i++)
		    for(int j = 1; j <= m; j++)
		    {
		        bool flag = (i + j) & 1;
		        int id = getId(i, j);
		        if(flag)
		            ins2(S, 1 + id, c[i][j]), ins2(1 + id, 1 + n * m + id, a[i][j]);
		        else
		            ins2(1 + id, T, c[i][j]), ins2(1 + n * m + id, 1 + id, a[i][j]);
		        for(int k = 0; k < 4; k++)
		        {
		            int x = i + dx[k], y = j + dy[k];
		            if(x < 1 || x > n || y < 1 || y > m) continue;
		            if(flag)
		                ins2(1 + n * m + id, 1 + getId(x, y), INF);
		            else
		                ins2(1 + getId(x, y), 1 + n * m + id, INF);
		        }
		    }
		int ans = 0;
		for(int i = 1; i <= n; i++)
		    for(int j = 1; j <= m; j++)
		        ans += a[i][j];
		dinic();
		return ans - flow;
	}
};

