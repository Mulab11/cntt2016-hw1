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
int q=1000000009;
class TheExperiment
{
	int n,s[310],f[310][310],g[310][310],h[310][310];
	int a,b;
	string x;
	inline int ff(int i,int j)
	{
		if(i>=0 && j>=0)
		  return f[i][j];
		else
		  return 0;
	}
	inline int gg(int i,int j)
	{
		if(i>=0 && j>=0)
		  return g[i][j];
		else
		  return 0;
	}
	inline int hh(int i,int j)
	{
		if(i>=0 && j>=0)
		  return h[i][j];
		else
		  return 0;
	}
	inline bool pd(int i,int j)
	{
		return i>=j && a<=s[i]-s[i-j] && s[i]-s[i-j]<=b;
	}
public:
	double countPlacements(vector<string> t,int m,int l,int aa,int bb)
	{
		int i,j,k;
		a=aa;
		b=bb;
		for(i=0;i<t.size();i++)
		  x+=t[i];
		n=x.size();
		for(i=1;i<=n;i++)
		  s[i]=s[i-1]+x[i-1]-'0';
		h[0][0]=1;
		//记录最后一段的状态 
		for(i=1;i<=n;i++)
		  for(j=0;j<=m;j++)
		    {
			 if(pd(i,l))
			   f[i][j]=(gg(i-l,j-1)+hh(i-l,j-1))%q;
			 for(k=1;k<=l;k++)
			   if(pd(i,k))
			     f[i][j]=(f[i][j]+ff(i-k,j-1))%q;
			 for(k=1;k<l;k++)
			   if(pd(i,k))
			     g[i][j]=((L)g[i][j]+gg(i-k,j-1)+hh(i-k,j-1))%q;
			 h[i][j]=(ff(i-1,j)+hh(i-1,j))%q;
			}
		return (f[n][m]+h[n][m])%q;
    }
};
