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
class Egalitarianism
{
	int n,f[60][60],p;
public:
	int maxDifference(vector<string> x,int q)
	{
		int i,j,k;
		n=x.size();
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    if(i!=j)
		      if(x[i][j]=='Y')
		        f[i][j]=1;
		      else
		        f[i][j]=1000000000;
		//floyd
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    for(k=0;k<n;k++)
		      f[j][k]=min(f[j][k],f[j][i]+f[i][k]);
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    p=max(p,f[i][j]);
		return p==1000000000?-1:p*q;
    }
};
