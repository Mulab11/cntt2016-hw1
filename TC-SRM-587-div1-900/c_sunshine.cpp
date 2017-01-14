#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class ThreeColorability
{
	public:
	int n,m,flag;
	int g[105][105],c[105];
	
	void dfs(int x,int t)//depth first search
	{
		c[x]=t;
		for(int i=0;i<n+m&&flag;i++)
			if(g[x][i]!=-1)
			{
				if(c[i]==-1)dfs(i,t^g[x][i]);
				else if(c[i]!=(t^g[x][i]))flag=0;
			}
	}
	
	bool check()//use dfs to determine if there is an odd-cycle
	{
		flag=1;
		memset(c,-1,sizeof(c));
		for(int i=0;i<n+m;i++)
			if(c[i]==-1)
				dfs(i,0);
		return flag;
	}
	
	vector<string> lexSmallest(vector<string> cells)
	{
		vector<string> res;
		n=cells.size();
		m=cells[0].size();
		
		//notice that:
		// NN NY
		// NY YY
		//is not 3-colorable
		//the adjacent rows and columns mush have the same or total different pattern
		
		memset(g,-1,sizeof(g));
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(cells[i][j]!='?')
					g[i][n+j]=g[n+j][i]=cells[i][j]=='Z';
		if(!check())return res;
		// pick each block check if it can be 'N'
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(cells[i][j]=='?')
				{
					g[i][n+j]=g[n+j][i]=0;
					if(!check())//check if it is possible to fill out the '?'s.
						g[i][n+j]=g[n+j][i]=1;
				}
		res=vector<string>(n,"");//get answer
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				res[i]+=g[i][n+j]?'Z':'N';
		return res;
	}
};

