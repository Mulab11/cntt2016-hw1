#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
const int M=1000000009;
const int dx[4]={-1,1,0,0};
const int dy[4]={0,0,-1,1};

class CoinsGame
{
	public:
	int R,C,n;
	int I[45][45];
	int f[45][45][45][45],g[1666][1666];
	char s[45][45];
	
	int q[3500000],qh,qt;
	
	int sz[1666],fa[1666];
	
	void Push(const int &a,const int &b,const int &c,const int &d)
	{
		if(!f[a][b][c][d])
		{
			f[a][b][c][d]=1;
			q[++qt]=a|b<<6|c<<12|d<<18;
		}
	}
	void Pop(int &a,int &b,int &c,int &d)
	{
		int t=q[++qh];
		a=t&63;t>>=6;
		b=t&63;t>>=6;
		c=t&63;t>>=6;
		d=t&63;
	}
	
	int pow(int a,int b)
	{
		int s=1;
		for(;b;b>>=1,a=(LL)a*a%M)
			if(b&1)s=(LL)s*a%M;
		return s;
	}
	
	int getfa(int x)
	{return fa[x]?fa[x]=getfa(fa[x]):x;}
	
	void merge(int x,int y)
	{
		x=getfa(x),y=getfa(y);
		if(x!=y)fa[y]=x,sz[x]+=sz[y];
	}
	
	int ways(vector<string> board)
	{
		int ans=0;
		R=board.size(),C=board[0].size();
		for(int i=1;i<=R;i++)
			for(int j=1;j<=C;j++)
			{
				s[i][j]=board[i-1][j-1];
				if(s[i][j]=='.')I[i][j]=++n;
			}
		//Push each pair of cells into the queue one of which are sill on the board and the other one has just been moved off from the board.
		for(int i=1;i<=R;i++)
			for(int j=1;j<=C;j++)
				if(s[i][j]=='.')
				{
					for(int k=1;k<=R;k++)
					{
						Push(i,j,k,0);
						Push(k,0,i,j);
						Push(i,j,k,C+1);
						Push(k,C+1,i,j);
					}
					for(int k=1;k<=C;k++)
					{
						Push(i,j,0,k);
						Push(0,k,i,j);
						Push(i,j,R+1,k);
						Push(R+1,k,i,j);
					}
				}
		int x1,y1,x2,y2;
		while(qh<qt)//Use breadth first search to get all possible pairs of cells that are essentially different.
		{
			Pop(x1,y1,x2,y2);
			for(int i=0;i<4;i++)
			{
				if(s[x1+dx[i]][y1+dy[i]]=='.'&&s[x2+dx[i]][y2+dy[i]]=='.')//Both moved
					Push(x1+dx[i],y1+dy[i],x2+dx[i],y2+dy[i]);
				if(s[x1+dx[i]][y1+dy[i]]=='.'&&s[x2-dx[i]][y2-dy[i]]=='#')//The first one moved
					Push(x1+dx[i],y1+dy[i],x2,y2);
				if(s[x1-dx[i]][y1-dy[i]]=='#'&&s[x2+dx[i]][y2+dy[i]]=='.')//The second one moved
					Push(x1,y1,x2+dx[i],y2+dy[i]);
			}
		}
		//Find all possible pairs of cells that are essentially different. 
		for(x1=1;x1<=R;x1++)
			for(y1=1;y1<=C;y1++)
				for(x2=1;x2<=R;x2++)
					for(y2=1;y2<=C;y2++)
						if(s[x1][y1]=='.'&&s[x2][y2]=='.')
							g[I[x1][y1]][I[x2][y2]]=f[x1][y1][x2][y2];
		//Find equivalence classes
		for(int i=1,j;i<=n;i++)
			for(sz[i]=j=1;j<i;j++)
				if(!g[i][j])merge(i,j);
		//anser = 2^n - 1 - \sum 2^|C_i| - 1
		ans=pow(2,n)-1;
		for(int i=1;i<=n;i++)
			if(!fa[i])ans=(ans-pow(2,sz[i])+1)%M;
		if(ans<0)ans+=M;
		return ans;
	}
};

