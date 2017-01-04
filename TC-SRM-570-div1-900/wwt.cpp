#include <bits/stdc++.h>

using namespace std;

const int maxn = 30 * 30 * 2;
const int xy[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

struct node
{
	int to,next,flow,cost;

	node(void){}
	node(int a,int b,int c,int d) : to(a),next(b),flow(c),cost(d){}
}e[maxn * 105];

class CurvyonRails
{
public:
	int final[maxn],s,t,tot,cnt,ans;
	int row[50][50],col[50][50];// for a single point,we divide into 2 points,one of which is moving by rows and another is moving by columns

	int maxflow()
	{
		ans = 0;
		int fl = 0;
		static bool in[maxn];
		static int d[maxn],que[maxn * maxn],pre[maxn];
		for(;;)
		{
			for(int i = s;i <= t;i ++) d[i] = (1 << 30),in[i] = 0;
			d[s] = 0;
			que[1] = s;
			for(int fi = 1,en = 1;fi <= en;fi ++)
			{
				int u = que[fi];
				for(int i = final[u];i;i = e[i].next)
					if (e[i].flow > 0 && d[e[i].to] > d[u] + e[i].cost)
					{
						d[e[i].to] = d[u] + e[i].cost;
						pre[e[i].to] = i;
						if (!in[e[i].to]) que[++ en] = e[i].to,in[e[i].to] = 1;
					}
				in[u] = 0;
			}
			if (d[t] == (1 << 30)) break;
			fl ++;
			ans += d[t];
			for(int i = t;i;i = e[pre[i] ^ 1].to)
				e[pre[i]].flow --,e[pre[i] ^ 1].flow ++;
		}
		return fl;
	}

	void link(int u,int v,int f,int c)
	{
		e[++ tot] = node(v,final[u],f,c),final[u] = tot;
		e[++ tot] = node(u,final[v],0,-c),final[v] = tot;
	}

	int getmin(vector<string> field)
	{	
		int n = field.size(),m = field[0].length();
		tot = 1;
		cnt = 0;
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < m;j ++)
				if (field[i][j] != 'w') 
					row[i][j] = ++ cnt,col[i][j] = ++ cnt;
		s = 0,t = ++ cnt;
		int f1 = 0,f2 = 0;
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < m;j ++)
				if (field[i][j] != 'w')
				{
					if ((i + j) & 1) link(s,row[i][j],1,0),link(s,col[i][j],1,0),f1 += 2; else //bipartite graph
						link(row[i][j],t,1,0),link(col[i][j],t,1,0),f2 += 2;
					link(row[i][j],col[i][j],1,field[i][j] == 'C'); //we need cost to change the direction
					link(col[i][j],row[i][j],1,field[i][j] == 'C');
					if ((i + j) & 1) //black to white
					{
						for(int d = 0;d < 4;d ++)
						{
							int nx = i + xy[d][0],ny = j + xy[d][1];
							if (nx >= 0 && ny >= 0 && nx < n && ny < m && field[nx][ny] != 'w')
							{
								if (d < 2)
									link(row[i][j],row[nx][ny],1,0); else
										link(col[i][j],col[nx][ny],1,0);
							}
						}
					}
				}
		if (f1 != f2 || maxflow() != f1) return -1;//cannot fullfill the need of every empty cell
		return ans;
	}
};
