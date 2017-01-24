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
int mod=1000000007;
class GooseInZooDivOne
{
	int n,m,x[60][60],a[2510],b[2510],d,p,q,t;
	bool y[2510];
	inline int dfs(int i)
	{
		int j,k,l=1;
		y[i]=1;
		for(j=0;j<n;j++)
		  for(k=0;k<n;k++)
		    if(x[j][k] && !y[x[j][k]] && abs(j-a[i])+abs(k-b[i])<=d)
		      l+=dfs(x[j][k]);
		return l;
	}
	inline int pow(int i)
	{
		int j,k=1;
		for(j=1;j<=i;j++)
		  k=(k<<1)%mod;
		return k;
	}
public:
	int count(vector<string> s,int dd)
	{
		int i,j;
		d=dd;
		n=s.size();
		m=s.size();
		for(i=0;i<n;i++)
		  for(j=0;j<m;j++)
		    if(s[i][j]=='v')
		      {
		       x[i][j]=++t;
		       a[t]=i;
		       b[t]=j;
			  }
		for(i=1;i<=t;i++)
		  if(!y[i])
		    if(dfs(i)&1)
		      p++;
		    else
		      q++;
		return (pow(max(p-1,0)+q)+mod-1)%mod;
    }
};
