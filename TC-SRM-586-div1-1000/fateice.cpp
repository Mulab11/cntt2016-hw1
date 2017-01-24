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
#define inf 1000000000;
using namespace std;
class StringWeight
{
	int n,f[100][100][100],p=inf;   //f[i][j][k]表示前i段子串，使用过j个字符，有k个不能再使用的方案
	inline int sqr(int x)
	{
		return x*(x+1)/2;
	}
public:
	int getMinimum(vector<int> x)
	{
		int i,j,k,l,u,v,w;
		n=x.size();
		for(i=0;i<=n;i++)
		  for(j=0;j<=26;j++)
		    for(k=0;k<=26;k++)
		      f[i][j][k]=inf;
		f[0][0][0]=0;
		for(i=0;i<n;i++)
		  for(j=0;j<=26;j++)
		    for(k=0;k<=j;k++)
			  for(l=max(0,min(x[i],26)+k-j);j+l<=26;l++)
			    for(u=0;u+k<=j+l;u++)
		          {
				   v=f[i][j][k];
				   w=min(j-k,u);
			       v+=sqr(w);
			       w=max(0,j-k-u);
			       v+=w*x[i]+(!w)*max(0,x[i]-26);
		       	   w=min(l,j+l-k-u);
			       f[i+1][j+l][k+u]=min(f[i+1][j+l][k+u],v+sqr(w-1));
		          }
		for(i=0;i<=26;i++)
		  p=min(p,f[n][i][i]);
		return p;
	}
};
