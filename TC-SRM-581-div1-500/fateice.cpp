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
class TreeUnion
{
	int n,a[310],b[610],c[610],f[10],g[10];
	double p;
	inline void dfs(int i,int j,int k,int f[])
	{
		f[k]++;
		if(k==4)
		  return;
		int l;
		for(l=a[i];l>0;l=c[l])
		  if(b[l]!=j)
		    dfs(b[l],i,k+1,f);
	}
	inline void orz(vector<string> x,int f[])
	{
		int i,j,k;
		string y;
		y.clear();
		for(i=0;i<x.size();i++)
		  y+=x[i];
		n=1;
		//建树 
		for(i=0;i<y.size();i=j+1)
		  {
		   for(j=i,k=0;j<y.size() && y[j]!=' ';j++)
		     k=k*10+y[j]-'0';
		   k++;
		   n++;
		   b[2*n-3]=k;
		   c[2*n-3]=a[n];
		   a[n]=2*n-3;
		   b[2*n-2]=n;
		   c[2*n-2]=a[k];
		   a[k]=2*n-2;
		  }
		//搜索距离为1~4的点对数量 
		for(i=1;i<=n;i++)
		  dfs(i,0,0,f);
		for(i=1;i<=n;i++)
		  a[i]=0;
		for(i=1;i<=2*n;i++)
		  b[i]=c[i]=0;
	}
public:
	double expectedCycles(vector<string> a,vector<string> b,int k)
	{
		int i,j;
		orz(a,f);
		orz(b,g);
		//枚举两棵树中的点对距离 
		for(i=1;i<k-2;i++)
		  p+=double(f[i])*g[k-2-i]/n/(n-1)/2;
		return p;
    }
};
