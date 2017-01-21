#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include<map>
#define L long long
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
class CoinsGame
{
	int n,m,x[2500],a[50][50],b[50][50],p,q,ans,mod=1000000009;
	char s[50][50];
	map<long long,int> f;
	inline void orz()  //计算每个点进过若干轮所能达到的状态集合 
	{
		int i,j;
		long long k;
		p=0;
		for(i=1;i<=n;i++)
		  for(j=1;j<=m;j++)
		    if(s[i][j]=='.')
		      {
			   k=(s[i-1][j]=='#'?a[i][j]:a[i-1][j]);
			   k+=(s[i][j-1]=='#'?a[i][j]:a[i][j-1])*10000;
			   k+=(s[i+1][j]=='#'?a[i][j]:a[i+1][j])*100000000ll;
			   k+=(s[i][j+1]=='#'?a[i][j]:a[i][j+1])*1000000000000ll;
			   if(f[k])
			     b[i][j]=f[k];
			   else
			     f[k]=b[i][j]=++p;
			  }
		f.clear();
		k=0;
		for(i=1;i<=n;i++)
		  for(j=1;j<=m;j++)
		    if(s[i][j]=='.' && a[i][j]!=b[i][j])
		      k=1;
		if(k)
		  {
		   for(i=1;i<=n;i++)
		     for(j=1;j<=m;j++)
		       a[i][j]=b[i][j];
		   orz();
		  }
	}
	inline int power(int a,int b)
	{
		if(!b)
		  return 1;
		int c=power(a,b>>1);
		c=(L)c*c%mod;
		if(b&1)
		  c=(L)c*a%mod;
		return c;
	}
public:
	int ways(vector<string> s_)
	{
		int i,j;
		n=s_.size();
		m=s_[0].size();
		for(i=1;i<=n;i++)
		  for(j=1;j<=m;j++)
		    {
			 s[i][j]=s_[i-1][j-1];
			 a[i][j]=1;
			}
		orz();
		for(i=1;i<=n;i++)
		  for(j=1;j<=m;j++)
		    if(s[i][j]=='.')
		      q++,x[a[i][j]]++;
		ans=power(2,q)-1;
		for(i=1;i<=p;i++)
		  ans=(ans+mod-power(2,x[i])+1)%mod;
		return ans;
    }
};
