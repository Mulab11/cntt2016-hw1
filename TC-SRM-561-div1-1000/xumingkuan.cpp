#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <cctype>
#include <queue>
#include <map>
using namespace std;
class Edge
{
	public:
		int to, next;
}e[20202];
int head[5050], en;
void insert(int u, int v)
{
	e[++en].to = v;
	e[en].next = head[u];
	head[u] = en;
	e[++en].to = u;
	e[en].next = head[v];
	head[v] = en;
}
class Orienteering
{
	private:
	int k;
	int n;//number of points
	int ncheck;//number of checkpoints
	bool type[2525];//type[i] = if point #i is a checkpoint
	int number[55][55];//field[i][j] is point #number[i][j]
	int check[305];//point #check[i] is a checkpoint
	bool visit[2525];
	int sum[2525], dist[2525];
	int dis[305][305];//distance of checkpoints
	double Ck[305], Ck2[305];//Ck[i] = C(i, k), Ck2[i] = C(i, k - 2);
	double ans;
	void dfs(int p)
	{
		visit[p] = true;
		sum[p] = type[p];
		for(int i = head[p]; i > 0; i = e[i].next)
			if(!visit[e[i].to])
			{
				dfs(e[i].to);
				sum[p] += sum[e[i].to];
			}
		if(p != 1)
			ans += Ck[sum[p]] + Ck[ncheck - sum[p]];
	}
	void dfs2(int p)
	{
		visit[p] = true;
		for(int i = head[p]; i > 0; i = e[i].next)
			if(!visit[e[i].to])
			{
				dist[e[i].to] = dist[p] + 1;
				dfs2(e[i].to);
			}
	}
	public:
	double expectedLength(vector<string> field, int K)
	{
		n = ncheck = 0;
		ans = 0.0;
		k = K;
		memset(head, -1, sizeof(head));
		en = 1;
		memset(type, false, sizeof(type));
		for(int i = 0; i < field.size(); i++)
			for(int j = 0; j < field[i].size(); j++)
				if(field[i][j] != '#')
				{
					number[i][j] = ++n;
					if(i && field[i - 1][j] != '#')
						insert(n, number[i - 1][j]);
					if(j && field[i][j - 1] != '#')
						insert(n, number[i][j - 1]);
					if(field[i][j] == '*')
						type[n] = true, check[++ncheck] = n;
				}
		for(int i = 0; i < k; i++)
			Ck[i] = 0;
		for(int i = k; i <= ncheck; i++)
		{
			Ck[i] = 1;
			for(int j = 1; j <= k; j++)
				Ck[i] = Ck[i] * (i - j + 1) / j;
		}
		for(int i = 0; i < k - 2; i++)
			Ck2[i] = 0;
		for(int i = k - 2; i <= ncheck; i++)
		{
			Ck2[i] = 1;
			for(int j = 1; j <= k - 2; j++)
				Ck2[i] = Ck2[i] * (i - j + 1) / j;
		}
		memset(visit, false, sizeof(visit));
		dfs(1);
		ans = (en - 1) - ans / Ck[ncheck] * 2;//(en - 1) / 2 bidirectional edges
		for(int i = 1; i <= ncheck; i++)
		{
			dist[check[i]] = 0;
			memset(visit, false, sizeof(visit));
			dfs2(check[i]);
			for(int j = 1; j <= ncheck; j++)
				dis[i][j] = dist[check[j]];
		}
		for(int i = 1; i <= ncheck; i++)
			for(int j = i + 1; j <= ncheck; j++)//let (check[i], check[j]) be the farthest pair
			{
				int cnt = 0;
				for(int k = 1; k <= ncheck; k++)
					if(k != i && k != j && ((dis[i][k] > dis[i][j] || (dis[i][k] == dis[i][j] && k < j))
						 || (dis[j][k] > dis[i][j] || (dis[j][k] == dis[i][j] && k < i))))
						cnt++;//count point check[k] which will cause (check[i], check[j]) not to be the farthest
				ans -= dis[i][j] * Ck2[ncheck - cnt - 2] / Ck[ncheck];
			}
		return ans;
	}
};

