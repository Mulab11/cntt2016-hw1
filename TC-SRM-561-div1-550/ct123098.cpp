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

class CirclesGame
{
	public:
	
	struct edge
	{
		int next, to;	
	}
	e[2 * MAXN];
	int p[MAXN], l;
	void addE(int x, int y)
	{
		e[l].next = p[x];
		e[l].to = y;
		p[x] = l++;
	}
	
	int n, m;
	bool vis[MAXN];
	int fa[MAXN];
	int f[MAXN];
	bool hash[MAXN];
	
	void getF(int x, int father, int top, vector<int> &v)
	{
		int tmp = 0;
		for(int i = p[x]; i; i = e[i].next)
			if(e[i].to != father)
				tmp ^= f[e[i].to];
		v.push_back(top ^ tmp);
		for(int i = p[x]; i; i = e[i].next)
			if(e[i].to != father)
				getF(e[i].to, x, top ^ tmp ^ f[e[i].to], v);
	}
	
	void work(int x, int father)
	{
		for(int i = p[x]; i; i = e[i].next)
			if(e[i].to != father)
				work(e[i].to, x);
		vector<int> v(0);
		getF(x, father, 0, v);
		for(int i = 0; i < v.size(); i++)
			hash[v[i]] = true;
		for(f[x] = 0; hash[f[x]]; f[x]++);
		for(int i = 0; i < v.size(); i++)
			hash[v[i]] = false;
	}
	
	double dist(int x1, int y1, int x2, int y2)
	{
		return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));	
	}
	
	string whoCanWin(vector<int> x, vector<int> y, vector<int> r)
	{
		memset(fa, 0, sizeof(fa));
		memset(f, 0, sizeof(f));
		memset(hash, 0, sizeof(hash));
		memset(p, 0, sizeof(p)), l = 2;
		
		n = x.size();
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				if(i != j)
					if(dist(x[i - 1], y[i - 1], x[j - 1], y[j - 1]) + r[i - 1] < r[j - 1])
						if(fa[i] == 0 || r[j - 1] < r[fa[i] - 1])
							fa[i] = j;
		for(int i = 1; i <= n; i++)
			if(fa[i] != 0)
				addE(i, fa[i]), addE(fa[i], i);
		
		int sta = 0;
		for(int i = 1; i <= n; i++)
			if(fa[i] == 0)
				work(i, 0), sta ^= f[i];
		
		if(sta == 0)
			return "Bob";
		else
			return "Alice";
	}
};

