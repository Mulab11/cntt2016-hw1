#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <iostream>
using namespace std;
struct Edge
{
	int v;
	Edge *next;
};
int mc, v, dep[51];
bool hvtps[51];
Edge memory[510], *edge[51];
void AddEdge(int u, int v)
{
	Edge *p = &memory[mc++];
	p->v = v, p->next = edge[u];
	edge[u] = p;
}
class TPS
{
public:
	int Dfs(int a)
	{
		int son = 0, son1 = 0, ans = 0;
		for(Edge *p = edge[a]; p; p = p->next)
		{
			int v = p->v;
			if(dep[v])
				continue;
			dep[v] = dep[a] + 1;
			son++;
			ans += Dfs(v);
			if(hvtps[v]) 
				son1++;
		}
		hvtps[a] = false;
		if(son >= 2)
			hvtps[a] = true, ans += max(son - son1 - 1, 0);
		if(son1)
			hvtps[a] = true;
		return ans;
	}
	int minimalBeacons(vector<string> linked)
	{
		int n = linked.size();
		for(int i = 0; i < n; i++) //处理连边 
		{
			for(int j = 0; j < n; j++)
			{
				if(linked[i][j] == 'Y') 
					AddEdge(i, j);
			}
		}
		int ans = n;
		if(n == 1) 
			return 0;
		for(int i = 0; i < n; i++) //考虑根节点并更新答案 
		{
			memset(hvtps, false, sizeof(hvtps));
			memset(dep, 0, sizeof(dep));
			dep[i] = 1;
			int nans = Dfs(i) + 1;
			ans = min(ans, nans);
		} 
		return ans;
	}
};
