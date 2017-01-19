#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
using namespace std;
class KingdomAndDice
{
	int x[60],a[60],b[60];
	bool f[55][55][2510];
public:
	double newFairness(vector<int> aa,vector<int> bb,int m)
	{
		int n=aa.size(),t=0,w=0,ans;
		int i,j,k,l;
		for(i=1;i<=n;i++)
		  {
		   a[i]=aa[i-1];
		   b[i]=bb[i-1];
		  }
		//将第二个骰子上的数排序，记下第一个骰子在相邻两个数之间还能放置多少个数  x[i]表示比第二个骰子中的i个数大的数的数量 
		sort(a+1,a+n+1);
		sort(b+1,b+n+1);
		b[n+1]=m+1;
		for(i=0;i<=n;i++)
		  x[i]=b[i+1]-b[i]-1;
		for(i=1;i<=n;i++)
		  if(!a[i])
		    t=i;
		  else
		    {
			 for(j=0;j<n && b[j+1]<a[i];j++);
			 w+=j;
			 x[j]--;
			}
		//dp f[i][j][k]表示从前i种数中取出j个，当前第一个骰子大于第二个骰子的情况数为k是否可行 
		for(i=0;i<=t;i++)
		  f[0][i][w]=1;
		for(i=1;i<=n;i++)
		  for(j=0;j<=t;j++)
		    for(k=0;k<=n*n;k++)
		      if(f[i-1][j][k])
		        for(l=0;l<=x[i] && j+l<=t;l++)
		          f[i][j+l][k+i*l]=1;
		ans=-1;
		for(i=0;i<=n*n;i++)
		  if(f[n][t][i] && abs(n*n-2*i)<abs(n*n-2*ans))
		    ans=i;
		return double(ans)/(n*n);
	}
};
