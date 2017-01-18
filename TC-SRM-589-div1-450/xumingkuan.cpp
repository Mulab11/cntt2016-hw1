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
const int MAXN = 55, MAXM = 1515;
class Edge
{
public:
	int to, next;
};
class GearsDiv1
{
private:
	int n;//number of gears
	int match[MAXN];
	Edge e[MAXM];//adjacency list
	int head[MAXN], en;
	vector<int> place[3];
	vector<string> graph;
	int visit[MAXN], vn;
	void clearedge()
	{
		memset(head, -1, sizeof(head));
		en = 0;
	}
	void insert(int u, int v)
	{
		e[++en].to = v;
		e[en].next = head[u];
		head[u] = en;
	}
	bool find(int x)//Hungarian algorithm
	{
		for(int i = head[x]; i > 0; i = e[i].next)
			if(visit[e[i].to] != vn)
			{
				visit[e[i].to] = vn;
				if(match[e[i].to] == -1 || find(match[e[i].to]))
				{
					match[e[i].to] = x;
					return true;
				}
			}
		return false;
	}
	int solve(int col1, int col2)
	{
		clearedge();
		memset(match, -1, sizeof(match));
		memset(visit, -1, sizeof(visit));
		vn = 0;
		for(int i = 0; i < place[col1].size(); i++)
			for(int j = 0; j < place[col2].size(); j++)
				if(graph[place[col1][i]][place[col2][j]] == 'Y')
					insert(i, j);
		int ret = 0;
		for(int i = 0; i < place[col1].size(); i++)
		{
			vn++;
			ret += find(i);
		}
		return ret;
	}
public:
	int getmin(string color, vector<string> graph)
	{
		n = color.size();
		for(int i = 0; i < n; i++)
			place[color[i] == 'R' ? 0 : color[i] == 'G' ? 1 : 2].push_back(i);
		this->graph = graph;
		return min(solve(0, 1), min(solve(1, 2), solve(2, 0)));
	}
};

