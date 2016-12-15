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
const int MOD = 1000000009;
class Edge
{
	public:
		int to, next;
};
long long quickmul(int a, int b)
{
	if(b <= 1)
		return b ? a : 1;
	long long tmp = quickmul(a, b >> 1);
	tmp = tmp * tmp % MOD;
	return b & 1 ? tmp * a % MOD : tmp;
}
class InducedSubgraphs
{
	private:
	Edge e[100];
	int head[50], en, n, k;
	int deg[50];//degree
	int sum0[50], height[50];//subtree size and height when root = point 0
	bool visit[50];//for dfs
	int fac[50], facrev[50];//fac[i] = i! % MOD, facrev[i] = 1/(i!) % MOD
	int f[50][50];//f[i][fa]: subtree i(father fa), number of arrangements
	int sum[50][50];//sum[i][fa]: size of subtree i(father fa)
	int g[50][50][50][50];//g[i][fa][cnt1][cnt2]: subtree i(father fa), cnt1 (<n-k) points, cnt2 (>k) points, number of arrangements
	bool visitg[50][50];//for memorizing g[][]
	int C[50][50];//combination
	//int tmpp[50][50];
	void insert(int u, int v)//add edge
	{
		e[++en].to = v;
		e[en].next = head[u];
		head[u] = en;
		e[++en].to = u;
		e[en].next = head[v];
		head[v] = en;
		deg[u]++;
		deg[v]++;
	}
	void dfs1(int p)
	{
		visit[p] = true;
		sum0[p] = 1;
		for(int i = head[p]; i > 0; i = e[i].next)
			if(!visit[e[i].to])
			{
				height[e[i].to] = height[p] + 1;
				dfs1(e[i].to);
				sum0[p] += sum0[e[i].to];
			}
	}
	int getSubtreeSum(int p, int fa)
	{
		if(height[fa] < height[p])
			return sum0[p];
		else
			return n - sum0[fa];
	}
	void dfs2(int p, int fa)
	{
		int nowsum = 0;
		long long now = 1;
		for(int i = head[p]; i > 0; i = e[i].next)
			if(e[i].to != fa)
			{
				dfs2(e[i].to, p);
				nowsum += sum[e[i].to][p];
				now = now * f[e[i].to][p] % MOD * facrev[sum[e[i].to][p]] % MOD;
			}
		f[p][fa] = now * fac[nowsum] % MOD;
		sum[p][fa] = nowsum + 1;
	}
	void dfs3(int p, int fa)
	{
		if(visitg[p][fa])
			return;
		visitg[p][fa] = true;
		g[p][fa][0][0] = 1;
		int nowsum = 0;
		for(int i = head[p]; i > 0; i = e[i].next)
			if(e[i].to != fa)
			{
				dfs3(e[i].to, p);
				int tmp = 0;
				for(int ii = nowsum; ii >= 0; ii--)
					for(int jj = nowsum - ii; jj >= 0; jj--)
						if(tmp = g[p][fa][ii][jj])
							for(int iii = 0; iii <= sum[e[i].to][p]; iii++)
								for(int jjj = !iii; iii + jjj <= sum[e[i].to][p]; jjj++)
									g[p][fa][ii + iii][jj + jjj] = (g[p][fa][ii + iii][jj + jjj] + (long long)g[e[i].to][p][iii][jjj] * tmp % MOD * C[ii + iii][iii] % MOD * C[jj + jjj][jjj]) % MOD;
				/*for(int ii = 0; ii <= nowsum; ii++)
					for(int jj = 0; ii + jj <= nowsum; jj++)
						tmpp[ii][jj] = g[p][fa][ii][jj];
				for(int ii = 0; ii <= nowsum; ii++)
					for(int jj = 0; ii + jj <= nowsum; jj++)
						g[p][fa][ii][jj] = 0;
				for(int ii = 0; ii <= nowsum; ii++)
					for(int jj = 0; ii + jj <= nowsum; jj++)
						if(tmp = tmpp[ii][jj])
							for(int iii = 0; iii <= sum[e[i].to][p]; iii++)
								for(int jjj = 0; iii + jjj <= sum[e[i].to][p]; jjj++)
									g[p][fa][ii + iii][jj + jjj] = (g[p][fa][ii + iii][jj + jjj] + (long long)g[e[i].to][p][iii][jjj] * tmp % MOD * C[ii + iii][iii] % MOD * C[jj + jjj][jjj]) % MOD;*/
				nowsum = min(nowsum + sum[e[i].to][p], 2 * (n - k));
			}
		g[p][fa][sum[p][fa]][0] = g[p][fa][0][sum[p][fa]] = f[p][fa];
		//printf("g[%d][%d][%d][%d] = %d\n", p, fa, n - k, n - k, g[p][fa][n - k][n - k]);
	}
	int solve1()//2k <= n
	{
		int ans = 0;
		memset(visit, false, sizeof(visit));
		height[0] = 0;
		dfs1(0);
		for(int i = 0; i < n; i++)
			for(int j = head[i]; j > 0; j = e[j].next)
				if(getSubtreeSum(i, e[j].to) == k)
				{
					bool flag = true;
					int now = e[j].to, prev = i;
					for(int ii = 1; ii <= n - 2 * k; ii++)//go through the (n-2k+2)-point chain
					{
						if(deg[now] != 2)
						{
							flag = false;
							break;
						}
						for(int jj = head[now]; jj > 0; jj = e[jj].next)
							if(e[jj].to != prev)
							{
								prev = now;
								now = e[jj].to;
								break;
							}
					}
					if(!flag)
						continue;
					if(getSubtreeSum(now, prev) != k)
						continue;
					/*
					o                          o
					 \                        /
					  i-e[j].to-o-o-o-prev-now
					 /                        \
					o                          o
					*/
					ans = (ans + (long long)f[i][e[j].to] * f[now][prev]) % MOD;
				}
		return ans;
	}
	int solve2()//2k > n
	{
		for(int i = 0; i <= n; i++)
		{
			C[i][0] = C[i][i] = 1;
			for(int j = 1; j < n; j++)
				C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
		}
		memset(visitg, false, sizeof(visitg));
		memset(g, 0, sizeof(g));
		int ans = 0;
		for(int i = 0; i < n; i++)
		{
			dfs3(i, n);
			ans = (ans + g[i][n][n - k][n - k]) % MOD;
			//printf("%d %d\n", i, g[i][n][n - k][n - k]);
		}
		ans = (long long)ans * fac[2 * k - n - 1] % MOD;
		return ans;
	}
	public:
	int getCount(vector<int> edge1, vector<int> edge2, int k)
	{
		memset(head, -1, sizeof(head));
		en = 1;
		n = edge1.size() + 1;
		this->k = k;
		memset(deg, 0, sizeof(deg));
		for(int i = 0; i < n - 1; i++)//build tree
			insert(edge1[i], edge2[i]);
		fac[0] = facrev[0] = 1;
		for(int i = 1; i <= n; i++)
		{
			fac[i] = (long long)fac[i - 1] * i % MOD;
			facrev[i] = quickmul(fac[i], MOD - 2);
		}
		for(int i = 0; i < n; i++)
			dfs2(i, n);
		if(k == 1 || k == n)//the condition will be satisfied however we renumber the vertices.
			return fac[n];
		else if(2 * k <= n)
			return solve1();
		else
			return solve2();
	}
};

