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
class EllysChessboard
{
	int n,x[100],y[100],f[20][20][20][20];
public:
	int minCost(vector<string> s)
	{
		int i,j,k,l,u,v,w,p;
		for(i=0;i<s.size();i++)
		  for(j=0;j<s[0].size();j++)
		    if(s[i][j]=='#')
		      {
			   x[++n]=i+j;
			   y[n]=i-j+7;
			  }
		for(u=0;u<=14;u++)
		  for(i=0;i+u<=14;i++)
		    for(v=0;v<=14;v++)
		      for(k=0;k+v<=14;k++)
		        {
				 j=i+u;
				 l=k+v;
				 if(i==j && k==l)
				   continue;
				 f[i][j][k][l]=1000000000;
		         //每次将矩形扩大一行/一列 
				 if(i<j)
				   {
				    p=0;
					for(w=1;w<=n;w++)
					  if(x[w]==i && y[w]>=k && y[w]<=l)
					    p+=max(j-x[w],max(y[w]-k,l-y[w]));
					f[i][j][k][l]=min(f[i][j][k][l],f[i+1][j][k][l]+p);
				    p=0;
					for(w=1;w<=n;w++)
					  if(x[w]==j && y[w]>=k && y[w]<=l)
					    p+=max(x[w]-i,max(y[w]-k,l-y[w]));
					f[i][j][k][l]=min(f[i][j][k][l],f[i][j-1][k][l]+p);
				   }
				 if(k<l)
				   {
				    p=0;
					for(w=1;w<=n;w++)
					  if(y[w]==k && x[w]>=i && x[w]<=j)
					    p+=max(l-y[w],max(x[w]-i,j-x[w]));
					f[i][j][k][l]=min(f[i][j][k][l],f[i][j][k+1][l]+p);
				    p=0;
					for(w=1;w<=n;w++)
					  if(y[w]==l && x[w]>=i && x[w]<=j)
					    p+=max(y[w]-k,max(x[w]-i,j-x[w]));
					f[i][j][k][l]=min(f[i][j][k][l],f[i][j][k][l-1]+p);
				   }
				}
		return f[0][14][0][14];
    }
};
