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
class Edge
{
public:
	int to, next;
};
class GooseTattarrattatDiv1
{
private:
	int n;//length of S
	int cntLetter[26];
	Edge e[60];//adjacency list
	int head[26], en;
	void clearedge()
	{
		memset(head, -1, sizeof(head));
		en = 1;
	}
	void insert(int u, int v)
	{
		if(u == v)
			return;
		e[++en].to = v;
		e[en].next = head[u];
		head[u] = en;
		e[++en].to = u;
		e[en].next = head[v];
		head[v] = en;
	}
	int sum, mx;
	bool visit[26];
	void dfs(int p)
	{
		visit[p] = true;
		sum += cntLetter[p];
		mx = max(mx, cntLetter[p]);
		for(int i = head[p]; i > 0; i = e[i].next)
			if(!visit[e[i].to])
				dfs(e[i].to);
	}
public:
	int getmin(string S)
	{
		n = S.size();
		memset(cntLetter, 0, sizeof(cntLetter));
		for(int i = 0; i < n; i++)
			cntLetter[S[i] - 'a']++;
		clearedge();
		for(int i = 0; i < n / 2; i++)
			if(S[i] != S[n - 1 - i])
				insert(S[i] - 'a', S[n - 1 - i] - 'a');//these two letters should be same
		memset(visit, false, sizeof(visit));
		int ans = 0;
		for(int i = 0; i < 26; i++)
			if(!visit[i])//consider the connected block with i
			{
				sum = mx = 0;
				dfs(i);
				ans += sum - mx;
			}
		return ans;
	}
};

