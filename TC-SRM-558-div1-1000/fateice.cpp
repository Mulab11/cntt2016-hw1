#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1},inf=1000000000;
class SurroundingGame
{
    int n,m,r,w,a[1000],b[1000000],c[1000000],d[1000000],f[1000],g[1000],q,p;
    bool x[1000];
	inline int get(int i,int j)
	{
		return i*m+j+1;
	}
	inline int get(char x)
	{
		if(x>='0' && x<='9')
		  return x-'0';
		else if(x>='a' && x<='z')
		  return x-'a'+10;
		else
		  return x-'A'+36;
	}
	inline void add_(int i,int j,int k)
    {
		b[++r]=j;
		c[r]=k;
		d[r]=a[i];
		a[i]=r;
	}
	inline void add(int i,int j,int k)
	{
		add_(i,j,k);
		add_(j,i,0);
	}
	inline bool bfs()
	{
		int i,j;
		for(i=1;i<=w+1;i++)
		  f[i]=x[i]=0;
		q=1;
		f[0]=1;
		for(i=1;i<=q;i++)
		  for(j=a[g[i]];j>0;j=d[j])
		    if(c[j] && !f[b[j]])
		      {
			   f[b[j]]=f[g[i]]+1;
			   g[++q]=b[j];
			   if(b[j]==w+1)
			     return 1;
			  }
		return 0;
	}
	inline int dfs(int i,int k)
	{
		int j,l=0,u;
		if(i==w+1)
		  return k;
		x[i]=1;
		for(j=a[i];j>0;j=d[j])
		  if(c[j] && !x[b[j]] && f[b[j]]==f[i]+1)
		    {
			 u=dfs(b[j],min(k-l,c[j]));
			 l+=u;
			 c[j]-=u;
			 c[(j-1^1)+1]+=u;
			 if(l==k)
			   {
				x[i]=0;
				return l;
			   }
			}
		return l;
	}
public:
	int maxScore(vector<string> a,vector<string> b)
	{
		int i,j,k;
		n=a.size();
		m=a[0].size();
		w=2*n*m;
		for(i=0;i<n;i++)
		  for(j=0;j<m;j++)
		    if(i+j&1)  //黑白染色 
		      {
			   add(0,get(i,j),get(a[i][j]));    //割掉表示这格选 
			   add(get(i,j),w+1,get(b[i][j]));  //割掉表示这格不选 
			   add(0,get(i,j)+n*m,get(b[i][j]));  //割掉表示相邻格子不选 
			   add(get(i,j)+n*m,get(i,j),inf);    //相邻格子都选的情况下这个格子一定不选 
			   for(k=0;k<4;k++)
			     if(i+dx[k]>=0 && i+dx[k]<n && j+dy[k]>=0 && j+dy[k]<m)
			       add(get(i,j)+n*m,get(i+dx[k],j+dy[k]),inf);   //相邻格子都选 
			  }
			else
		      {
			   add(0,get(i,j),get(b[i][j]));
			   add(get(i,j),w+1,get(a[i][j]));
			   add(get(i,j)+n*m,w+1,get(b[i][j]));
			   add(get(i,j),get(i,j)+n*m,inf);
			   for(k=0;k<4;k++) 
			     if(i+dx[k]>=0 && i+dx[k]<n && j+dy[k]>=0 && j+dy[k]<m)
			       add(get(i+dx[k],j+dy[k]),get(i,j)+n*m,inf);
			  }
		for(i=0;i<n;i++)
		  for(j=0;j<m;j++)
		    p+=get(b[i][j])*2;
		while(bfs())
		  p-=dfs(0,inf);
		return p;
    }
};
