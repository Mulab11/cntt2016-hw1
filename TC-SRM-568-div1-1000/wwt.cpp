#include <bits/stdc++.h>

using namespace std;

class DisjointSemicircles
{
public:
	int n,cnt[100],col[55],N;
	int graph[55][55];
	int a[55];

	bool dfs_col(int now,int c)
	{
		col[now] = c;
		for(int i = 0;i < N;i ++)
			if (graph[now][i] != -1)
			{
				if (col[i] == -1)
				{
					if (!dfs_col(i,c ^ graph[now][i])) return 0;
				} else
					if (col[i] != (c ^ graph[now][i])) return 0;
			}
		return 1;
	}

	int co;

	bool test_1()
	{
		++ co;
		N = n / 2;
		static int l[55],r[55];
		memset(l,255,sizeof l);
		for(int i = 0;i < n;i ++)
			if (l[a[i]] == -1) l[a[i]] = i; else r[a[i]] = i;
		memset(graph,255,sizeof graph);
		for(int i = 0;i < n / 2;i ++)
			for(int j = 0;j < n / 2;j ++)
				if (i != j && l[i] < l[j] && l[j] < r[i] && r[j] > r[i]) // segment i and segment j are crossing.
					graph[i][j] = graph[j][i] = 1;
		memset(col,255,sizeof col);
		for(int i = 0;i < n / 2;i ++)
			if (col[i] == -1)
				if (!dfs_col(i,col[i] = 0)) return 0;//legal only when the graph is a bipartite graph
		return 1;
	}

	bool dfs_1(int now)
	{
		if (now == n) return test_1(); else
		{
			if (a[now] != -1) return dfs_1(now + 1);
			//asigned label
			
			for(int i = 0;i < n / 2;i ++)
				if (!cnt[i])
				{
					a[now] = i,cnt[i] ++;
					if (dfs_1(now + 1)) return 1;
					cnt[i] --;
					a[now] = -1;
					break;
				}
			for(int i = 0;i < n / 2;i ++)
				if (cnt[i] == 1)
				{
					a[now] = i,cnt[i] ++;
					if (dfs_1(now + 1)) return 1;
					cnt[i] --;
					a[now] = -1;
				}
			return 0;
		}
	}

	bool brute_force_1()
	{
		memset(cnt,0,sizeof cnt);
		for(int i = 0;i < n;i ++) if (a[i] != -1) cnt[a[i]] = 2;
		return dfs_1(0); //asign labels
	}

	int fal[55][55],up[55],other[55],l[55],r[55];

	bool test_2()
	{
		static int s[55];
		N = n + 1;
		memset(graph,255,sizeof graph);
		memset(s,0,sizeof s);
		graph[0][n] = graph[n][0] = 0;
		for(int i = n - 1;i >= 0;i --) 
		{
			if (a[i] != -1) graph[i][i + 1] = graph[i + 1][i] = 0;//this block cant place 0 or 1
			s[i] = s[i + 1] + (a[i] == -1);//how many empty blocks
		}
		for(int i = 0;i < n;i ++)
			if (a[i] != -1 && other[i] > i)
			{
				int r = other[i] + 1;
				if (up[a[i]]) graph[i][r] = graph[r][i] = 0; //even number of blocks choose up
					else graph[i][r] = graph[r][i] = (s[i] - s[r]) & 1; //even number of blocks choose down
			}
		memset(col,255,sizeof col);
		for(int i = 0;i <= n;i ++)
			if (col[i] == -1)
				if (!dfs_col(i,col[i] = 0)) return 0;
		return 1;
	}

	bool dfs_2(int now)
	{
		if (now == n) return test_2();
		if (a[now] == -1 || other[now] < now) return dfs_2(now + 1);
		//keep this segment up
		bool ok = 1;
		for(int i = 0;i < n / 2;i ++)
			if (l[i] != -1 && l[i] < now && fal[a[now]][i] && up[i]) ok = 0;
		if (ok) 
		{
			up[a[now]] = 1;
			if (dfs_2(now + 1)) return 1;
			up[a[now]] = 0;
		}
		//keep this segment down
		ok = 1;
		for(int i = 0;i < n / 2;i ++)
			if (l[i] != -1 && l[i] < now && fal[a[now]][i] && !up[i]) ok = 0;
		if (ok) 
			if (dfs_2(now + 1)) return 1;
		return 0;
	}

	bool brute_force_2()
	{
		memset(l,255,sizeof l);
		memset(fal,0,sizeof fal),memset(up,0,sizeof up);
		for(int i = 0;i < n;i ++)
			if (a[i] != -1 && l[a[i]] == -1) l[a[i]] = i; else r[a[i]] = i;
		for(int i = 0;i < n;i ++)
			if (a[i] != -1) other[i] = (i == l[a[i]]) ? r[a[i]] : l[a[i]];
		for(int i = 0;i < n / 2;i ++)
			if (l[i] != -1)
				for(int j = 0;j < n / 2;j ++)
					if (l[j] != -1 && l[i] < l[j] && l[j] < r[i] && r[j] > r[i]) fal[i][j] = fal[j][i] = 1;
		return dfs_2(0);				
	}

	string getPossibility(vector<int> labels)
	{
		n = labels.size();
		for(int i = 0;i < n;i ++) a[i] = labels[i];
		int emp = 0;
		for(int i = 0;i < n;i ++) if (a[i] == -1) ++ emp;
		bool ok;
		if (emp <= 12) //only 6 missing segments
			ok = brute_force_1(); else
				ok = brute_force_2();// only 18 existing segments 
		return ok ? "POSSIBLE" : "IMPOSSIBLE";
	}
};
