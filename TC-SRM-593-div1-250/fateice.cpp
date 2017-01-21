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
#define inf 1000000000
using namespace std;
class HexagonalBoard
{
	int n,m,a[3000],b[30000],c[30000],f[3000],p;
	inline void add_(int i,int j)
	{
		b[++m]=j;
		c[m]=a[i];
		a[i]=m;
	}
	inline void add(int i,int j)
	{
		add_(i,j);
		add_(j,i);
	}
	inline void dfs(int i)
	{
		int j;
		for(j=a[i];j>0;j=c[j])
		  if(!f[b[j]])
		    {
			 f[b[j]]=(f[i]-1^1)+1;
			 dfs(b[j]);
			}
		  else if(f[b[j]]==f[i])
		    p=1;
	}
public:
	int minColors(vector<string> x)
	{
		int w=x.size();
		int i,j;
		n=w*w;
		for(i=0;i<w;i++)
		  for(j=0;j<w;j++)
		    if(x[i][j]=='X')
		      {
			   p=1;
			   if(j<w-1 && x[i][j+1]=='X')
			     add(i*w+j+1,i*w+j+2);
			   if(i<w-1 && j && x[i+1][j-1]=='X')
			     add(i*w+j+1,i*w+w+j);
			   if(i<w-1 && x[i+1][j]=='X')
			     add(i*w+j+1,i*w+w+j+1);
			  }
		//判断0和1 
		if(!m)
		  return p;
		//判断2 
		p=0;
		for(i=1;i<=n;i++)
		  if(!f[i])
		    {
			 f[i]=1;
			 dfs(i);
			}
		return p+2;
    }
};
