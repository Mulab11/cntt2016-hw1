#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <cassert>
using namespace std;
//try to optimize to O(n) if the input is O(n). Now that the input is O(n^2), the total time complexity is O(n^2).
class Edge
{
public:
	int to, next;
};
const int MAXN = 55;
class TPS
{
private:
	int n;
	int head[MAXN], en;
	int deg[MAXN];
	Edge e[MAXN * 2];//adjacency list
	int f[MAXN * 2];//f[i]: distinguish subtree e[i].to (with father e[i^1].to), ans
	int f2[MAXN];//f2[i]: root i, ans
	int cnt0[MAXN];//number of j: f[edge i->j] = 0
	int searchtime;
	void insert(int u, int v)
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
	int search(int i)//edge #i
	{
		searchtime++;
		if(f[i] != -1)//memorization
			return f[i];
		//printf("%dth search %d (%d->%d) %d\n", searchtime, i, e[i ^ 1].to, e[i].to, f2[0]);
		if(f2[e[i].to] >= 0 && f[i ^ 1] != -1)
			return f[i] = f2[e[i].to] - f[i ^ 1] - (!f[i ^ 1] && cnt0[e[i].to] >= 2);
		int cnt = 0, sum = 0;
		for(int j = head[e[i].to]; j > 0; j = e[j].next)
			if(j ^ i ^ 1)
			{
				int now = search(j);
				sum += now;
				cnt += !now;
			}
		f[i] = sum + cnt - !!cnt;
		//printf("f[%d] = %d\n", i, f[i]);
		if(f2[e[i].to] == -1 && deg[e[i].to] > deg[e[i ^ 1].to])//seems that "deg[e[i].to] > deg[e[i ^ 1].to]" optimizes a lot
		{
			f2[e[i].to] = -2;
			int now = search(i ^ 1);
			sum += now;
			cnt += !now;
			f2[e[i].to] = sum + cnt - !!cnt;
			cnt0[e[i].to] = cnt;
			//printf("f2[%d] = %d\n", e[i].to, f2[e[i].to]);
		}
		return f[i];
	}
	int search2(int p)
	{
		if(f2[p] >= 0)
			return f2[p];
		f2[p] = -2;
		int cnt = 0, sum = 0;
		for(int j = head[p]; j > 0; j = e[j].next)
		{
			if(f[j ^ 1] == -1 && e[j].next == -1)
				f[j ^ 1] = sum + cnt - !!cnt;
			int now = search(j);
			sum += now;
			cnt += !now;
		}
		f2[p] = sum + cnt - !!cnt;
		cnt0[p] = cnt;
		//printf("f2[%d] = %d\n", p, f2[p]);
		return f2[p];
	}	
public:
	int minimalBeacons(vector<string> linked)
	{
		n = linked.size();
		if(n == 1)
			return 0;
		en = 1;
		memset(deg, 0, n * sizeof(int));
		for(int i = 0; i < n; i++)
			for(int j = i + 1; j < n; j++)
				if(linked[i][j] == 'Y')
					insert(i, j);
		memset(f, -1, (en + 1) * sizeof(int));
		memset(f2, -1, n * sizeof(int));
		searchtime = 0;
		int ans = n;
		for(int i = 0; i < n; i++)
			ans = min(ans, search2(i));
		//printf("search time: %d\n", searchtime);
		return ans + 1;
	}
};
/*
//this is a simple O(n^2) code.

class Edge
{
public:
	int to, next;
};
const int MAXN = 55;
class TPS
{
private:
	int n;
	int head[MAXN], en;
	Edge e[MAXN * 2];//adjacency list
	int f[MAXN * 2];//f[i]: distinguish subtree e[i].to (with father e[i^1].to), ans
	int f2[MAXN];//f2[i]: root i, ans
	int cnt0[MAXN];//number of j: f[edge i->j] = 0
	int searchtime;
	void insert(int u, int v)
	{
		e[++en].to = v;
		e[en].next = head[u];
		head[u] = en;
		e[++en].to = u;
		e[en].next = head[v];
		head[v] = en;
	}
	int search(int i)//edge #i
	{
		searchtime++;
		//printf("search %d (%d->%d)\n", i, e[i ^ 1].to, e[i].to);
		if(f[i] != -1)//memorization
			return f[i];
		if(f2[e[i ^ 1].to] != -1 && f[i ^ 1] != -1)
			return f[i] = f2[e[i ^ 1].to] - f[i ^ 1] - (!f[i ^ 1] && cnt0[e[i ^ 1].to] >= 2);
		int cnt = 0, sum = 0;
		for(int j = head[e[i].to]; j > 0; j = e[j].next)
			if(j ^ i ^ 1)
			{
				int now = search(j);
				sum += now;
				cnt += !now;
			}
		f[i] = sum + cnt - !!cnt;
		//printf("f[%d] = %d\n", i, f[i]);
		if(f2[e[i ^ 1].to] == -1)
		{
			int now = search(i ^ 1);
			sum += now;
			cnt += !now;
			f2[e[i ^ 1].to] = sum + cnt - !!cnt;
			cnt0[e[i ^ 1].to] = cnt;
			//printf("f2[%d] = %d\n", f2[e[i ^ 1].to]);
		}
		return f[i];
	}
public:
	int minimalBeacons(vector<string> linked)
	{
		n = linked.size();
		if(n == 1)
			return 0;
		en = 1;
		for(int i = 0; i < n; i++)
			for(int j = i + 1; j < n; j++)
				if(linked[i][j] == 'Y')
					insert(i, j);
		memset(f, -1, (en + 1) * sizeof(int));
		memset(f2, -1, n * sizeof(int));
		searchtime = 0;
		for(int i = 2; i <= en; i++)
			if(f[i] == -1)
				search(i);
		printf("search time: %d\n", searchtime);
		int ans = n;
		for(int i = 0; i < n; i++)
			if(f2[i] < ans)
				ans = f2[i];
		return ans + 1;
	}
};
*/
