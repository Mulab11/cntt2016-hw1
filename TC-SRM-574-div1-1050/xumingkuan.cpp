#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
/*class Edge
{
public:
	int to, next;
};*/
class Tunnels
{
private:
	vector<string> frame;
	int n, m;
	bool in(int x, int y)
	{
		return x >= 0 && x < n && y >= 0 && y < m;
	}
	bool isX(int x, int y)
	{
		return in(x, y) ? frame[x][y] == 'X' : false;
	}
	int countAdjacentX(int x, int y)
	{
		return isX(x, y - 1) + isX(x, y + 1) + isX(x - 1, y) + isX(x + 1, y);
	}
	bool checkIfThereIsAtLeast1X()
	{
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				if(frame[i][j] == 'X')
					return true;
		return false;
	}
	
	int number[60][2];
	int tot;//number of points
	bool visit[60][60];
	int a[120][4];//left up, right up, left down, right down
	int type[60];
	bool dfs(int x, int y, char ch = 'X')
	{
		if(!isX(x, y) || visit[x][y])
			return false;
		visit[x][y] = true;
		frame[x][y] = ch;//for debug
		if(!dfs(x, y - 1, ch) && !dfs(x, y + 1, ch) && !dfs(x + 1, y, ch))//end point
		{
			if(y == 0)
				a[tot][2] = x;
			if(y == m - 1)
				a[tot][3] = x;
		}
		return true;
	}
	/*int head[300], en;
	Edge e[5050];
	void insert(int u, int v)
	{
		printf("insert %c %c\n", 'a' + u - 1, 'a' + v - 1);
		e[++en].to = v;
		e[en].next = head[u];
		head[u] = en;
	}
	int match[300];
	bool visit2[300];
	bool find(int x)
	{
		for(int i = head[x]; i > 0; i = e[i].next)
			if(!visit2[e[i].to])
			{
				visit2[e[i].to] = true;
				if(!match[e[i].to] || find(match[e[i].to]))
				{
					match[e[i].to] = x;
					return true;
				}
			}
		return false;
	}
	int getMaxMatch()
	{
		memset(match, 0, sizeof(match));
		int ret = 0;
		for(int i = 1; i <= tot; i++)
		{
			memset(visit2, false, sizeof(visit2));
			if(find(i))
				ret++;
		}
		for(int i = 0; i < n; i++)
			printf("%s\n", frame[i].c_str());
		memset(visit2, false, sizeof(visit2));
		for(int i = tot; i >= 1; i--)
			if(!visit2[i] && match[i])
			{
				printf("%c", 'a' + i - 1);
				visit2[i] = true;
				for(int j = match[i]; j; j = match[j])
					visit2[j] = true, printf("-%c", 'a' + j - 1);
				printf("\n");
			}
		return ret;
	}*/
	int f[60][60][60];
	int getMaxMatch()
	{
		#define update(addj, addk, addv) \
		for(int j = 0; j <= i; j++)\
			for(int k = 0; k <= i; k++)\
				if((tmp = f[i][j][k]) >= 0 && j + (addj) >= 0 && k + (addk) >= 0)\
					f[i + 1][j + (addj)][k + (addk)] = max(f[i + 1][j + (addj)][k + (addk)], tmp + (addv));
		memset(f, -1, sizeof(f));
		f[0][0][0] = 0;
		for(int i = 0; i < n; i++)
		{
			int tmp;
			if(type[i] & 1)//left up
				update(-1, !!(type[i] & 8), 1);
			if(type[i] & 2)//right up
				update(!!(type[i] & 4), -1, 1);
			if(type[i] == 15)//horizontal line
			{
				update(0, 1, 0);
				update(1, 0, 0);
			}
			else
			{
				if((type[i] & 1) && (type[i] & 2))//left up and right up
					update(-1, -1, 2);
				update(!!(type[i] & 4), !!(type[i] & 8), 0);//left down or/and right down
			}
			/*int ret = 0; //for debug
			for(int j = 0; j <= i; j++)
				for(int k = 0; k <= i; k++)
				{
					if(f[i][j][k] >= 0)
						printf("f[%d][%d][%d] = %d\n", i, j, k, f[i][j][k]);
					ret = max(ret, f[i][j][k]);
				}
			printf("%d: %d\n", i, ret);*/
		}
		int ret = 0;
		for(int j = 0; j <= n; j++)
			for(int k = 0; k <= n; k++)
				ret = max(ret, f[n][j][k]);
		return ret;
	}
	void checkNewTunnel(int i, int j)
	{
		/*
		.. .. ..
		XX X. X.
		.. X. ..
		   ..
		
		#0 #1 #2
		*/
		if(isX(i, j) && !visit[i][j] && countAdjacentX(i, j) <= 1)
		{
			tot++;
			a[tot][0] = !j ? i - !i : -1;//"up" at line 0 is useless
			a[tot][1] = j == m - 1 ? i - !i : -1;
			a[tot][2] = a[tot][3] = n;
			//dfs(i, j, 'a' + tot - 1);//for debug
			dfs(i, j);
			if(!j && a[tot][3] == i)//horizontal line, case #0
				a[tot][0] = a[tot][1] = a[tot][2] = i;//also set a[tot][0] to i because it may be set to -1 as i may be 0
			if(i && a[tot][(j == m - 1) + 2] == i + 1)//case #1
				a[tot][(j == m - 1) + 2] = n;
			if(i && a[tot][(j == m - 1) + 2] == i && a[tot][!j + 2] == n)//case #2
				a[tot][(j == m - 1) + 2] = n;
			//printf("tunnel %c: %d %d %d %d\n", 'a' + tot - 1, a[tot][0], a[tot][1], a[tot][2], a[tot][3]);
			for(int i = 0; i <= 3; i++)
				if(a[tot][i] != -1 && a[tot][i] != n)
					type[a[tot][i]] |= (1 << i);
		}
	}
public:
	int minimumTunnels(vector<string> frame)
	{
		this->frame = frame;
		n = frame.size();
		m = frame[0].size();
		if(m == 1)
			return checkIfThereIsAtLeast1X();//the code below is not compatible with the case when m == 1
		tot = 0;
		memset(type, 0, sizeof(type));
		for(int i = 1; i < m - 1; i++)//enumerate the start point (it can't appear elsewhere)
			checkNewTunnel(0, i);
		for(int i = 0; i < n; i++)
		{
			checkNewTunnel(i, 0);
			checkNewTunnel(i, m - 1);
		}
		/*en = 0;//zui xiao lian fu gai, WA (it can't handle the case of horizontal line)
		memset(head, -1, sizeof(head));
		for(int i = 1; i <= tot; i++)
			for(int j = i + 1; j <= tot; j++)
				if(a[i][2] + 1 < a[j][0] || a[i][3] + 1 < a[j][1])//link at left/right
					insert(i, j);*/
		return tot - getMaxMatch();
	}
};

