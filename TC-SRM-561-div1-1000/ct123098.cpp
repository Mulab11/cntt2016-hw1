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

const int MAXL = 50;
const int MAXN = MAXL * MAXL + 100;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

class Orienteering
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
	
	double getF(int a, int b, int m)
	{
		double ret = 1.0;
		for(int i = 0; i <= a - b - 1; i++)
			ret *= a - m - i, ret /= a - i;
		return ret;
	}
	
	int tot, totc, n, m, k;
	int id[MAXL][MAXL];
	int size[MAXN];
	vector<int> sp;
	int dis[MAXN][MAXN];
	double ans1, ans2;
	
	void getPath(vector<string> &graph, int x, int y)
	{
		id[x][y] = ++tot;
		if(graph[x][y] == '*') sp.push_back(id[x][y]), size[id[x][y]] = 1, totc++;
		for(int i = 0; i < 4; i++)
		{
			int xx = x + dx[i], yy = y + dy[i];
			if(xx < 0 || xx > n - 1 || yy < 0 || yy > m - 1) continue;
			if(graph[xx][yy] == '#') continue;
			if(id[xx][yy]) continue;
			getPath(graph, xx, yy);
			addE(id[x][y], id[xx][yy]), addE(id[xx][yy], id[x][y]);
		}
	}
	
	void getDist(int x, int fa, int ro, int di)
	{
		dis[ro][x] = di;
		for(int i = p[x]; i; i = e[i].next)
			if(e[i].to != fa)
				getDist(e[i].to, x, ro, di + 1);
	}
	
	void getAns1(int x, int fa)
	{
		for(int i = p[x]; i; i = e[i].next)
			if(e[i].to != fa)
			{
				int y = e[i].to;
				getAns1(y, x);
				size[x] += size[y];
				ans1 += 1 - getF(totc, size[y], k) - getF(totc, totc - size[y], k);
			}
	}
	
	bool cmp(int x, int y, int a, int b)
	{
		if(dis[x][y] != dis[a][b])
			return dis[x][y] > dis[a][b];
		if(max(x, y) != max(a, b))
			return max(x, y) > max(a, b);
		return min(x, y) > min(a, b);
	}
	
	void getAns2()
	{
		for(int i = 0; i < sp.size(); i++)
			for(int j = i + 1; j < sp.size(); j++)
			{
				int cnt = 0;
				for(int l = 0; l < sp.size(); l++)
					if(l != i && l != j)
						if(cmp(sp[i], sp[j], sp[i], sp[l]) && cmp(sp[i], sp[j], sp[j], sp[l]))
							cnt++;
				if(cnt < k - 2) continue;
				double tmp = 1.0 * k * (k - 1) / totc / (totc - 1);
				ans2 += dis[sp[i]][sp[j]] * tmp * getF(totc - 2, cnt, k - 2);
			}
	}
	
	double expectedLength(vector<string> field, int K)
	{
	 	l = 2;
		n = field.size();
		m = field[0].size();
		k = K;
		for(int i = 0, flag = false; i < n && !flag; i++)
			for(int j = 0; j < m && !flag; j++)
				if(field[i][j] != '#')
					getPath(field, i, j), flag = true;
		for(int i = 0; i < sp.size(); i++)
			getDist(sp[i], 0, sp[i], 0);
		
		ans1 = ans2 = 0;
		
		getAns1(1, 0);
		getAns2();
//		cout << ans1 << ' ' << ans2 << endl;
		
		
		return 2 * ans1 - ans2;
	}
};

