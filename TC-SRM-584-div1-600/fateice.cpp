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
class Excavations
{
	int n,m,d[60],x[60][60];
	long long f[60][60],C[60][60],p;
public:
	long long count(vector<int> a,vector<int> b,vector<int> c,int q)
	{
		int i,j,k,l,u,v;
		n=50;
		m=c.size();
		if(q<m)
		  return 0;
		for(i=0;i<=n;i++)
		  {
		   C[i][0]=1;
		   for(j=1;j<=i;j++)
		     C[i][j]=C[i-1][j]+C[i-1][j-1];
		  }
		for(i=0;i<a.size();i++)
		  x[a[i]][++x[a[i]][0]]=b[i];
		for(i=1;i<=n;i++)
		  if(x[i][0])
		    sort(x[i]+1,x[i]+x[i][0]+1);
		for(i=0;i<m;i++)
		  d[c[i]]=1;
		//枚举探测到的最小点 
		for(u=1;u<=n;u++)
		  if(d[u])
		    for(v=1;v<=x[u][0];v++)
		      {
			   //dp
			   f[0][0]=1;
			   for(i=1;i<=n;i++)
			     for(j=0;j<=n;j++)
			       {
					f[i][j]=0;
					x[i][x[i][0]+1]=2000000000;
			        for(k=1;k<=x[i][0]+1;k++)
			          if(!d[i])
			            {
						 if(x[i][k]>x[u][v])
						   {
							if(j-(x[i][0]-k+1)>=0)
							  f[i][j]+=f[i-1][j-(x[i][0]-k+1)];
							break;
						   }
						}
					  else if(i<u && x[i][k]<x[u][v] || i==u && k==v || i>u && x[i][k]<=x[u][v])
					    if(j-(x[i][0]-k)>=0)
					      f[i][j]+=f[i-1][j-(x[i][0]-k)];
				  }
			   for(i=0;i<=n;i++)
			     p+=f[n][i]*C[i][q-m];
			  }
		return p;
    }
};
