#include <bits/stdc++.h>

using namespace std;

const int maxn = 55 * 55 * 2;
const int xy[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};

class TheTilesDivOne
{
public:
	struct node
	{
		int to,next,flow;

		node(void){}
		node(int a,int b,int c) : to(a),next(b),flow(c){}
	}e[maxn * 5];

	int final[maxn],d[maxn],ord[55][55],cnt,s,t,tot;

	void link(int u,int v,int f)
	{
		e[++ tot] = node(v,final[u],f),final[u] = tot;
		e[++ tot] = node(u,final[v],0),final[v] = tot;
	}

	int level(int x,int y)
	{
		//white
		//black white
		//let the black node have level 1,one of the white has level 0 and the other has 2,than we need to find a path from level 0
		//to level 2
		if ((x + y) & 1) return (y & 1) * 2;
		return 1;
	}

	int dfs(int now,int flow)//sap
	{
		if (now == t) return flow;
		int use = 0;
		for(int i = final[now];i;i = e[i].next)
			if (e[i].flow > 0 && d[e[i].to] + 1 == d[now])
			{
				int tmp = dfs(e[i].to,min(e[i].flow,flow - use));
				e[i].flow -= tmp,e[i ^ 1].flow += tmp,use += tmp;
				if (use == flow) return use;
			}
		++ d[now];
		return use;
	}

	int find(vector <string> board)
	{
		tot = 1;
		int n = board.size(),m = board[0].length();
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < m;j ++) ord[i][j] = ++ cnt;
		s = 0,t = cnt * 2 + 1;
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < m;j ++)
			{
				if (board[i][j] == '.') link(ord[i][j],ord[i][j] + cnt,1);//define ord[i][j] as inner node,ord[i][j]+n as outer node
				if (level(i,j) == 2) link(ord[i][j] + cnt,t,1);
				if (level(i,j) == 0) link(s,ord[i][j],1);
				for(int dir = 0;dir < 4;dir ++)
				{
					int x = i + xy[dir][0],y = j + xy[dir][1];
					if (x >= 0 && y >= 0 && x < n && y < m && level(i,j) + 1 == level(x,y)) //find the next node on the path
						link(ord[i][j] + cnt,ord[x][y],1);
				}
			}
		int tmp = 0;
		for(;d[s] < t + 1;tmp += dfs(s,1 << 30));//maxflow
		return tmp;
	}
}work;

int main()
{
	work.find({"X.X",
		 "...",
		 "X.X"}
		);
}
