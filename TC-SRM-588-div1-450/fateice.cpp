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
class KeyDungeonDiv1
{
	int n,f[5000][200],s[5000],p=0;
public:
	int maxKeys(vector<int> r,vector<int> g,vector<int> a,vector<int> b,vector<int> c,vector<int> m)
	{
		int i,j,k,R,G,W;
		n=r.size();
		s[0]=m[0]+m[1]+m[2];
		for(i=1;i<(1<<n);i++)
		  {
		   for(j=0;j<n;j++)
		     if((i^(1<<j))<i)
		       break;
		   s[i]=s[i^(1<<j)]+a[j]+b[j]+c[j]-r[j]-g[j];
		  }
		for(i=0;i<(1<<n);i++)
		  for(j=0;j<=150;j++)
		    f[i][j]=-1;
		f[0][m[0]]=m[2];
		//状压dp 
		for(i=0;i<(1<<n);i++)
		  for(j=0;j<=150;j++)
		    if(f[i][j]>=0)
		      {
			   R=j;
			   W=f[i][j];
			   G=s[i]-R-W;
			   p=max(p,s[i]);
		       for(k=0;k<n;k++)
		         if((i^(1<<k))>i)
				   if(max(0,r[k]-R)+max(0,g[k]-G)<=W)
				     f[i^(1<<k)][max(0,R-r[k])+a[k]]=max(f[i^(1<<k)][max(0,R-r[k])+a[k]],W-(max(0,r[k]-R)+max(0,g[k]-G))+c[k]);
			  }
		return p;
    }
};
