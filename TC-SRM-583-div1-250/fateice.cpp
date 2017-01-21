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
class TravelOnMars
{
	int n,f[60][60];
public:
	int minTimes(vector<int> x,int s,int t)
	{
		int i,j,k;
		n=x.size();
		//建边 
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    if(i==j)
		      f[i][j]=0;
		    else if((j-i+n)%n<=x[i] || (i-j+n)%n<=x[i])
		      f[i][j]=1;
		    else
		      f[i][j]=10000;
		//floyd 
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    for(k=0;k<n;k++)
		      f[j][k]=min(f[j][k],f[j][i]+f[i][k]);
		return f[s][t];
    }
};
