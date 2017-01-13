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
class Directed_mst
{
public:
	typedef int cost_t;
	static const int MAXN = 100, MAXM = 300;
	static const cost_t oo = (((cost_t)1) << (sizeof(cost_t) * 8 - 3));
	class Edge
	{
	public:
		Edge(){}
		Edge(int u, int v, cost_t w): u(u), v(v), w(w) {}
		int u, v;
		cost_t w;//u ----(w)---> v
	}e[MAXM];
	int inpoint[MAXN];
	cost_t incost[MAXN];
	int visit[MAXN], circle[MAXN];
	int n, m, root;
	Directed_mst(): n(0), m(0), root(-1) {}
	void insert(int u, int v, cost_t w)
	{
		if(u != v && v != root)
			e[++m] = Edge(u, v, w);
	}
	int solve()
	{
		cost_t ret = 0;
		while(1)
		{
			if(root != -1)
				inpoint[root] = -1;
			memset(incost, 63, (n + 1) * sizeof(cost_t));
			for(int i = 1; i <= m; i++)
				if(e[i].w < incost[e[i].v])
					incost[e[i].v] = e[i].w, inpoint[e[i].v] = e[i].u;
			memset(visit, -1, (n + 1) * sizeof(int));
			memset(circle, -1, (n + 1) * sizeof(int));
			int n2 = 0;
			for(int i = 1; i <= n; i++)
			{
				if(i == root)
					continue;
				if(incost[i] >= oo)
					return -1;//mst doesn't exist
				ret += incost[i];
				int u;
				for(u = i; u != -1 && visit[u] == -1; u = inpoint[u])
					visit[u] = i;
				if(u == -1 || visit[u] != i)
					continue;
				n2++;//new circle
				for(; circle[u] == -1; u = inpoint[u])
					circle[u] = n2;
			}
			if(!n2)//no circles
				break;
			for(int i = 1; i <= n; i++)
				if(circle[i] == -1)
					circle[i] = ++n2;
			n = n2;
			if(root != -1)
				root = circle[root];
			int m2 = m;
			m = 0;
			for(int i = 1; i <= m2; i++)
				insert(circle[e[i].u], circle[e[i].v], e[i].w - (circle[i] != -1 ? incost[e[i].v] : 0));
		}
		return ret;
	}
};
class FoxTheLinguist
{
private:
	Directed_mst a;
	string concatenate(const vector<string> &vec)
	{
		string ret;
		for(int i = 0; i < (int)vec.size(); i++)
			ret += vec[i];
		return ret;
	}
	int getpoint(char language, char level)
	{
		if(level == '0')
			return a.root;
		return (language - 'A') * 9 + level - '0';
	}
	int to_number(const string &s)
	{
		int ret = 0;
		for(int i = 0; i < s.size(); i++)
			ret = ret * 10 + s[i] - '0';
		return ret;
	}
public:
	int minimalHours(int n, vector<string> courseInfo)
	{
		string course = concatenate(courseInfo);
		a.n = a.root = 9 * n + 1;
		for(int i = 0; i < course.size(); i += 12)//build graph
			a.insert(getpoint(course[i], course[i + 1]), getpoint(course[i + 4], course[i + 5]), to_number(course.substr(i + 7, 4)));
		for(int i = 0; i < n; i++)
			for(int j = 2; j <= 9; j++)
				a.insert(i * 9 + j, i * 9 + j - 1, 0);//e.g. A2 -> A1
		return a.solve();//zhu liu algorithm
	}
};

