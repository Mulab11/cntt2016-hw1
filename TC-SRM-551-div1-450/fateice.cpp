#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
using namespace std;
class ColorfulWolves
{
public:
	int getmin(vector<string> a)
	{
		int n=a.size();
		int x[60][60];
		int i,j,k;
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    if(i!=j)
		      x[i][j]=1000000;
		    else
		      x[i][j]=0;
		for(i=0;i<n;i++)
		  for(j=0,k=0;j<n;j++)
		    if(a[i][j]=='Y')
		      x[i][j]=k++;    //求出使i一步变为j的代价 
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    for(k=0;k<n;k++)
		      x[j][k]=min(x[j][k],x[j][i]+x[i][k]);    //最短路 
		return x[0][n-1]==1000000?-1:x[0][n-1];
	}
};
