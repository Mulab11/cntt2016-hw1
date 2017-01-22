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
class PolygonTraversal
{
	int m;
	long long f[300000][20],p;
public:
	long long count(int n,vector<int> x)
	{
		int i,j,k,l,u,v;
		for(i=0;i<x.size();i++)
		  m|=1<<x[i]-1;
		f[m][x[x.size()-1]-1]=1;
		//状压dp 
		for(i=m+1;i<(1<<n);i++)
		  for(j=0;j<n;j++)
		    if((i^(1<<j))<i)
		      for(k=0;k<n;k++)
		        if((i^(1<<k))<i)
		          {
				   for(l=0,u=v=0;l<n;l++)
				     if(l!=j && l!=k && (i^(1<<l))<i)
				       if((l<j)^(l<k))
				         u=1;
				       else
				         v=1;
				   if(u && v)
				     f[i][j]+=f[i^(1<<j)][k];
				  }
		for(i=0;i<n;i++)
		  if(abs(i-x[0]+1)!=1 && abs(i-x[0]+1)!=n-1)
		    p+=f[(1<<n)-1][i];
		return p;
    }
};
