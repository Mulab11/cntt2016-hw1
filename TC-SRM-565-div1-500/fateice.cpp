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
class TheDivisionGame
{
	int n,x[1000010],s[1000010],a[1000010];
	long long p;
public:
	long long countWinningIntervals(int l,int r)
	{
		int i,j;
		n=r-l+1;
		for(i=1;i<=n;i++)
		  a[i]=l+i-1;
		for(i=2;i*i<=r;i++)
		  for(j=(i-l%i)%i+1;j<=n;j+=i)
		    while(a[j]%i==0)
		      {
			   a[j]/=i;
			   x[j]++;
			  }
		for(i=1;i<=n;i++)
		  if(a[i]>1)
		    x[i]++;
		for(i=1;i<=n;i++)
		  s[i]=s[i-1]^x[i];
		sort(s,s+n+1);
		p=(L)n*(n+1)/2;
		//统计有多少组不满足条件 
		for(i=0;i<=n;i=j)
		  {
		   for(j=i;j<=n && s[i]==s[j];j++);
		   p-=(L)(j-i)*(j-i-1)/2;
		  }
		return p;
    }
};
